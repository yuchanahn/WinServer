#pragma once
#include <functional>
#include <map>
#include <vector>
#include <memory>


enum Class;
struct Base;
class session;

class PackData
{
	int size;
public:
	char * data;

	template <typename T>
	auto Get() {
		return ((T*)m_GetBase(data))->UnPack();
	}
	template <typename T, typename T2>
	void Get(T2 * target) {
		((T*)m_GetBase(data))->UnPackTo(target);
	}




	Base* m_GetBase(char * data_);

	PackData(int len) {
		size = len;
		data = new char[len];
	};
	~PackData() {
		delete[] data;
	};

private:
};


class ReadManager
{
public:
	ReadManager();
	~ReadManager();
	static void Read(char data_[1024], size_t,std::shared_ptr<session>);
	static int byteToInt(char data[], int idx);
	static int buffToInteger(char * buffer);
	static std::map<Class, std::function<void (PackData*,std::shared_ptr<session>) >> ReadSome;
};

