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

void Item::RemoveDropItem(int DropID)
{
	Item::Items.erase(DropItems[DropID]);
	Item::SetUserItem(DropItems[DropID]);

	DropItemsPos.erase(DropID);
	DropItems.erase(DropID);
}

int Item::AddDropItem(int useritemID, float x, float y, float z)
{
	DropItemsPos[DropItemNum] = Uvector3(x,y,z);
	DropItems[DropItemNum] = useritemID;
	return DropItemNum++;
}

WriteManager<fDropItem, fDropItemT> Item::GetDropItem(int DropItemID)
{
	WriteManager<fDropItem, fDropItemT> w;
	w.wdata->cType = Class::Class_fDropItem;
	w.wdata->dID = DropItemID;
	w.wdata->dName = Items[DropItems[DropItemID]].wdata->name;
	w.wdata->x = DropItemsPos[DropItemID].x;
	w.wdata->y = DropItemsPos[DropItemID].y;
	w.wdata->z = DropItemsPos[DropItemID].z;
	w.wdata->count = Items[DropItems[DropItemID]].wdata->count;
	return w;
}


int Item::CreateItem(int itemcode, int count)
{
	auto temid = MysqlManager::GetInstance()->CreateItem(itemcode, count);
	ItemManager::AddItem(temid, itemcode);
	Items[temid].wdata->count = count;
	Items[temid].wdata->cType = Class::Class_fItem;

	return temid;
}

std::map<int, WriteManager<fItem, fItemT>> Item::Items;
std::map<int, Uvector3> Item::DropItemsPos;
std::map<int, int> Item::DropItems;
int Item::DropItemNum = 1;