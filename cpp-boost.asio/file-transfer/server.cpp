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

	void SendData(){

	}

	void ReceiveCommand(){

	}

	void SendResponse(){
		std::string response = "OK";
		boost::asio::write(*ptr_socket, boost::asio::buffer(response.c_str(), response.size()));
	}

	void RecevieData(){

	}

	void SendFile(){

	}

	void ReceiveFile(std::string file_name, size_t file_size){
		std::cout << "File Receive: " << file_name << " (" << file_size << " bytes)\n";
		size_t cursor = 0;
		char file_buf[FILE_BUF_SIZE];
		FILE* fp = fopen(file_name.c_str(), "w+");
		if(!fp){
			std::cerr << "File Open Error " << file_name << "\n";
			return;
		}

		while(cursor < file_size) {
			size_t length = ptr_socket->read_some(boost::asio::buffer(file_buf), error);
			fwrite(file_buf, length, 1, fp);
			cursor += length;
		}
		fclose(fp);
		std::cout << "File Receive Completed\n";
	}

	void Run(){
		char data[COMMAND_BUF_SIZE];
		memset(data, 0x00, COMMAND_BUF_SIZE);

		try{
			while(1){
				size_t length = ptr_socket->read_some(boost::asio::buffer(data), error);
				if(error == boost::asio::error::eof){
					break;
				}else if(error){
					throw boost::system::system_error(error);
				}

				Protocol* protocol = (Protocol*) data;
				switch(protocol->GetCommand()){
					case Command::SEND:
						SendProtocol* send_protocol = (SendProtocol*) protocol;

						SendResponse();

						std::string file_name = send_protocol->GetFileName();
						size_t file_size = send_protocol->GetFileSize();

						ReceiveFile(file_name, file_size);
						break;
				}
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