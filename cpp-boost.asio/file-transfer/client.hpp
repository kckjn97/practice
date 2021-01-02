#ifndef FILE_TRANSFER_CLIENT_HPP
#define FILE_TRANSFER_CLIENT_HPP

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <cstdio>
#include "protocol.hpp"
#include <cstring>

using boost::asio::ip::tcp;

class Client{
	boost::asio::io_context io_context;
	std::unique_ptr<tcp::resolver> ptr_resolver;
	std::unique_ptr<tcp::socket> ptr_socket;
	boost::system::error_code error;
	unsigned int sequence;

	char command_buf[sizeof(Protocol)];

	size_t _GetFileSize(FILE* fp) {
		long cursor = ftell(fp);
		fseek(fp, 0, SEEK_END);
		size_t file_size = ftell(fp);
		fseek(fp, cursor, SEEK_SET);
		return file_size;
	}

public:
	Client(const std::string host, const std::string port){
		try{
			ptr_resolver = std::make_unique<tcp::resolver>(io_context);
			tcp::resolver::results_type endpoints = ptr_resolver->resolve({host, port});
			ptr_socket = std::make_unique<tcp::socket>(io_context);
			boost::asio::connect(*ptr_socket, endpoints);
		}catch (std::exception& e){
			std::cerr << e.what() << std::endl;
		}
	}

	int SendCommand(Command command, std::string& file_name, size_t& file_size){
		try {
			Protocol send_protocol(command, file_name, file_size);
			Send(&send_protocol, sizeof(send_protocol));

			Protocol receive_protocol;
			size_t r = Receive(&receive_protocol, sizeof(receive_protocol));
			assert(r == sizeof(receive_protocol));
			assert(receive_protocol.GetCommand() == command);
			assert(receive_protocol.GetFileName() == file_name);

			if(command == Command::RECEIVE_FROM_SERVER)
				file_size = receive_protocol.GetFileSize();
			return 0;
		}catch (std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
		return -1;
	}

	void Send(void* buf, size_t size){
		try {
			boost::asio::write(*ptr_socket, boost::asio::buffer(buf, size));
		}catch (std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}

	size_t Receive(void* buf,  size_t size){
		try {
			//size_t length = ptr_socket->read_some(boost::asio::buffer(buf, size), error);
			size_t length = boost::asio::read(*ptr_socket, boost::asio::buffer(buf, size));
			printf("length %d %d\n", length, size);
			return size;
		}catch (std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
		return 0;
	}

	void SendFile(std::string local_file_path, std::string server_file_name){
		char file_buf[FILE_BUF_SIZE];
		FILE* fp = fopen(local_file_path.c_str(), "r");

		if(!fp){
			perror("File Open Error");
			exit(-1);
		}

		size_t file_size = _GetFileSize(fp);
		SendCommand(Command::SEND_TO_SERVER, server_file_name, file_size);

		std::cout << "File Send: " << local_file_path << " (" << file_size << " bytes)\n";
		while(!feof(fp)){
			size_t c = ftell(fp);
			size_t length = fread(file_buf, 1, FILE_BUF_SIZE, fp);
			Send(file_buf, length);
		}
		fclose(fp);

		std::cout << "File Send: Completed\n";
	}
	
	void ReceiveFile(std::string server_file_name, std::string local_file_path){
		size_t file_size;
		SendCommand(Command::RECEIVE_FROM_SERVER, server_file_name, file_size);

		char file_buf[FILE_BUF_SIZE];
		FILE* fp = fopen(local_file_path.c_str(), "w+");

		if(!fp){
			perror("File Open Error");
			exit(-1);
		}

		std::cout << "File Receive: " << server_file_name << " (" << file_size << " bytes)\n";
		size_t remain = file_size;
		while(remain){
			size_t length = remain > FILE_BUF_SIZE ? FILE_BUF_SIZE : remain;
			Receive(file_buf, length);
			fwrite(file_buf, 1, length, fp);
			remain -= length;
		}
		fclose(fp);

		std::cout << "File Receive: Completed\n";
	}
};
#endif //FILE_TRANSFER_CLIENT_HPP
