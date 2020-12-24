#ifndef FILE_TRANSFER_PROTOCOL_HPP
#define FILE_TRANSFER_PROTOCOL_HPP

#include <cstring>
enum class Command: char{
	SEND,
	RECEIVE
};

const size_t FILE_BUF_SIZE = 2*1024*1024UL;
const size_t COMMAND_BUF_SIZE = 128;

class Protocol{
protected:
	Command command;

public:
	Protocol(Command command)
	: command(command){
	}

	Command GetCommand(){
		return command;
	}
};

class SendProtocol: public Protocol{
	size_t file_size;
	char filename[32];

public:
	SendProtocol(const std::string& filename, const size_t file_size)
	: Protocol(Command::SEND)
	, file_size(file_size) {
		size_t length = (filename.size() < 31) ? filename.size() : 31;
		memcpy(this->filename, filename.c_str(), length);
		this->filename[31] = '\0';
	}

	size_t GetFileSize(){
		return file_size;
	}

	std::string GetFileName(){
		return std::string(filename);
	}
};

class ReceiveProtocol: public Protocol{
	size_t file_size;
	char filename[32];

public:
	ReceiveProtocol(const std::string& filename, const size_t file_size)
			: Protocol(Command::RECEIVE)
			, file_size(file_size) {
		size_t length = (filename.size() < 31) ? filename.size() : 31;
		memcpy(this->filename, filename.c_str(), length);
		this->filename[31] = '\0';
	}

	size_t GetFileSize(){
		return file_size;
	}

	std::string GetFileName(){
		return std::string(filename);
	}
};
#endif //FILE_TRANSFER_PROTOCOL_HPP
