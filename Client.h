#pragma once

#define OSCPKT_OSTREAM_OUTPUT
#include "oscpkt.hh"
#include "udp.hh"

// #pragma comment(lib,"ws2_32.lib") //Winsock Library

using std::cout;
using std::cerr;

using namespace oscpkt;

const int PORT_NUM = 12345;


//#define SERVER "127.0.0.1"  //ip address of udp server
//#define BUFLEN 512  //Max length of buffer
//#define PORT 12345   //The port on which to listen for incoming data

class Client {
	
	public:
		void sendTheUDP(float x, float y, float z);

};
