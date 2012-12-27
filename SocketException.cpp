#include <iostream>
#include <cstdlib>
#include "SocketException.h"
using namespace NetSocket;

SocketException::SocketException(std::string msg) {
_msg = msg;	
}

SocketException::~SocketException() throw() {
_msg = "";	
}

const char* SocketException::what() const throw() {
std::string str = "";
str += "Failure occured in NetSocket++: ";
str += _msg;
return str.c_str();
}
