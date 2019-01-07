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
	mysql->setParameter("35.200.70.203", "anyc123", "123", "Main", 3306, NULL, 0, 50);
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
			atoi(m["Exp"][i]),
			atof(m["Speed"][i]),
			atof(m["Range"][i]),
			atof(m["FollowRange"][i]),
			atof(m["RandRange"][i]),
			atof(m["ATKAttribute"][i]),
			atof(m["ATKDamage"][i]),
			atof(m["ATKTime"][i])
		));
	}

	return Monsters;
}

MysqlManager * MysqlManager::GetInstance()
{
	static MysqlManager * m = new MysqlManager();

	return m;
}

void MysqlManager::SetSkillSlot(int slot[], int UserKey)
{
	char str[50];
	string m_kstr = "";

	sprintf_s(str, "UPDATE `Main`.`SkillSlot` SET `1`='%d'", slot[0]);
	m_kstr.append(str);

	for (int i = 1; i < 30; i++) {
		sprintf_s(str, ",`%d`='%d'", i + 1, slot[i]);
		m_kstr.append(str);
	}

	sprintf_s(str, "WHERE  `UserKey`=%d;", UserKey);
	m_kstr.append(str);

	mysql->executeSql(m_kstr.c_str());
}
void MysqlManager::GetSkillSlot(int slot[], int UserKey)
{
	char str[256];
	sprintf_s(str, "SELECT * FROM `Main`.`SkillSlot` WHERE `UserKey`=%d LIMIT 1;", UserKey);
	auto m = mysql->executeSql(str);

	for (int i = 0; i < 30; i++) {
		slot[i] = stoi(m[std::to_string(i + 1)][0]);
	}
}


void MysqlManager::SetKeySlot(int slot[], int UserKey)
{
	char str[256];
	sprintf_s(str, 
		"UPDATE `Main`.`KeySlot` SET `q`='%d', `w`='%d', `e`='%d', `r`='%d', `a`='%d', `s`='%d', `d`='%d', `f`='%d'  WHERE  `UserKey`=%d LIMIT 1;",
		slot[0],
		slot[1], 
		slot[2], 
		slot[3], 
		slot[4], 
		slot[5],
		slot[6],
		slot[7],
		UserKey);

	mysql->executeSql(str);
}

void MysqlManager::GetKeySlot(int slot[], int UserKey)
{
	char str[256];
	sprintf_s(str, "SELECT * FROM `Main`.`KeySlot` WHERE `UserKey`=%d LIMIT 1;", UserKey);
	auto mSlot = mysql->executeSql(str);

	slot[0] = stoi(mSlot["q"][0]);
	slot[1] = stoi(mSlot["w"][0]);
	slot[2] = stoi(mSlot["e"][0]);
	slot[3] = stoi(mSlot["r"][0]);
	slot[4] = stoi(mSlot["a"][0]);
	slot[5] = stoi(mSlot["s"][0]);
	slot[6] = stoi(mSlot["d"][0]);
	slot[7] = stoi(mSlot["f"][0]);
}

void MysqlManager::GetEquipSlot(int Slot[EQUIP_SLOT_MAX], int id)
{
	char str[256];
	sprintf_s(str, "SELECT * FROM `Main`.`EquipSlot` WHERE `UserKey`=%d LIMIT 1;", id);
	auto m = mysql->executeSql(str);

	Slot[0] = atoi(m["weapon"][0]);
	Slot[1] = atoi(m["weapon2"][0]);
	Slot[2] = atoi(m["helm"][0]);
	Slot[3] = atoi(m["armor"][0]);
}

