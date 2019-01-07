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
void ItemManager::Input(map<const string, vector<const char*>> uItem)
{
	auto UserItems = uItem;
	auto size = UserItems["ItemKey"].size();

	vector<int> key(size);
	vector<int> code(size);
	vector<int> count(size);
	for (int i = 0; i < size; i++) {
		key[i] = stoi(UserItems["ItemKey"][i]);
		code[i] = stoi(UserItems["ItemId"][i]);
		count[i] = stoi(UserItems["Count"][i]);
	}


	for (int i = 0; i < size; i++) {
		*Item::Items[key[i]].wdata = *Items[code[i]];
		Item::Items[key[i]].wdata->count = count[i];

		printf("<< [%s] item load... key : %d, code : %d\n", Items[code[i]]->name.c_str(), key[i], code[i]);
	}
}

void ItemManager::AddItem(int itemid, int itemCode)
{
	*Item::Items[itemid].wdata = *Items[itemCode];
}



void ItemManager::getItemData() {
	if (Items.empty())
	{
		auto m_items = MysqlManager::GetInstance()->GetThisItems();
		auto n = m_items["Id"].size();
		for (int i = 0; i < m_items["Id"].size(); i++) {
			Items[i] = new fItemT;
			Items[i]->cType = Class::Class_fItem;
			Items[i]->id = i;
			Items[i]->name.append(m_items["Name"][i]);
			Items[i]->type = stoi(m_items["type"][i]);
			Items[i]->val1 = stoi(m_items["1"][i]);
			Items[i]->val2 = stoi(m_items["2"][i]);
			Items[i]->val3 = stoi(m_items["3"][i]);
			Items[i]->val4 = stoi(m_items["4"][i]);
			Items[i]->val5 = stoi(m_items["5"][i]);
			Items[i]->val6 = stoi(m_items["6"][i]);
			Items[i]->val7 = stoi(m_items["7"][i]);
			Items[i]->val8 = stoi(m_items["8"][i]);

			printf("Item Load : %s\n", Items[i]->name.c_str());
		}
	}
}




std::map<int, fItemT*> ItemManager::Items;