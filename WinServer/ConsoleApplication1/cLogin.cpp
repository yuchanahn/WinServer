#include "COMPONENT_H.h"
#include "MysqlManager.h"

cLogin::~cLogin()
{
}

void cLogin::Start()
{
	ReadManager::ReadSome[Class::Class_LogIn] = [this](PackData* data, std::shared_ptr<session> client) {

		server::UseStrand([=]() {
			
			data->Get < Login, LoginT > (wdata);
			MysqlManager m;

			int oID;
			auto e = m.GetLoginData(wdata, &oID);

			switch (e)
			{
			case eLogin::passSame:
				if (!wdata->isSignin)
				{
					isNonSuccess(client->shared_from_this());
				}
				else
				{
					session::InputSession[oID] = client->shared_from_this();
					client->id = oID;
					wdata->id = std::to_string(oID);
					isSuccess(client->shared_from_this());
					client->IsLogined();

				}
				break;
			case eLogin::idSame:
				if (!wdata->isSignin)
				{
					isNonSuccess(client->shared_from_this());
				}
				else
				{
					isNonSuccess(client->shared_from_this());
				}
				break;
			case eLogin::idNone:
				if (!wdata->isSignin)
				{
					int ID = m.CreateID(wdata);
					isSuccess(client->shared_from_this());
				}
				else
				{
					isNonSuccess(client->shared_from_this());
				}
				break;
			default:
				break;
			}
			delete data;
		});
	};
}

void cLogin::isSuccess(std::shared_ptr<session> client)
{
	wdata->isSuccess = true;
	Write(client);
}

void cLogin::isNonSuccess(std::shared_ptr<session> client)
{
	wdata->isSuccess = false;
	Write(client);
}
