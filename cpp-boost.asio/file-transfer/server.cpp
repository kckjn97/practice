#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "protocol.hpp"

using boost::asio::ip::tcp;

class Server {
	boost::asio::io_context io_context;
	std::unique_ptr<tcp::acceptor> ptr_acceptor;
	std::unique_ptr<tcp::socket> ptr_socket;
	boost::system::error_code error;
	//uuid ...

	size_t _GetFileSize(FILE* fp) {
		long cursor = ftell(fp);
		fseek(fp, 0, SEEK_END);
		size_t file_size = ftell(fp);
		fseek(fp, cursor, SEEK_SET);
		return file_size;
	}

public:
	Server(const int port){
		try {
			ptr_acceptor = std::make_unique<tcp::acceptor>(io_context, tcp::endpoint(tcp::v4(), port));
			ptr_socket = std::make_unique<tcp::socket>(io_context);
			ptr_acceptor->accept(*ptr_socket);
			std::cout << "connected\n";
		}catch(std::exception& e){
			std::cerr << e.what() << std::endl;
		}
	}

	~Server(){
		io_context.stop();
		ptr_acceptor->close();
		ptr_socket->close();
	}

	void ReceiveFile(std::string file_name, size_t file_size){
		std::cout << "File Receive: " << file_name << " (" << file_size << " bytes)\n";

		char file_buf[FILE_BUF_SIZE];
		FILE* fp = fopen(file_name.c_str(), "w+");
		if(!fp){
			std::cerr << "File Open Error " << file_name << "\n";
			return;
		}

		size_t remain = file_size;
		while(remain) {
			//size_t length = ptr_socket->read_some(boost::asio::buffer(file_buf), error);
			size_t length = remain > FILE_BUF_SIZE ? FILE_BUF_SIZE : remain;
			boost::asio(*ptr_socket, boost::asio::bufer(file_buf, length));
			fwrite(file_buf, 1, length, fp);
			remain -= length;
		}
		fclose(fp);
		std::cout << "File Receive Completed\n";
	}

	void SendFile(std::string file_name){
		std::cout << "File Send: " << file_name << "\n";
		char file_buf[FILE_BUF_SIZE];
		//memset(file_buf, 0x00, FILE_BUF_SIZE);

		size_t file_size = 0;
		FILE* fp = fopen(file_name.c_str(), "r");
		if(!fp){
			std::cerr << "File Open Error " << file_name << "\n";
			return;
		}

		while(!feof(fp)) {
			size_t length = fread(file_buf, 1, FILE_BUF_SIZE, fp);
			boost::asio::write(*ptr_socket, boost::asio::buffer(file_buf, length));
			printf("send %d %d\n", length, FILE_BUF_SIZE);
			file_size += length;
		}
		fclose(fp);
		std::cout << "File Send Completed (" << file_size << ")\n";
	}

	size_t GetFileSize(std::string file_name){
		FILE* fp = fopen(file_name.c_str(), "r");
		if(!fp){
			std::cerr << "File Open Error " << file_name << "\n";
			return -1;
		}
		size_t ret = _GetFileSize(fp);
		fclose(fp);
		return ret;
	}

	void Response(Protocol& protocol){
		protocol.IncSequence();
		boost::asio::write(*ptr_socket, boost::asio::buffer(&protocol, sizeof(protocol)));
	}

	void Run(){
		char data[sizeof(Protocol)];

		try{
			while(1){
				size_t length = ptr_socket->read_some(boost::asio::buffer(data), error);
				if(error == boost::asio::error::eof){
					break;
				}else if(error){
					throw boost::system::system_error(error);
				}

				Protocol& protocol = *((Protocol*) data);
				size_t file_size = 0;

				std::string file_name = protocol.GetFileName();
				switch(protocol.GetCommand()){
					case Command::SEND_TO_SERVER: {
						size_t file_size = protocol.GetFileSize();
						Response(protocol);
						ReceiveFile(file_name, file_size);
						break;
					}
					case Command::RECEIVE_FROM_SERVER: {
						std::string file_name = protocol.GetFileName();
						assert(protocol.GetFileSize() == 0);
						size_t file_size = GetFileSize(file_name);
						protocol.SetFileSize(file_size);
						Response(protocol);
						SendFile(file_name);
						break;
					}
					default:
						assert(0);
						break;
				}
				sleep(1);
			}
		}catch(std::exception& e){
			std::cerr << "Exception in Worker: " << e.what() << std::endl;
		}
	}
};

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "Usage: <PORT>" << std::endl;
		return 1;
	}

	while(1) {
		Server server(atoi(argv[1]));
		server.Run();
	}
	return 0;
}