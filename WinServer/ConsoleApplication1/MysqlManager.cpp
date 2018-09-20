#include "MysqlManager.h"
#include <iostream>
#include "mysqlpool.h"
#include "Base_generated.h"
#include "ItemManager.h"
#include "cMonsterManager.h"


using namespace std;

MysqlManager::MysqlManager()
{
	mysql = MysqlPool::getMysqlPoolObject();
	mysql->setParameter("35.229.140.57", "anyc123", "123", "Main", 3306, NULL, 0, 50);
}

MysqlManager::~MysqlManager()
{

}


bool MysqlManager::IsIdPassSame(LoginT * data, int * Id)
{
	if (GetLoginData(data, Id) == eLogin::passSame) {
		return true;
	}
	return false;
}

bool MysqlManager::IsIdNone(LoginT * data)
{
	if (GetLoginData(data, nullptr) == eLogin::idNone) {
		return true;
	}
	return false;
}



std::list<CreateMonsterData*> MysqlManager::GetMonsterInfo()
{
	std::list<CreateMonsterData*> Monsters;
	
	auto m = mysql->executeSql("select * from MonsterInfo");
	
	for (size_t i = 0; i < m["StartX"].size(); i++) {
		Monsters.push_back(new CreateMonsterData(
			m["Name"][i], 
			atof(m["StartX"][i]),
			atof(m["StartY"][i]),
			atoi(m["HP"][i]),
			atoi(m["Exp"][i])
		));
	}

	return Monsters;
}

int MysqlManager::CreateID(LoginT * data)
{
	char str[256];
	sprintf_s(str, "INSERT INTO LoginData (LoginData.id,LoginData.pass) VALUES('%s', '%s');", data->id.c_str(), data->pass.c_str());
	mysql->executeSql(str);

	sprintf_s(str, "select LoginData.key from LoginData Where LoginData.id = '%s';", data->id.c_str());
	int ID = stoi(mysql->executeSql(str)["key"][0]);
	
	
	sprintf_s(str , "INSERT INTO `Inventory`  (`UserKey`) VALUES ('%d');", ID);
	mysql->executeSql(str);
	sprintf_s(str , "INSERT INTO `SkillInfo`  (`UserKey`) VALUES ('%d');", ID);
	mysql->executeSql(str);
	sprintf_s(str , "INSERT INTO `PlayerInfo` (`UserKey`) VALUES ('%d');", ID);
	mysql->executeSql(str);

	return ID;
}

void MysqlManager::SetPlayerStat(PlayerStatT * stat)
{
	char str[256];
	sprintf_s(str, "UPDATE `Main`.`PlayerInfo` SET `Hp`='%d' WHERE  `UserKey`=%d LIMIT 1;", stat->HP, stat->ID);
	mysql->executeSql(str);
}

void MysqlManager::SetPlayerPos(PlayerT * player)
{
	char str[256];
	auto pos = new Vec3(player->pos->x(), player->pos->y(), player->pos->z());
	sprintf_s(str, "UPDATE `Main`.`PlayerInfo` SET `X`='%lf' ,`Y`='%lf' ,`Z`='%lf' WHERE  `UserKey`=%d LIMIT 1;", pos->x(), pos->y(), pos->z(), player->ID);
	mysql->executeSql(str); 
}

void MysqlManager::SetInv(int inv[30],int id)
{
	char str[50];
	string m_kstr = "";

	sprintf_s(str, "UPDATE `Main`.`Inventory` SET `1`='%d'", inv[0]);
	m_kstr.append(str);

	string m_kstrEnd = "WHERE  `UserKey`=%d;";

	for (int i = 2; i < 31; i++) {
		sprintf_s(str, ",`%d`='%d'", i, inv[i-1]);
		m_kstr.append(str);
	}

	sprintf_s(str, "WHERE  `UserKey`=%d;", id);
	m_kstr.append(str);

	mysql->executeSql(m_kstr.c_str());
}

void MysqlManager::SetItem(int userItemid, int count)
{
	char str[256];
	sprintf_s(str, "UPDATE `Main`.`UserItem` SET `Count`='%d' WHERE  `ItemKey`=%d;", count,userItemid);
	auto m = mysql->executeSql(str);
}

// : delete Item
void MysqlManager::SetItem(int userItemid)
{
	char str[256];
	sprintf_s(str, "DELETE FROM `Main`.`UserItem` WHERE  `ItemKey`=%d;", userItemid);
	auto m = mysql->executeSql(str);
}







PlayerStatT * MysqlManager::GetPlayerStat(int id)
{
	char str[256];
	sprintf_s(str, "select * from PlayerInfo WHERE `UserKey`=%d LIMIT 1;", id);
	auto m = mysql->executeSql(str);

	PlayerStatT * stat = new PlayerStatT;

	stat->cType = Class::Class_PlayerStat;
	stat->HP = stoi(m["Hp"][0]);
	stat->HPLim = stoi(m["HpLim"][0]);
	stat->ID = id;

	return stat;
}

Vec3 * MysqlManager::GetPlayerPos(int id)
{
	char str[256];
	sprintf_s(str, "select * from PlayerInfo WHERE `UserKey`=%d LIMIT 1;", id);
	auto m = mysql->executeSql(str);
	printf("load data : %lf, %lf, %lf \n", stof(m["X"][0]), stof(m["Y"][0]), stof(m["Z"][0]));
	return new Vec3(stof(m["X"][0]), stof(m["Y"][0]), stof(m["Z"][0]));
}

int MysqlManager::isPlayerIDandPass(char * id, char * pass)
{
	char str[256];
	sprintf_s(str, "select count(*) from LoginData Where LoginData.id = '%s';", id);

	if (GetDataCount_LogIn(str)) {
		sprintf_s(str, "select LoginData.pass from LoginData Where LoginData.id = '%s';", id);

		if ( !strcmp(mysql->executeSql(str)["pass"][0], pass) ) {
			sprintf_s(str, "select LoginData.key from LoginData Where LoginData.id = '%s';", id);
			printf("mysql : %s\n" , mysql->executeSql(str)["key"][0]);
			int d = stoi(mysql->executeSql(str)["key"][0]);
			return d;
		}
		return -2;
	}
	return -1;
}

void MysqlManager::GetPlayerInventory(int id , int inven[30]) {
	char str[256];
	sprintf_s(str, "select * from Inventory WHERE `UserKey`=%d LIMIT 1;", id);
	auto m = mysql->executeSql(str);

	for (int i = 0; i < 30;	i++) {

		auto SlotNum = m[ std::to_string(i + 1) ][0];

		inven[i] = stoi(SlotNum);
	}
}

void MysqlManager::GetItems() {
	char str[256];
	sprintf_s(str, "select * from Item;");
	auto Item = mysql->executeSql(str);
	sprintf_s(str, "select * from UserItem;");
	auto uItem = mysql->executeSql(str);

	ItemManager im;
	im.ItemSeting(uItem, Item);
}





int MysqlManager::GetDataCount_LogIn(char * str)
{
	auto m = mysql->executeSql(str);
	return stoi(m["count(*)"][0]);
}




eLogin MysqlManager::GetLoginData(LoginT * data, int * ID)
{
	auto stat = isPlayerIDandPass((char*)data->id.c_str(), (char*)data->pass.c_str());

	if (stat >= 0) {
		if(ID != nullptr) *ID = stat;
		return eLogin::passSame;
	}
	else if (stat == -1) {
		return eLogin::idNone;
	}

	return eLogin::idSame;
}

