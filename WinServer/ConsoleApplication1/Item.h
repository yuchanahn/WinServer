#pragma once
#include "WriteManager.h"
#include <map>

class Item
{

public:
	static std::map<int, WriteManager<fItem, fItemT>> Items;
		
	Item();
	~Item();

	static void SetUserItem(int useritemID);
	static void SetUserItem(int useritemID,int count);

	static int CreateItem(int itemcode, int count);
};

