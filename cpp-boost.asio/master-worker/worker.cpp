#include<cstdlib>
#include<iostream>
#include<boost/asio.hpp>

using namespace std;
using boost::asio::ip::tcp;

class Worker
{
	enum{ BUF_SIZE = 1024};
	boost::asio::io_context &io_context_;
	tcp::acceptor acceptor_;

public:
	Worker(boost::asio::io_context& io_context, short port)
			: io_context_(io_context), acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
	{
		char data[BUF_SIZE];
		memset(data, 0x00, BUF_SIZE);

		while(1){
			tcp::socket sock(io_context_);
			acceptor_.accept(sock);

			try{
				while(1){
					boost::system::error_code error;
					size_t length = sock.read_some(boost::asio::buffer(data), error);
					if(error == boost::asio::error::eof){
						break;
					}else if(error){
						throw boost::system::system_error(error);
					}
					data[length] = NULL;
					cout << "("<< port << ") Message from Master: " << data << endl;

					string res = Run(data);

					boost::asio::write(sock, boost::asio::buffer(res.c_str(), BUF_SIZE));
				}
			}catch(exception& e){
				cerr << "Exception in Worker: " << e.what() << endl;
			}
		}
	}

	string Run(string data){
		return "completed: " + data;
	}

private:

};

int main(int argc, char* argv[]){
	try{
		if(argc != 2){
			cerr << "Usage: Worker <port>" << endl;
			return 1;
		}
		boost::asio::io_context io_context;
		Worker worker(io_context, atoi(argv[1]));

	}catch(exception& e){
		cerr << "Exception: " << e.what() << endl;
	}
	return 0;
}
