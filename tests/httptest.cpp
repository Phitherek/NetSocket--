#include <iostream>
#include <cstdlib>
#include <string>
#include "NetSocket++/NetSocketPP.h"
using namespace std;

int main() {
try {
NetSocketPP::HTTPClientSocket socket("phitherek.mooo.com", "http", "/");
NetSocketPP::HTTPReply reply;
cout << "Sent request: " << endl << socket.getRequest() << endl << "Request end" << endl;
reply = socket.getReply();
cout << "Read content: " << endl << reply.getContent() << endl;
return EXIT_SUCCESS;
} catch (NetSocketPP::NetworkException &exc) {
	cerr << "Network exception in main function: " << exc.what() << endl;
	return 2;	
	} catch (NetSocketPP::SocketException &exc) {
	cerr << "Library exception in main function: " << exc.what() << endl;
	return 1;	
	} 
}
