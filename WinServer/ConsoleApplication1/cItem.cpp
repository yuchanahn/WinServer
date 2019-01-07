#include "COMPONENT_H.h"
#include "MysqlManager.h"
#include "ItemManager.h"
#include "Item.h"
#include "InventoryManager.h"


cItem::~cItem()
{
}

void cItem::Start()
{
	ItemManager::getItemData();
	MysqlManager::GetInstance()->GetItems();
	ReadManager::ReadSome[Class::Class_fDropItem] = [this](PackData* data, std::shared_ptr<session> client)
	{
		auto dItem = data->Get<fDropItem>();


		server::UseStrand([=]() {
			Item::Items[dItem->dID].wdata->count -= dItem->count;

			int newItemID;
			if (Item::Items[dItem->dID].wdata->count < 1)
			{
				client->inventoryManager->InvSet(dItem->dID);
				newItemID = dItem->dID;
			}
			else
			{
				Item::SetUserItem(dItem->dID, Item::Items[dItem->dID].wdata->count);
				newItemID = Item::CreateItem(Item::Items[dItem->dID].wdata->id, dItem->count);
			}

			int DropItemID = Item::AddDropItem(newItemID, dItem->x, dItem->y, dItem->z);
			Item::GetDropItem(DropItemID).Write();

			delete data;
		});
	};


	ReadManager::ReadSome[Class::Class_fItemGet] = [this](PackData* data, std::shared_ptr<session> client)
	{
		auto gItem = data->Get<fItemGet>();
		int id = Item::DropItems[gItem->dID];
		server::UseStrand([=]() {
			if (Item::Items.find(id) != Item::Items.end()) {
				Item::Items[id].wdata->type = -1;
				client->inventoryManager->InvUpdate(Item::Items[id].wdata);

				DropEND(gItem->dID);

				Item::RemoveDropItem(gItem->dID);
			}
			delete data;
		});
	};
}

void cItem::DropEND(int ItemID)
{
	auto DropEND = Item::GetDropItem(ItemID);
	DropEND.wdata->count = 0;
	DropEND.Write();
}



void cItem::GetDropItem(std::shared_ptr<session> client)
{
	server::UseStrand([=]() {
		for (auto i : Item::DropItems)
		{
			Item::GetDropItem(i.first).Write(client);
		}
	});
}