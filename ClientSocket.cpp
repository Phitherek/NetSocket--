#include <iostream>
#include <cstdlib>
#include "ClientSocket.h"
using namespace NetSocket;

ClientSocket::ClientSocket(std::string host = NULL, std::string service, std::string protocol): NetSocket(host, service, protocol) {
if(protocol == "TCP") {
int conret;
conret = connect(_descriptor, _servinfo->ai_addr, _servinfo->ai_addrlen);
if(conret == -1) {
throw NetworkException("connect", strerror(errno));
}
}
}

int ClientSocket::send(std::string msg, int flags=0) {
	if(protocol == "TCP") {
		int sr = send(_descriptor, msg.c_str(), msg.length(), flags);
		if(sr == -1) {
		throw NetworkException("send", strerror(errno));	
		}
		return sr;
	} else if(protocol == "UDP") {
		int sr = sendto(_descriptor, msg.c_str(), msg.length(), flags, _servinfo->ai_addr, _servinfo->ai_addrlen);
		if(sr == -1) {
		throw NetworkException("sendto", strerror(errno));	
		}
		return sr;
	}
}

int ClientSocket::recv(int flags) {
	if(protocol == "TCP") {
		int rr = recv(_descriptor, _buf, 99999, flags);
		if(rr == -1) {
		throw NetworkException("recv", strerror(errno));	
		} else if(rr == 0) {
		throw NetworkException("recv", "Remote end has closed the connection.");	
		}
		return rr;	
	} else if(protocol == "UDP") {
		int rr = recvfrom(_descriptor, _buf, 99999, flags, _servinfo->ai_addr, _servinfo->ai_addrlen);
		if(rr == -1) {
		throw NetworkException("recvfrom", strerror(errno));	
		} else if(rr == 0) {
		throw NetworkException("recvfrom", "Remote end has closed the connection.");	
		}
		buf[rr] = '\0';
		return rr;
	}
}

std::string ClientSocket::get() {
	return static_cast<std::string>(_buf);
}
