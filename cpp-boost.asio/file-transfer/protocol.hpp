#ifndef FILE_TRANSFER_PROTOCOL_HPP
#define FILE_TRANSFER_PROTOCOL_HPP

#include <cstring>
enum class Command: char{
	SEND_TO_SERVER,
	RECEIVE_FROM_SERVER,
	NONE
};

const size_t FILE_BUF_SIZE = 2*1024*1024UL;
const size_t MAX_FILE_NAME_SIZE = 100;


class Protocol{
	Command command;
	unsigned int sequence;
	size_t file_size;
	char file_name[MAX_FILE_NAME_SIZE + 1];

public:
	Protocol(){
		command = Command::NONE;
		sequence = 0;
		file_size = 0;
		memset(file_name, 0x00, MAX_FILE_NAME_SIZE);
	}

	Protocol(const Protocol& copy){
		memcpy(this, &copy, sizeof(Protocol));
	}

	Protocol(Command command, std::string file_name)
			: command(command)
			, file_size(0)
			, sequence(0){

	}

	Protocol(Command command, std::string file_name, size_t file_size)
	: command(command)
	, file_size(file_size){
		size_t length = (file_name.size() < MAX_FILE_NAME_SIZE) ? file_name.size() : MAX_FILE_NAME_SIZE;
		memcpy(this->file_name, file_name.c_str(), length);
		this->file_name[length] = '\0';
	}

	Command GetCommand(){
		return command;
	}

	void SetFileSize(size_t file_size){
		this->file_size = file_size;
	}

	size_t GetFileSize(){
		return file_size;
	}

	std::string GetFileName(){
		return std::string(file_name);
	}

	void IncSequence(){
		sequence++;
	}

	unsigned int GetSequnce(){
		return sequence;
	}
};

const size_t PROTOCOL_SIZE = sizeof(Protocol);
#endif //FILE_TRANSFER_PROTOCOL_HPP
