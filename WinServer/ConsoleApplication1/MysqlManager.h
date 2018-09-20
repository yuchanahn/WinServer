#pragma once
#include <string>
#include <map>
#include <vector>
#include <list>

class CreateMonsterData;
struct LoginT;
struct PlayerStatT;
struct Vec3;
struct PlayerT;

class MysqlPool;

enum class eLogin
{
	idSame,passSame,idNone
};

class MysqlManager
{

	MysqlPool * mysql;



public:
	MysqlManager();
	~MysqlManager();

	bool IsIdPassSame(LoginT * data , int * Id);
	bool IsIdNone(LoginT * data);
	int CreateID(LoginT * data);
	


	void SetPlayerStat(PlayerStatT * stat);
	void SetPlayerPos(PlayerT * player);
	
	void SetInv(int inv[30],int id);
	void SetItem(int userItemid, int count);
	void SetItem(int userItemid);

	PlayerStatT * GetPlayerStat(int id);
	Vec3 * GetPlayerPos(int id);


	int isPlayerIDandPass(char * id, char * pass);

	void GetPlayerInventory(int id, int inven[30]);

	void GetItems();

	int GetDataCount_LogIn(char * str);


	eLogin GetLoginData(LoginT * data, int * ID);

	std::list<CreateMonsterData*> GetMonsterInfo();
};

