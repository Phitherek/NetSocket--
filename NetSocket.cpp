#include <iostream>
#include <cstdlib>
#include "NetSocket.h"
#include "NetworkException.h"
#include "SocketException.h"
using namespace NetSocket;

NetSocket::NetSocket(std::string host = NULL, std::string service, std::string protocol) {
_yes=1;
memset(&_hints, 0, sizeof(_hints));
_hints.ai_family = AF_UNSPEC;
if(protocol == "TCP") {
_hints.ai_socktype = SOCK_STREAM;
} else if(protocol == "UDP") {
_hints.ai_socktype = SOCK_DGRAM;	
} else {
	std::string errmsg = "";
	errmsg = "Protocol not known: ";
	errmsg += protocol;
	throw SocketException(errmsg);	
}
_status = getaddrinfo(host.c_str(), service.c_str(), &_hints, &_servinfo);
if(_status != 0) {
throw NetworkException("getaddrinfo", gai_strerror(_status));	
}
addrinfo *p;
for(p = _servinfo; p != NULL; p = p->ai_next) {
	_descriptor = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
	if(_descriptor == -1) {
	continue;	
	}
	break;
}
if(p == NULL) {
throw NetworkException("socket", strerror(errno));	
}
inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), _caddr, sizeof(_caddr));
_servinfo = p;
if(protocol = "TCP") {
setsockopt(_descriptor, SOL_SOCKET, SO_REUSEADDR, &_yes, sizeof(int));
int bindret = bind(_descriptor, _servinfo->ai_addr, _servinfo->ai_addrlen);
if(bindret == -1) {
throw NetworkException("bind", strerror(errno));	
}	
}
_protocol = protocol;
_host = host;
_service = service;
}

std::string NetSocket::getIP() {
return static_cast<std::string>(_caddr);
}

int NetSocket::getDesc() {
return _descriptor;	
}

NetSocket::~NetSocket() {
freeaddrinfo(_servinfo);
close(_descriptor);
}

void* NetSocket::get_in_addr(sockaddr* sa) {
if(sa->sa_family == AF_INET) {
	return &(((sockaddr_in*)sa)->sin_addr);	
	}
	return &(((sockaddr_in6*)sa)->sin6_addr);	
}