int MysqlManager::CreateID(LoginT * data)
{
	char str[256];
	sprintf_s(str, "INSERT INTO LoginData (LoginData.id,LoginData.pass) VALUES('%s', '%s');", data->id.c_str(), data->pass.c_str());
	mysql->executeSql(str);

	sprintf_s(str, "select LoginData.key from LoginData Where LoginData.id = '%s';", data->id.c_str());
	int ID = stoi(mysql->executeSql(str)["key"][0]);


	sprintf_s(str, "INSERT INTO `Inventory`  (`UserKey`) VALUES ('%d');", ID);
	mysql->executeSql(str);
	sprintf_s(str, "INSERT INTO `SkillInfo`  (`UserKey`) VALUES ('%d');", ID);
	mysql->executeSql(str);
	sprintf_s(str, "INSERT INTO `PlayerInfo` (`UserKey`) VALUES ('%d');", ID);
	mysql->executeSql(str);

	sprintf_s(str, "UPDATE `PlayerInfo`  SET `Name`='%s' WHERE  `UserKey`=%d LIMIT 1;", data->nikName.c_str(),ID);
	mysql->executeSql(str);

	sprintf_s(str, "INSERT INTO `EquipSlot` (`UserKey`) VALUES ('%d');", ID);
	mysql->executeSql(str);
	sprintf_s(str, "INSERT INTO `SkillSlot` (`UserKey`) VALUES ('%d');", ID);
	mysql->executeSql(str);
	sprintf_s(str, "INSERT INTO `KeySlot` (`UserKey`) VALUES ('%d');", ID);
	mysql->executeSql(str);

	return ID;
}

void MysqlManager::SetPlayerStat(PlayerStatT * stat)
{
	char str[256];
	sprintf_s(str, "UPDATE `Main`.`PlayerInfo` SET `Hp`='%d', `HpLim`='%d', `Mp`='%d', `MpLim`='%d', `Exp`='%d',`Lv`='%d',`Attack`='%d' WHERE  `UserKey`=%d LIMIT 1;", 
		stat->HP, stat->HPLim,stat->MP, stat->MPLim, stat->EXP, stat->LV, stat->Attack, stat->ID);
	mysql->executeSql(str);
}

void MysqlManager::SetPlayerPos(PlayerT * player)
{
	char str[256];
	auto pos = new Vec3(player->pos->x(), player->pos->y(), player->pos->z());
	sprintf_s(str, "UPDATE `Main`.`PlayerInfo` SET `X`='%lf' ,`Y`='%lf' ,`Z`='%lf' WHERE  `UserKey`=%d LIMIT 1;", pos->x(), pos->y(), pos->z(), player->ID);
	mysql->executeSql(str);
}

void MysqlManager::SetInv(int inv[30], int id)
{
	char str[50];
	string m_kstr = "";

	sprintf_s(str, "UPDATE `Main`.`Inventory` SET `1`='%d'", inv[0]);
	m_kstr.append(str);

	string m_kstrEnd = "WHERE  `UserKey`=%d;";

	for (int i = 1; i < 30; i++) {
		sprintf_s(str, ",`%d`='%d'", i + 1, inv[i]);
		m_kstr.append(str);
	}

	sprintf_s(str, "WHERE  `UserKey`=%d;", id);
	m_kstr.append(str);

	mysql->executeSql(m_kstr.c_str());
}

void MysqlManager::SetItem(int userItemid, int count)
{
	char str[256];
	sprintf_s(str, "UPDATE `Main`.`UserItem` SET `Count`='%d' WHERE  `ItemKey`=%d;", count, userItemid);
	printf("[update] USER_ID : %d (Now_Count : %d)\n", userItemid, count);
	auto m = mysql->executeSql(str);
}

// : delete Item
void MysqlManager::SetItem(int userItemid)
{
	char str[256];
	sprintf_s(str, "DELETE FROM `Main`.`UserItem` WHERE  `ItemKey`=%d;", userItemid);
	printf("[delete] USER_ID : %d\n", userItemid);
	auto m = mysql->executeSql(str);
}

void MysqlManager::SetEquip(int EquipSlot[EQUIP_SLOT_MAX], int userId)
{
	char str[256];
	sprintf_s(str, 
		"UPDATE `Main`.`EquipSlot` SET `weapon`='%d' , `weapon2`='%d',`helm`='%d',`armor`='%d' WHERE `Userkey`=%d;", 
		EquipSlot[0], EquipSlot[1], EquipSlot[2], EquipSlot[3], userId);
	printf("[update] EQUIPSLOT (PID : %d)\n", userId);
	auto m = mysql->executeSql(str);
}

