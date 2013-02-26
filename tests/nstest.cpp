#include <iostream>
#include <cstdlib>
#include "../NetSocketPP.h"
using namespace std;

int main() {
NetSocketPP::NetSocket ns("phitherek.mooo.com", "http", "TCP");
cout << "Host IP: " << ns.getIP() << endl;
return EXIT_SUCCESS;
}
