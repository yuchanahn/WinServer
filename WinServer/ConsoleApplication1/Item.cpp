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
	MysqlManager::GetInstance()->SetItem(useritemID);
}

void Item::SetUserItem(int useritemID, int count)
{
	MysqlManager::GetInstance()->SetItem(useritemID,count);
}

int Item::CreateItem(int itemcode, int count)
{
	auto temid = MysqlManager::GetInstance()->CreateItem(itemcode, count);
	Items[temid].wdata->count = count;


	ItemManager::AddItem(temid, itemcode);

	return temid;
}

std::map<int, WriteManager<fItem, fItemT>> Item::Items;