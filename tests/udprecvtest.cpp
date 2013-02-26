#include <iostream>
#include <cstdlib>
#include <string>
#include "NetSocket++/NetSocketPP.h"
using namespace std;

int main() {
try {
NetSocketPP::ServerSocket socket("127.0.0.1", "4950", "UDP");
socket.recv(0);
cout << "Receiver got: " << socket.get() << endl;
return EXIT_SUCCESS;
} catch (NetSocketPP::NetworkException &exc) {
	cerr << "Network exception in main function: " << exc.what() << endl;
	return 2;	
	} catch (NetSocketPP::SocketException &exc) {
	cerr << "Library exception in main function: " << exc.what() << endl;
	return 1;	
	} 
}