int MysqlManager::CreateItem(int ItemCode, int count)
{
	char str[256];
	sprintf_s(str, "INSERT INTO `Main`.`UserItem` (`ItemId`, `Count`) VALUES ('%d', '%d');", ItemCode, count);
	auto m = mysql->executeSql(str);

	auto m2 = mysql->executeSql("SELECT * FROM `Main`.`UserItem`;");
	auto val = stoi(m2["ItemKey"][m2["ItemKey"].size() - 1]);
	return val;
}







PlayerStatT * MysqlManager::GetPlayerStat(int id, std::string & name)
{
	char str[256];
	sprintf_s(str, "select * from PlayerInfo WHERE `UserKey`=%d LIMIT 1;", id);
	auto m = mysql->executeSql(str);

	PlayerStatT * stat = new PlayerStatT;

	stat->cType = Class::Class_PlayerStat;
	stat->HP = stoi(m["Hp"][0]);
	stat->HPLim = stoi(m["HpLim"][0]);
	stat->MP = stoi(m["Mp"][0]);
	stat->MPLim= stoi(m["MpLim"][0]);
	stat->EXP = stoi(m["Exp"][0]);
	stat->Attack = stoi(m["Attack"][0]);
	stat->LV = stoi(m["Lv"][0]);
	stat->ID = id;
	stat->nikName = m["Name"][0];
	
	name = m["Name"][0];
	printf("@ LOAD NAME : %s\n", name.c_str());
	return stat;
}

Vec3 * MysqlManager::GetPlayerPos(int id)
{
	char str[256];
	sprintf_s(str, "select * from PlayerInfo WHERE `UserKey`=%d LIMIT 1;", id);
	auto m = mysql->executeSql(str);
	printf("@ PLAYER POS LOAD : %lf, %lf, %lf \n", stof(m["X"][0]), stof(m["Y"][0]), stof(m["Z"][0]));
	return new Vec3(stof(m["X"][0]), stof(m["Y"][0]), stof(m["Z"][0]));
}

int MysqlManager::isPlayerIDandPass(char * id, char * pass)
{
	char str[256];
	sprintf_s(str, "select count(*) from LoginData Where LoginData.id = '%s';", id);

	if (GetDataCount_LogIn(str)) {
		sprintf_s(str, "select LoginData.pass from LoginData Where LoginData.id = '%s';", id);

		if (!strcmp(mysql->executeSql(str)["pass"][0], pass)) {
			sprintf_s(str, "select LoginData.key from LoginData Where LoginData.id = '%s';", id);
			printf("@ PLAYER NUMBER : %s\n", mysql->executeSql(str)["key"][0]);
			int d = stoi(mysql->executeSql(str)["key"][0]);
			return d;
		}
		return -2;
	}
	return -1;
}

void MysqlManager::GetPlayerInventory(int id, int inven[30]) {
	bool DataNoneSave = true;

	std::cout << "@ LOAD LIVENTORY\n";
	char str[256];
	sprintf_s(str, "SELECT * FROM `Main`.`Inventory` WHERE `UserKey`=%d LIMIT 1;", id);
	auto m = mysql->executeSql(str);

	for (int i = 0; i < 30; i++) {
		printf("%2d |%s| ", i+1, m[std::to_string(i + 1)][0]);
		inven[i] = stoi(m[std::to_string(i + 1)][0]);

		if ((i + 1) % 10 == 0) {
			printf("\n");
		}
	}
}

void MysqlManager::GetItems() {
	auto uItem = mysql->executeSql("SELECT * FROM `Main`.`UserItem` LIMIT 1000;");
	ItemManager::Input(uItem);
}

std::map<const std::string, std::vector<const char*>> MysqlManager::GetThisItems() {
	return mysql->executeSql("SELECT * FROM `Main`.`Item` LIMIT 1000;");
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
		if (ID != nullptr) *ID = stat;
		return eLogin::passSame;
	}
	else if (stat == -1) {
		return eLogin::idNone;
	}

	return eLogin::idSame;
}

