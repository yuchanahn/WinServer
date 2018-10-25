#include "ClientSession.h"
#include <thread>
#include <vector>

int main(int argc, char* argv[]) {

	//try {
		auto io_service = new asio::io_service;
		std::vector< std::thread > WorkerThread;

		server s(*io_service, atoi("12588"));


		


		printf("# Thread LIST\n");
		for (int i = 0; i < std::thread::hardware_concurrency() * 2 + 1; i++) {
			WorkerThread.push_back(std::thread([=]() {
				printf("[%d Thread] id : %d\n", i, std::this_thread::get_id());
				io_service->run();
			}));
		}


		while (1) { Sleep(1000); }

		for (int i = 0; i < WorkerThread.size(); i++) {
			WorkerThread[i].join();
		}


//	}
	//catch (std::exception& e) {
		//std::cerr << "Exception: " << e.what() << "\n";
	//}


	return 0;
}
