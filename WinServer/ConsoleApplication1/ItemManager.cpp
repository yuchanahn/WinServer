#include "ItemManager.h"
#include "Item.h"
#include "MysqlManager.h"

using namespace std;

ItemManager::ItemManager()
{
	
}


ItemManager::~ItemManager()
{
}

void ItemManager::ItemSeting(map<const string, vector<const char*>> uItem, map<const string, vector<const char*>> Item)
{
	for (int i = 1; i < uItem["ItemKey"].size()+1; i++) {
		
		auto ItemID = stoi(uItem["ItemId"][i-1]) - 1;
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
		Item::Items[i].wdata->count = stoi(uItem["Count"][i-1]);
	}

}

void ItemManager::ItemSeting(int itemid, int itemcode)
{
	if (m_items.empty()) {
		MysqlManager m;
		m_items = m.GetThisItems();
	}

	Item::Items[itemid].wdata->cType = Class::Class_fItem;
	Item::Items[itemid].wdata->id = stoi(m_items["Id"][itemcode]);
	Item::Items[itemid].wdata->name = m_items["Name"][itemcode];
	Item::Items[itemid].wdata->type = stoi(m_items["type"][itemcode]);
	Item::Items[itemid].wdata->val1 = stoi(m_items["1"][itemcode]);
	Item::Items[itemid].wdata->val2 = stoi(m_items["2"][itemcode]);
	Item::Items[itemid].wdata->val3 = stoi(m_items["3"][itemcode]);
	Item::Items[itemid].wdata->val4 = stoi(m_items["4"][itemcode]);
	Item::Items[itemid].wdata->val5 = stoi(m_items["5"][itemcode]);
	Item::Items[itemid].wdata->val6 = stoi(m_items["6"][itemcode]);
	Item::Items[itemid].wdata->val7 = stoi(m_items["7"][itemcode]);
	Item::Items[itemid].wdata->val8 = stoi(m_items["8"][itemcode]);
}

std::map<const std::string, std::vector<const char*>> ItemManager::m_items;