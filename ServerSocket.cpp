#include "ServerSocket.h"
#include <iostream>
#include <cstdlib>
using namespace NetSocketPP;

ServerFunctionArgs::ServerFunctionArgs() {
_tab = NULL;
_size = 0;
}

ServerFunctionArgs::ServerFunctionArgs(ServerFunctionArgs& sfa) {
if(sfa._tab == NULL) {
_tab = NULL;
_size = 0;
} else {
_size = sfa._size;
_tab = new std::string[_size];
for(unsigned int i = 0; i < _size; i++) {
_tab[i] = sfa._tab[i];
}
}
}

ServerFunctionArgs::~ServerFunctionArgs() {
_size = 0;
if(_tab != NULL) {
delete[] _tab;
}
_tab = NULL;
}

void ServerFunctionArgs::addArgument(std::string arg) {
unsigned int newSize = _size+1;
std::string* newTab = NULL;
newTab = new std::string[newSize];
for(unsigned int i = 0; i < _size; i++) {
newTab[i] = _tab[i];	
}
newTab[newSize-1] = arg;
_size = newSize;
delete[] _tab;
_tab = newTab;
}

std::string ServerFunctionArgs::getArgument(unsigned int idx) {
if(idx >= _size) {
throw SocketException("Index out of bounds!");
} else {
return _tab[idx];
}	
}

std::string ServerFunctionArgs::operator[](unsigned int idx) {
return getArgument(idx);	
}

ServerSocket::ServerSocket(std::string host, std::string service, std::string protocol): NetSocket(host, service, protocol) {
	int bindret = bind(_descriptor, _servinfo->ai_addr, _servinfo->ai_addrlen);
	if(bindret == 1) {
		throw NetworkException("bind", strerror(errno));
	}
}
ServerSocket::~ServerSocket() {
close(_newDescriptor);	
}

void ServerSocket::startServer(ServerFunctionArgs& functionOutput ,ServerFunctionArgs& (*serverMain)(ServerFunctionArgs, ServerSocket*), ServerFunctionArgs functionInput, bool infinite, unsigned int iternum, int connectionLimit) {
	if(_protocol == "UDP") {
	throw SocketException("startServer() works only with TCP! Use send() and recv() methods to transfer data via UDP!");	
	}
	int lr = listen(_descriptor, connectionLimit);
	if(lr == -1) {
	throw NetworkException("listen", strerror(errno));	
	}
	_sa.sa_handler = sigchld_handler;
	sigemptyset(&_sa.sa_mask);
	_sa.sa_flags = SA_RESTART;
	if(sigaction(SIGCHLD, &_sa, NULL) == -1) {
	throw SocketException("Sigaction failed!");	
	}
	if(infinite == true) {
	while(true) {
	_newDescriptor = accept(_descriptor, (sockaddr*)&_their_addr, &_addr_size);
	if(_newDescriptor == -1) {
	throw NetworkException("accept", strerror(errno));	
	}
	if(!fork()) {
	close(_descriptor);
	functionOutput = serverMain(functionInput, this);	
	}
	}
	} else {
	for(unsigned int i = 0; i < iternum; i++) {
	_newDescriptor = accept(_descriptor, (sockaddr*)&_their_addr, &_addr_size);
	if(_newDescriptor == -1) {
	throw NetworkException("accept", strerror(errno));	
	}
	if(!fork()) {
	close(_descriptor);
	functionOutput = serverMain(functionInput, this);	
	}
	}	
	}
}

int ServerSocket::send(std::string msg, int flags) {
	if(_protocol == "TCP") {
		int sr = ::send(_newDescriptor, msg.c_str(), msg.length(), flags);
		if(sr == -1) {
		throw NetworkException("send", strerror(errno));	
		}
		return sr;
	} else if(_protocol == "UDP") {
		int sr = ::sendto(_descriptor, msg.c_str(), msg.length(), flags, _servinfo->ai_addr, _servinfo->ai_addrlen);
		if(sr == -1) {
		throw NetworkException("sendto", strerror(errno));	
		}
		return sr;
	}
	return -1;
}

int ServerSocket::recv(int flags) {
	memset(&_buf[0], 0, sizeof(_buf));
	if(_protocol == "TCP") {
		int rr = ::recv(_newDescriptor, _buf, 99999, flags);
		if(rr == -1) {
		throw NetworkException("recv", strerror(errno));	
		} else if(rr == 0) {
		throw NetworkException("recv", "Remote end has closed the connection.");	
		}
		return rr;	
	} else if(_protocol == "UDP") {
		int rr = ::recvfrom(_descriptor, _buf, 99999, flags, (sockaddr*)&_their_addr, &_addr_size);
		if(rr == -1) {
		throw NetworkException("recvfrom", strerror(errno));	
		} else if(rr == 0) {
		throw NetworkException("recvfrom", "Remote end has closed the connection.");	
		}
		_buf[rr] = '\0';
		return rr;
	}
	return -1;
}

std::string ServerSocket::get() {
	return static_cast<std::string>(_buf);
}
