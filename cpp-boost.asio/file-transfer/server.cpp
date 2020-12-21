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

	void Run(){
		const size_t BUF_SIZE = 1024;
		char data[BUF_SIZE];
		memset(data, 0x00, BUF_SIZE);

		try{
			while(1){
				boost::system::error_code error;
				size_t length = ptr_socket->read_some(boost::asio::buffer(data), error);
				if(error == boost::asio::error::eof){
					break;
				}else if(error){
					throw boost::system::system_error(error);
				}

				Protocol* protocol = (Protocol*) data;
				if(protocol->GetCommand() == Command::SEND) {
					std::cout << "Send\n";
					SendProtocol* send_protocol = (SendProtocol*) protocol;
					std::cout << "file size: "<<send_protocol->GetFileSize() << "\n";
					std::cout << "file name: "<<send_protocol->GetFileName() << "\n";

					std::string response = "ok";
					boost::asio::write(*ptr_socket, boost::asio::buffer(response.c_str(), response.size()));
					std::cout << "file transfer start: receive\n";

					size_t cursor = 0;
					char file_buf[1024*1024*2];
					const char* filename = send_protocol->GetFileName().c_str();
					FILE* fp = fopen(filename, "w+");
					if(!fp){
						std::cout << "file open error " << filename << "\n";
						break;
					}

					while(cursor < send_protocol->GetFileSize()) {
						size_t length = ptr_socket->read_some(boost::asio::buffer(file_buf), error);
						fwrite(file_buf, length, 1, fp);
						cursor += length;
					}
					fclose(fp);
					std::cout << cursor << " file transfer complete\n";
				}
				else
					std::cout << "Etc\n";
//				data[length] = NULL;
//				std::cout << "Message from Master: " << data << std::endl;
//
//				std::string res = std::string("response: ") + data;
//
//				boost::asio::write(*ptr_socket, boost::asio::buffer(res.c_str(), BUF_SIZE));
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