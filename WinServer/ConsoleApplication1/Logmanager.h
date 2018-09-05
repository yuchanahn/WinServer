#pragma once
#include <spdlog.h>

#define SPDLOG_TRACE_ON
#define SPDLOG_DEBUG_ON

#include <iostream>
#include <memory>


namespace spd = spdlog;
class LogManager
{
	static LogManager* instance;
	std::shared_ptr<spdlog::logger> async_file = spd::daily_logger_st("async_file_logger", "logs/async_log.txt");
	std::shared_ptr<spdlog::logger> console = spd::stdout_color_mt("console");



public:
	static LogManager* GetInstance() {
		if (instance == nullptr) {
			instance = new LogManager();
		}
		return instance;
	}

	std::shared_ptr<spdlog::logger> Console() {
		return console;
	}

	void Log(std::string text) {
		size_t q_size = 4096; //queue size must be power of 2
		spdlog::set_async_mode(q_size);
		async_file->info(text.c_str());
	}
};


LogManager* LogManager::instance = nullptr;