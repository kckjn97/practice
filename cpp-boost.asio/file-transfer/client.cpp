#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <cstdio>
#include "protocol.hpp"
#include <cstring>
#include <filesystem>

using boost::asio::ip::tcp;

int main(int argc, char* argv[]){
	if (argc != 4){
		std::cerr << "Usage: client <HOST> <PORT> <FILE>" << std::endl;
		return 1;
	}

	try {
		std::string host(argv[1]);
		std::string port(argv[2]);
		std::string file_path(argv[3]);

		boost::asio::io_context io_context;
		tcp::resolver resolver(io_context);
		tcp::resolver::results_type endpoints = resolver.resolve({host, port});

		tcp::socket socket(io_context);
		boost::asio::connect(socket, endpoints);

		boost::array<char, 128> command_buf;
		boost::system::error_code error;

		FILE* fp = fopen(file_path.c_str(), "r");
		if(!fp){
			std::cout << "file path error: " << file_path.c_str() << "\n";
			perror("error");
			exit(-1);
		}

		fseek(fp, 0, SEEK_END);
		size_t file_size = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		std::string filename = std::__fs::filesystem::path(file_path).filename();
		SendProtocol send_protocol(filename, file_size);

		memcpy(command_buf.c_array(), (void*) &send_protocol, sizeof(send_protocol));
		boost::asio::write(socket, boost::asio::buffer(command_buf, sizeof(send_protocol)));

		char reply[1024] = {0};
		size_t reply_length = socket.read_some(boost::asio::buffer(reply), error);
		std::string str_reply(reply);
		if(str_reply != "ok"){
			std::cout << "response error\n";
			exit(-1);
		}
		std::cout << "file transfer start: send\n";

		char file_buf[1024*1024*2];
		while(!feof(fp)){
			size_t c = ftell(fp);
			std::cout << c << "\n";
			size_t length = fread(file_buf, 1, 1024*1024*2, fp);
			boost::asio::write(socket, boost::asio::buffer(file_buf, length));
			std::cout << length << " transfer\n";

		}

	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}