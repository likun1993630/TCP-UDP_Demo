#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
#include <vector>
#include <iostream>
#include <ctime>
const clock_t delay = CLOCKS_PER_SEC;

using namespace std;
using namespace boost::asio;

int main()
{
	try
	{
		typedef ip::tcp::acceptor acceptor_type;
		typedef ip::tcp::endpoint endpoint_type;
		typedef ip::tcp::socket socket_type;

		cout << "server start." << endl;
		io_service io;
		acceptor_type acceptor(io, endpoint_type(ip::tcp::v4(),12002)); //在12002端口监听
		cout << acceptor.local_endpoint().address() << endl;
		socket_type sock(io);
		acceptor.accept(sock); //阻塞等待对象
		std::vector<uint8_t> remsg(100,0);
		sock.receive(buffer(remsg));
		cout << "client:";
		cout << sock.remote_endpoint().address() << endl;
		cout << "reveived: " << unsigned(remsg[0]) << ", " << unsigned(remsg[1]) <<  endl;
		
		for ( ; ; )
		{
			std::vector<uint8_t> msg = {0xdc, 0x0e, 0xa1, 0xf1};
				
			cout<< "the size of msg is:" << msg.size() << endl;
			clock_t start = clock();
	    	while(clock() - start < delay*0.01){};

			sock.send(buffer(msg));
		}

	}
	catch(std::exception& e)
	{
		cout << e.what() << endl;
	}


	return 0;
}