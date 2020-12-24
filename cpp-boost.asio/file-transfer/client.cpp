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

	char command_buf[COMMAND_BUF_SIZE];

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

	void SendCommand(){

	}

	void ReceiveResponse(){

	}

	void SendData(char* buf, size_t size){
		try {
			boost::asio::write(*ptr_socket, boost::asio::buffer(buf, size));
		}catch (std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}

	char* ReceiveData(){
		size_t reply_length = ptr_socket->read_some(boost::asio::buffer(command_buf), error);
		command_buf[reply_length] = '\0';
		return command_buf;
	}

	void SendFile(std::string file_path){
		char file_buf[FILE_BUF_SIZE];
		FILE* fp = fopen(file_path.c_str(), "r");

		if(!fp){
			perror("File Open Error");
			exit(-1);
		}

		size_t file_size = _GetFileSize(fp);
		std::string filename = file_path.substr(file_path.find_last_of("/\\") + 1);

		SendProtocol send_protocol(filename, file_size);
		memcpy(command_buf, (void*) &send_protocol, sizeof(send_protocol));
		SendData(command_buf, sizeof(send_protocol));

		std::string response = ReceiveData();
		if(response != "OK"){
			std::cerr << "Response Error: " << response << "\n";
			exit(-1);
		}

		std::cout << "File Send: " << file_path << " (" << file_size << " bytes)\n";
		while(!feof(fp)){
			size_t c = ftell(fp);
			size_t length = fread(file_buf, 1, FILE_BUF_SIZE, fp);
			SendData(file_buf, length);
//			std::cout << length << " transfer\n";
		}
		fclose(fp);

		std::cout << "File Send: Completed\n";
	}

	void ReceiveFile(){

	}
};

int main(int argc, char* argv[]){
	if (argc != 4){
		std::cerr << "Usage: client <HOST> <PORT> <FILE>" << std::endl;
		return 1;
	}

	std::string host(argv[1]);
	std::string port(argv[2]);
	std::string file_path(argv[3]);

	Client client(host, port);
	client.SendFile(file_path);

	return 0;
}