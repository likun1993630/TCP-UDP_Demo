#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
#include <vector>
#include <iostream>
#include <cstdint>
#include <typeinfo>
#include <ctime>

using namespace std;
using namespace boost::asio;

const clock_t delay = CLOCKS_PER_SEC;

int main()
{
	try
	{
		typedef ip::tcp::endpoint endpoint_type;
		typedef ip::tcp::socket socket_type;
		typedef ip::address address_type;

		cout << "client start." << endl;

		io_service io;

		socket_type sock(io);
		endpoint_type ep(address_type::from_string("127.0.0.1"), 12002);

		sock.connect(ep);

		std::vector<uint8_t> set_filter_cmd =
          {0xaf, 0xfe, 0xc0, 0xc2,
           0x00, 0x00, 0x00, 0x00,
           0x00, 0x00, 0x00, 0x08,
           0x00, 0x00, 0x20, 0x10,
           0x00, 0x00, 0x00, 0x00,
           0x00, 0x00, 0x00, 0x00,
           0x00, 0x05, 0x00, 0x02,
           0x00, 0x00, 0xff, 0xff};

        sock.send(buffer(set_filter_cmd));

    	
    	int count = 1;
        for(;;)
        {	
        	cout << "count : " << count << endl;

        	clock_t start = clock();
	    	while(clock() - start < delay){};

			cout <<"the size of data in socket buffer: " <<sock.available() << endl; //获取可读取的字节数
			vector<uint8_t> buf;
			buf.resize(sock.available(),0);
			// vector<uint8_t> buf;
			// buf.reserve(2000);
			sock.receive(buffer(buf));

			cout << "receive from ip : " << sock.remote_endpoint().address() << endl;

/*			cout << "received: " << endl;
			int pcount = 0;
			for (int i = 0; i < buf.size(); ++i)
			{
				pcount = pcount +1;
				if (pcount == 16)
				{
					cout << endl;
					pcount = 0;
				}
				else
					cout << hex << unsigned(buf[i]) << " ";
			}*/
			cout << "received data size: " << buf.size() << endl;

			io.reset();
			count = count+1;
        }
	}

	catch(std::exception& e)
	{
		cout << e.what() << endl;
	}

	return 0;
}
