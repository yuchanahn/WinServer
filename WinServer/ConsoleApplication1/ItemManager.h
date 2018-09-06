#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <map>

class ItemManager
{
public:
	ItemManager();
	~ItemManager();

	void ItemSeting(std::map<const std::string, std::vector<const char*>>,std::map<const std::string, std::vector<const char*>>);
};

