#pragma once
#include "WriteManager.h"
#include <map>

class Item
{

	
	
public:
	static std::map<int, WriteManager<fItem, fItemT>> Items;

	Item();
	~Item();
};

