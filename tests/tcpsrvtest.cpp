#include <iostream>
#include <cstdlib>
#include <string>
#include "NetSocket++/NetSocketPP.h"
using namespace std;

NetSocketPP::ServerFunctionArgs& serverMain(NetSocketPP::ServerFunctionArgs args, NetSocketPP::ServerSocket* sck) {
	static NetSocketPP::ServerFunctionArgs ret;
	try {
	sck->send(args[0], 0);
	sck->recv(0);
	ret.addArgument(sck->get());
	} catch (NetSocketPP::NetworkException &exc) {
	cerr << "Network exception in server function: " << exc.what() << endl;
	ret.addArgument("exception");	
	} catch (NetSocketPP::SocketException &exc) {
	cerr << "Library exception in server function: " << exc.what() << endl;
	ret.addArgument("exception");	
	}
	return ret;
}

int main() {
cout << "Server message: " << endl;
string msg;
cin >> msg;
try {
NetSocketPP::ServerSocket socket("0.0.0.0", "3490", "TCP");
NetSocketPP::ServerFunctionArgs args;
NetSocketPP::ServerFunctionArgs ret;
args.addArgument(msg);
socket.startServer(ret, serverMain, args, false, 1, 5);
cout << "Server function returned: " << ret[0] << endl;
return EXIT_SUCCESS;
} catch (NetSocketPP::NetworkException &exc) {
	cerr << "Network exception in main function: " << exc.what() << endl;
	return 2;	
	} catch (NetSocketPP::SocketException &exc) {
	cerr << "Library exception in main function: " << exc.what() << endl;
	return 1;	
	} 
}
