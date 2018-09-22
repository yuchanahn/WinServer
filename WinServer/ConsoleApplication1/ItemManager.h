#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <map>

class ItemManager
{
public:
	static std::map<const std::string, std::vector<const char*>> m_items;

	ItemManager();
	~ItemManager();

	void ItemSeting(std::map<const std::string, std::vector<const char*>>,std::map<const std::string, std::vector<const char*>>);
	static void ItemSeting(int itemid, int itemcode);


};

