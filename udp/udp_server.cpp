//g++ -g udp_server.cpp -o udp_server -lboost_system
//
 
#include <iostream>
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

#include "mags.h"
 
using namespace std;
using namespace boost::asio;
 
int main(){
    try{
        cout << "udp server start ......" << endl;
        io_service ios;
 
        ip::udp::socket sock(ios, ip::udp::endpoint(ip::udp::v4(), 6699));
 
        while(true){
            mags buf[1];
            ip::udp::endpoint ep;
            boost::system::error_code ec;
            sock.receive_from(buffer(buf), ep, 0, ec);

            // visual
            cout << "receive :\n" << 
            	"x:\t"<< buf[0].x << "\ny:\t"<< buf[0].y <<"\nz:\t" << buf[0].z <<
            	"\nroll:\t"<< buf[0].rx << "\npitch:\t"<< buf[0].ry <<"\nyaw:\t" << buf[0].rz << endl;
            cout << endl;
 
            if(ec && ec!=error::message_size){
                throw boost::system::system_error(ec);
            }
 
            //cout << "send to " << ep.address() << endl;
            sock.send_to(buffer("hello asio udp"), ep);
        }
    }
    catch(std::exception& e){
        cout << e.what() << endl;
    }
    return 0;
}
