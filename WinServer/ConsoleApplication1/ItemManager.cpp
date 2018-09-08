#include "ItemManager.h"
#include "Item.h"

using namespace std;

ItemManager::ItemManager()
{
	
}


ItemManager::~ItemManager()
{
}

void ItemManager::ItemSeting(map<const string, vector<const char*>> uItem, map<const string, vector<const char*>> Item)
{
	for (int i = 0; i < uItem["ItemKey"].size(); i++) {
		
		auto ItemID = stoi(uItem["ItemId"][i]);

		Item::Items[i].wdata->cType = Class::Class_fItem;
		Item::Items[i].wdata->id = stoi(Item["Id"][ItemID]);
		Item::Items[i].wdata->name = Item["Name"][ItemID];
		Item::Items[i].wdata->type = stoi(Item["type"][ItemID]);
		Item::Items[i].wdata->val1 = stoi(Item["1"][ItemID]);
		Item::Items[i].wdata->val2 = stoi(Item["2"][ItemID]);
		Item::Items[i].wdata->val3 = stoi(Item["3"][ItemID]);
		Item::Items[i].wdata->val4 = stoi(Item["4"][ItemID]);
		Item::Items[i].wdata->val5 = stoi(Item["5"][ItemID]);
		Item::Items[i].wdata->val6 = stoi(Item["6"][ItemID]);
		Item::Items[i].wdata->val7 = stoi(Item["7"][ItemID]);
		Item::Items[i].wdata->val8 = stoi(Item["8"][ItemID]);
		Item::Items[i].wdata->count = stoi(uItem["Count"][i]);
	}
}