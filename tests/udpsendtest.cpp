#include <iostream>
#include <cstdlib>
#include <string>
#include "NetSocket++/NetSocketPP.h"
using namespace std;

int main() {
cout << "Message to send to receiver: " << endl;
string msg;
cin >> msg;
try {
NetSocketPP::ClientSocket socket("127.0.0.1", "4950", "UDP");
socket.send(msg, 0);
return EXIT_SUCCESS;
} catch (NetSocketPP::NetworkException &exc) {
	cerr << "Network exception in main function: " << exc.what() << endl;
	return 2;	
	} catch (NetSocketPP::SocketException &exc) {
	cerr << "Library exception in main function: " << exc.what() << endl;
	return 1;	
	} 
}
