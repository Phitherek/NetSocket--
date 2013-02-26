#include <iostream>
#include <cstdlib>
#include "ClientSocket.h"
using namespace NetSocketPP;

ClientSocket::ClientSocket(std::string host, std::string service, std::string protocol): NetSocket(host, service, protocol) {
if(protocol == "TCP") {
int conret;
conret = connect(_descriptor, _servinfo->ai_addr, _servinfo->ai_addrlen);
if(conret == -1) {
throw NetworkException("connect", strerror(errno));
}
}
}

int ClientSocket::send(std::string msg, int flags=0) {
	if(_protocol == "TCP") {
		int sr = ::send(_descriptor, msg.c_str(), msg.length(), flags);
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

int ClientSocket::recv(int flags) {
	if(_protocol == "TCP") {
		int rr = ::recv(_descriptor, buf, 99999, flags);
		if(rr == -1) {
		throw NetworkException("recv", strerror(errno));	
		} else if(rr == 0) {
		throw NetworkException("recv", "Remote end has closed the connection.");	
		}
		return rr;	
	} else if(_protocol == "UDP") {
		int rr = ::recvfrom(_descriptor, buf, 99999, flags, (sockaddr*)&_their_addr, &_addr_size);
		if(rr == -1) {
		throw NetworkException("recvfrom", strerror(errno));	
		} else if(rr == 0) {
		throw NetworkException("recvfrom", "Remote end has closed the connection.");	
		}
		buf[rr] = '\0';
		return rr;
	}
	return -1;
}

std::string ClientSocket::get() {
	return static_cast<std::string>(buf);
}
