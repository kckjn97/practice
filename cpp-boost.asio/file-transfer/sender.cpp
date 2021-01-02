#include "client.hpp"

int main(int argc, char* argv[]){
	if (argc != 5){
		std::cerr << "Usage: client <HOST> <PORT> <LOCAL_FILE> <SERVER_FILE>" << std::endl;
		return 1;
	}

	std::string host(argv[1]);
	std::string port(argv[2]);
	std::string local_file_path(argv[3]);
	std::string server_file_name(argv[4]);

	Client client(host, port);
	client.SendFile(local_file_path, server_file_name);
	return 0;
}