#include "Client.h"

void Client::sendTheUDP(float x, float y, float z) {
 
	UdpSocket sock;
	sock.connectTo("localhost", PORT_NUM);
	if (!sock.isOk()) {
		cerr << "Error connection to port " << PORT_NUM << ": " << sock.errorMessage() << "\n";
	}
	else {
		// cout << "Client started, will send packets to port " << PORT_NUM << std::endl;
		int iping = 1;
		Message msg("/righthand"); msg.pushFloat(x); msg.pushFloat(y); msg.pushFloat(z);
			PacketWriter pw;
			pw.startBundle().startBundle().addMessage(msg).endBundle().endBundle();
			bool ok = sock.sendPacket(pw.packetData(), pw.packetSize());
			cout << "Client: sent /ping " << iping++ << ", ok=" << ok << "\n";
			// wait for a reply ?
			//if (sock.receiveNextPacket(30 /* timeout, in ms */)) {
			//	PacketReader pr(sock.packetData(), sock.packetSize());
			//	Message *incoming_msg;
			//	while (pr.isOk() && (incoming_msg = pr.popMessage()) != 0) {
			//		cout << "Client: received " << *incoming_msg << "\n";
			//	}
			//}
		
		cout << "sock error: " << sock.errorMessage() << " -- is the server running?\n";
	}
	
	
	
	//   
	//struct sockaddr_in si_other;
 //   int s, slen=sizeof(si_other);
 //   char buf[BUFLEN];
 //   // char message[BUFLEN];
 //   WSADATA wsa;

 //   //Initialize winsock
 //   printf("\nInitialising Winsock...");
 //   if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
 //   {
 //       printf("Failed. Error Code : %d",WSAGetLastError());
 //       exit(EXIT_FAILURE);
 //   }
 //   printf("Initialised.\n");

 //   //create socket
 //   if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
 //   {
 //       printf("socket() failed with error code : %d" , WSAGetLastError());
 //       exit(EXIT_FAILURE);
 //   }

 //   //setup address structure
 //   memset((char *) &si_other, 0, sizeof(si_other));
 //   si_other.sin_family = AF_INET;
 //   si_other.sin_port = htons(PORT);
 //   si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

 //   //start communication

 //       // printf("Enter message : ");
 //       // strcpy_s(message,coor);

 //       //send the message
 //       if (sendto(s, coor, strlen(coor) , 0 , (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
 //       {
 //           printf("sendto() failed with error code : %d" , WSAGetLastError());
 //           exit(EXIT_FAILURE);
 //       }

 //       //receive a reply and print it
 //       //clear the buffer by filling null, it might have previously received data
 //       memset(buf,'\0', BUFLEN);
 //       //try to receive some data, this is a blocking call
 //       if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
 //       {
 //           printf("recvfrom() failed with error code : %d" , WSAGetLastError());
 //           exit(EXIT_FAILURE);
 //       }

 //       puts(buf);
 //   

 //   closesocket(s);
 //   WSACleanup();

}
