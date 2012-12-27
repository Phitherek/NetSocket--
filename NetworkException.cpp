#include <iostream>
#include <cstdlib>
#include "NetworkException.h"
using namespace NetSocket;

NetworkException::NetworkException(std::string cmd, std::string msg) {
	_cmd = cmd;
	_msg = msg;
}

NetworkException::~NetworkException() throw() {
_cmd = "";
_msg = "";
}

const char* NetworkException::what() const throw() {
	std::string str = "";
	str += _cmd;
	str += " failed in NetSocket++: ";
	str += _msg;
	return str.c_str();
}
