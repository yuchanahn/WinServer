#include "ClientSession.h"

#define ASIO_STANDALONE
#define ASIO_HEADER_ONLY

#define ASIO_HAS_STD_ADDRESSOF
#define ASIO_HAS_STD_ARRAY
#define ASIO_HAS_CSTDINT
#define ASIO_HAS_STD_SHARED_PTR
#define ASIO_HAS_STD_TYPE_TRAITS

#define ASIO_HAS_VARIADIC_TEMPLATES
#define ASIO_HAS_STD_FUNCTION
#define ASIO_HAS_STD_CHRONO

#define BOOST_ALL_NO_LIB
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "Logmanager.h"
#include "MysqlManager.h"
#include "ReadManager.h"
#include "Base_generated.h"
#include "ClientSession.h"
#include "InputComponent.h"
#include "InventoryManager.h"
#include "COMPONENT_H.h"

#include "PlayerPositionManager.h"
#include "PlayerStateManager.h"
#include "EquipManager.h"

using asio::ip::tcp;

std::map<int, std::shared_ptr<session> > session::InputSession;


void session::start()
{
	id = -1;
	do_read();
}

void session::do_write(char * str, int len)
{
	Time::WriteTime++;
	auto self(shared_from_this());

	PackData * pd = new PackData(len);
	memcpy(pd->data, str, len);

	asio::async_write(self->socket_, asio::buffer(pd->data, len)
		, [this, self, pd](std::error_code ec, std::size_t length) {
		if (!ec) {
			delete pd;
			//전송완료.
		}
		else {
			//예외.
		}
	});



}

void session::UseStrand(std::function<void()> f)
{
	auto self(shared_from_this());
	strand_.get_io_service().post(strand_.wrap([self, f] {
		f();
	}));
}


session::~session()
{
	if (state != nullptr)	delete state;
	if (position != nullptr)delete position;
	if (inventoryManager != nullptr) delete inventoryManager;
	if (equipManager != nullptr) delete equipManager;

	printf("클라이언트 접속 종료\nID : %d\n", id);
}

void session::do_read()
{
	auto self(shared_from_this());

	socket_.async_read_some(asio::buffer(data_, max_length)
		, [this, self](std::error_code ec, std::size_t length) {
		if (!ec) {
			ReadManager::Read(data_, length, shared_from_this());
			do_read();
		}
		else {
			InputSession.erase(id);

			server::UseStrand([self,this]() {
				isOffLine = true;
			});
		}
	});
}

void session::IsLogined() {
	//// strand 문제있을 수 있음.
	UseStrand([=]() {
		inventoryManager = new InventoryManager(id); 
		equipManager = new EquipManager(shared_from_this());
	});
}



void server::UseStrand(std::function<void()> f)
{
	ServerStrand->get_io_service().post(ServerStrand->wrap([f] {
		f();
	}));
}

void server::do_accept()
{
	acceptor_.async_accept(socket_,
		[this](std::error_code ec) {
		if (!ec) {
			asio::ip::tcp::no_delay option(true);
			socket_.set_option(option);
			std::make_shared<session>(std::move(socket_))->start();

		}
		do_accept();
	});
}

void server::ServerStart()
{
	gameObjects = new InputComponent;

	InputComponent* PingManager = new InputComponent;
	InputComponent* PlayerManager = new InputComponent;
	InputComponent* ServerFpsManger = new InputComponent;
	InputComponent* LoginManager = new InputComponent;
	InputComponent* MonsterManager = new InputComponent;

	PingManager->AddComponent<cPing>();

	LoginManager->AddComponent<cLogin>();

	
	PlayerManager->AddComponent<cInventory>(); 
	PlayerManager->AddComponent<cPlayer>();
	PlayerManager->AddComponent<cItem>();
	PlayerManager->AddComponent<cEquip>();

	ServerFpsManger->AddComponent<cServerFPS>();

	MonsterManager->AddComponent<cMonsterManager>();

	gameObjects->AddComponent(PingManager);
	gameObjects->AddComponent(PlayerManager);
	gameObjects->AddComponent(ServerFpsManger);
	gameObjects->AddComponent(LoginManager);
	gameObjects->AddComponent(MonsterManager);


	PlayerManager->GetComponent<cPlayer>()->MonsterManager = MonsterManager;

	gameObjects->Start();

	cLoop();
}

void server::cLoop()
{
	strand_.get_io_service().post(strand_.wrap([this] {
		Time::UpdateDeltaTime();
		//Time timer;
		//timer.TimerStart();
		gameObjects->Update();
		cLoop();
		//printf("%lf\n" ,timer.TimerEnd());
	}));
}

asio::io_service::strand * server::ServerStrand;