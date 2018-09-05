#pragma once
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <map>
#include <functional>

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

#include <asio.hpp>

class InputComponent;
class PlayerStateManager;
class PlayerPositionManager;
class SendStateTo;


using asio::ip::tcp;

class session : public std::enable_shared_from_this<session>{

	tcp::socket socket_; 
	asio::io_service::strand strand_;

	enum { max_length = 1024 };
	char data_[max_length];



public:
	static std::map<int, std::shared_ptr<session> > InputSession;

	PlayerStateManager*		state    = nullptr;
	PlayerPositionManager*	position = nullptr;

	int id;
	bool isOffLine = false;

	void start();
	void do_write(char * str, int len);
	void UseStrand(std::function<void()>);

	session(tcp::socket socket) :
		socket_(std::move(socket)),
		strand_(socket.get_io_service())
	{}
	~session();
private:
	void do_read();
};

class server {

	tcp::acceptor acceptor_;
	tcp::socket socket_;
	asio::io_service::strand strand_;

	static asio::io_service::strand * ServerStrand;

	InputComponent* gameObjects;

public:

	static void UseStrand(std::function<void()>);

	server(asio::io_service& io_service, short port)
		: acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
		socket_(io_service),
		strand_(io_service)
	{
		ServerStrand = &strand_;
		do_accept(); 
		ServerStart();
	}

private:
	void do_accept();
	void ServerStart();
	void cLoop();
};



