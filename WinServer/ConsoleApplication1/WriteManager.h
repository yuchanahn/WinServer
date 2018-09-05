#pragma once
#include <iostream>
#include "Base_generated.h"
#include "ClientSession.h"

template <typename T , typename T2>
class WriteManager
{
	
public:
	T2 * wdata;

	WriteManager() {
		wdata = new T2();
	}
	~WriteManager() {}

	void Write(std::shared_ptr<session> client) {
		flatbuffers::FlatBufferBuilder fbb;
		flatbuffers::Offset<T> orc = T::Pack(fbb, wdata);
		fbb.Finish(orc);
		int len = fbb.GetSize(); 

		client->do_write((char*)fbb.GetBufferPointer(),len);
	}

	void Write() {
		flatbuffers::FlatBufferBuilder fbb;
		flatbuffers::Offset<T> orc = T::Pack(fbb, wdata);
		fbb.Finish(orc);
		int len = fbb.GetSize();

		for (auto i : session::InputSession) 
		{
			i.second->do_write((char*)fbb.GetBufferPointer(), len);
		}
	}

};

