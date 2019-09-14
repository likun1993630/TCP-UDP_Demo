//g++ -g udp_client.cpp -o udp_client -lboost_system
//
 
#include <iostream>
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

#include "mags.h"
#include <ctime>
 
using namespace std;
using namespace boost::asio;
 
int main(){
    try{
        cout << "udp client start ......" << endl;
        io_service ios;
        ip::udp::endpoint send_ep(ip::address::from_string("127.0.0.1"), 6699);
 
        ip::udp::socket sock(ios);
        sock.open(ip::udp::v4());

        double i = 0.0;

        mags buf[1];

        clock_t delay = CLOCKS_PER_SEC;

        while(i < 10)
        {

	    	buf[0].x = i+0.1;
	    	buf[0].y = i+0.2;
	    	buf[0].z = i+0.3;
	    	buf[0].rx = i+0.4;
	    	buf[0].ry = i+0.5;
	    	buf[0].rz = i+0.6;

	        clock_t start = clock();
	    	while(clock() - start < delay){};
	    	sock.send_to(buffer(buf), send_ep);

	        //vector<char> v(100, 0); //将v初始化为100个为0的char向量
	        //ip::udp::endpoint recv_ep;
	        //sock.receive_from(buffer(v), recv_ep);
	        //cout << "recv from " << recv_ep.address() << endl;
	        //cout << &v[0] << endl;

	        i+=1;
        }
 
        
    }
    catch(exception& e){
        cerr << e.what() << endl;
    }
    return 0;
}
