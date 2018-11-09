#include "COMPONENT_H.h"
#include "EquipManager.h"


cEquip::~cEquip()
{
}



void cInventory::Start()
{
	ReadManager::ReadSome[Class::Class_fEquip] = [this](PackData* data, std::shared_ptr<session> client) {
		auto EquipSlot = data->Get<fEquip>();
		try
		{
			client->equipManager->Set(0, EquipSlot->weapon);
			client->equipManager->Set(1, EquipSlot->weapon2);
			client->equipManager->Set(2, EquipSlot->helm);
			client->equipManager->Set(3, EquipSlot->armor);
		}
		catch (const std::exception&)
		{
			printf("[READ] EQUIP exception!\n");
			delete data;
			return;
		}
		
		delete data;
	};
}