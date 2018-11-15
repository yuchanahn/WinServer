#include "COMPONENT_H.h"
#include "ReadManager.h"



cEffect::~cEffect()
{
}

void cEffect::Start()
{
	ReadManager::ReadSome[Class::Class_fIG_Effect] = [this](PackData* data, std::shared_ptr<session> client)
	{
		WriteManager<fIG_Effect, fIG_EffectT> w;
		w.wdata = data->Get<fIG_Effect>();
		w.Write();
	};
}
