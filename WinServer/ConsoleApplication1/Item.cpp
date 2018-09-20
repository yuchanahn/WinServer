#include "Item.h"
#include "MysqlManager.h"


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

std::map<int, WriteManager<fItem, fItemT>> Item::Items;