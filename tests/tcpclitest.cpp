#include <iostream>
#include <cstdlib>
#include <string>
#include "NetSocket++/NetSocketPP.h"
using namespace std;

int main() {
cout << "Message to send to server: " << endl;
string msg;
cin >> msg;
try {
NetSocketPP::ClientSocket socket("127.0.0.1", "3490", "TCP");
socket.recv(0);
cout << "Server said: " << socket.get() << endl;
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
