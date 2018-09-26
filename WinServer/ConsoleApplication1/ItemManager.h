#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <map>

struct fItemT;

class ItemManager
{
public:
	static std::map<int, fItemT*> Items;




	ItemManager();
	~ItemManager();

	static void Input(std::map<const std::string, std::vector<const char*>> uItem);
	static void AddItem(int itemid, int itemcode);

	static void getItemData();


};

