#include<cstdlib>
#include<fstream>
#include<iostream>
#include<boost/asio.hpp>
#include<thread>
#include<queue>

using boost::asio::ip::tcp;
using namespace std;

class Master
{
	tcp::socket sock;
	enum { max_length = 1024 };
public:
	Master(boost::asio::io_context& io_context, const string& host, const string& port)
	: sock(io_context) {
		tcp::resolver resolver(io_context);
		boost::asio::connect(sock, resolver.resolve({host, port}));
	}

	void Send(string msg){
		size_t msg_length = msg.length();
		boost::asio::write(sock, boost::asio::buffer(msg, msg_length));
	}

	string Receive(){
		char reply[max_length] = {0};
		size_t reply_length = boost::asio::read(sock, boost::asio::buffer(reply, max_length));
		return string(reply);
	}
};


void MasterThread(string ip, string port, queue<string>* ptr_taskq){
	static mutex mtx;
	boost::asio::io_context io_context;
	Master master(io_context, ip, port);

	mtx.lock();
	while(ptr_taskq->size()) {
		string task = ptr_taskq->front();
		ptr_taskq->pop();
		mtx.unlock();
		master.Send(task);
		string res = master.Receive();
		mtx.lock();
		cout << res << "\n";
	}
	mtx.unlock();
}

int main(int argc, char* argv[]){
	try{
		if(argc != 3){
			cerr << "Usage: Master <network config file> <task list>" << endl;
			return 1;
		}
		ifstream network_conf_file(argv[1]);
		if(!network_conf_file.is_open()){
			cerr << "network config file path error" << endl;
			return 1;
		}
		ifstream task_list_file(argv[2]);
		if(!network_conf_file.is_open()){
			cerr << "task list file path error" << endl;
			return 1;
		}

		vector<pair<string, string>> node_list;
		queue<string> taskq;
		string line;
		while(getline(network_conf_file, line)){
			string ip, port;
			istringstream ss(line);
			getline(ss, ip, ':');
			getline(ss, port, ':');
			node_list.push_back({ip, port});
		}

		while(getline(task_list_file, line))
			taskq.push(line);

		vector<thread*> threads;
		for(auto& it: node_list) {
			thread *t = new thread(MasterThread, it.first, it.second, &taskq);
			threads.push_back(t);
		}

		for(auto& t: threads) {
			t->join();
			delete t;
		}

	}catch(exception& e){
		cerr<<"Exception: " << e.what() << endl;
	}

	return 0;
}

