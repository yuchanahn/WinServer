#include "COMPONENT_H.h"
#include "MysqlManager.h"


cItem::~cItem()
{
}

void cItem::Start()
{
	MysqlManager::GetInstance()->GetItems();
}
