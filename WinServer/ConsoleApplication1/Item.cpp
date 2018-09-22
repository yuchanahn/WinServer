#include "Item.h"
#include "MysqlManager.h"
#include "ItemManager.h"

Item::Item()
{

}


Item::~Item()
{
}

void Item::SetUserItem(int useritemID)
{
	MysqlManager m;
	m.SetItem(useritemID);
}

void Item::SetUserItem(int useritemID, int count)
{
	MysqlManager m;
	m.SetItem(useritemID,count);
}

int Item::CreateItem(int itemcode, int count)
{
	MysqlManager m;

	auto temid = m.CreateItem(itemcode, count);
	Items[temid].wdata->count = count;

	ItemManager::ItemSeting(temid, itemcode);

	return temid;
}

std::map<int, WriteManager<fItem, fItemT>> Item::Items;