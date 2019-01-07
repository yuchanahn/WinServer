#pragma once
#include "WriteManager.h"
#include <map>
#include "CPoint.h"

class Uvector3 {

public:

	Uvector3(){}

	Uvector3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	float x;
	float y;
	float z;
};

class Item
{
	static int DropItemNum;
public:
	static std::map<int, WriteManager<fItem, fItemT>> Items;
	static std::map<int, Uvector3> DropItemsPos;
	static std::map<int, int> DropItems;
		
	Item();
	~Item();

	static void SetUserItem(int useritemID);
	static void SetUserItem(int useritemID,int count);
	static void RemoveDropItem(int useritemID);
	static int AddDropItem(int useritemID, float x, float y, float z);
	static WriteManager<fDropItem, fDropItemT> GetDropItem(int useritemID);
	static int CreateItem(int itemcode, int count);
};

