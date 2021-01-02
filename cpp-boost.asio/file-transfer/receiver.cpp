#include "client.hpp"

int main(int argc, char* argv[]){
	if (argc != 5){
		std::cerr << "Usage: client <HOST> <PORT> <LOCAL_FILE> <SERVER_FILE>" << std::endl;
		return 1;
	}

	std::string host(argv[1]);
	std::string port(argv[2]);
	std::string server_file_name(argv[3]);
	std::string local_file_path(argv[4]);

	Client client(host, port);
	client.ReceiveFile(server_file_name, local_file_path);
	return 0;
}