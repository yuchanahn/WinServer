#include "COMPONENT_H.h"
#include "MysqlManager.h"
#include "ItemManager.h"

cItem::~cItem()
{
}

void cItem::Start()
{
	ItemManager::getItemData();
	MysqlManager::GetInstance()->GetItems();

}
