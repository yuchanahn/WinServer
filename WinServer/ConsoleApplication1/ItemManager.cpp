#include "ItemManager.h"
#include "Item.h"



ItemManager::ItemManager()
{
	
}


ItemManager::~ItemManager()
{
}

void ItemManager::ItemSeting(std::map<const std::string, std::vector<const char*>> uItem, std::map<const std::string, std::vector<const char*>> Item)
{
	for (int i = 0; i < uItem["ItemKey"].size(); i++) {
		
		auto ItemID = std::stoi(uItem["ItemId"][i]);

		Item::Items[i].wdata->cType = Class::Class_fItem;
		Item::Items[i].wdata->id = std::stoi(Item["Id"][ItemID]);
		Item::Items[i].wdata->name = std::stoi(Item["Name"][ItemID]);
		Item::Items[i].wdata->type = std::stoi(Item["type"][ItemID]);
		Item::Items[i].wdata->val1 = std::stoi(Item["1"][ItemID]);
		Item::Items[i].wdata->val2 = std::stoi(Item["2"][ItemID]);
		Item::Items[i].wdata->val3 = std::stoi(Item["3"][ItemID]);
		Item::Items[i].wdata->val4 = std::stoi(Item["4"][ItemID]);
		Item::Items[i].wdata->val5 = std::stoi(Item["5"][ItemID]);
		Item::Items[i].wdata->val6 = std::stoi(Item["6"][ItemID]);
		Item::Items[i].wdata->val7 = std::stoi(Item["7"][ItemID]);
		Item::Items[i].wdata->val8 = std::stoi(Item["8"][ItemID]);
		Item::Items[i].wdata->count = std::stoi(uItem["Count"][i]);
	}
}