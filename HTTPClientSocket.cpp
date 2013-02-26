#include <iostream>
#include <cstdlib>
#include <cctype>
#include "HTTPClientSocket.h"
using namespace NetSocketPP;

HTTPReply::HTTPReply() {
_raw = "";
_protocol = "";
_response = "";
_timestamp = "";
_server = "";
_cl = 0;
_connection = "";
_ct = "";
_content = "";
}

HTTPReply::HTTPReply(std::string raw) {
_raw = raw;
_protocol = "";
_response = "";
_timestamp = "";
_server = "";
_cl = 0;
_connection = "";
_ct = "";
_content = "";
}

HTTPReply::~HTTPReply() {
_raw = "";
_protocol = "";
_response = "";
_timestamp = "";
_server = "";
_cl = 0;
_connection = "";
_ct = "";
_content = "";
}

void HTTPReply::parse() {
	std::string action = "firstline";
	std::string parsed = "";
	std::string scl = "";
	bool postspace = false;
	for(unsigned int i = 0; i < _raw.length(); i++) {
	if(action == "firstline") {
	if(postspace == true) {
	if(_raw[i] == '\r') {
	_response = parsed;
	parsed = "";
	action = "reqparse";
	i++;
	} else {
	parsed += _raw[i];
	}
	} else if(_raw[i] == ' ') {
	_protocol = parsed;
	parsed = "";
	postspace = true;	
	} else {
	parsed += _raw[i];	
	}
	} else if(action == "reqparse") {
		if(_raw[i] == ':') {
		i++;
		if(parsed == "Date" || parsed == "Request timestamp") {
		action = "timestamp";	
		} else if(parsed == "Server" || parsed == "server") {
		action = "server";	
		} else if(parsed == "Content-Length") {
		action = "cl";		
		} else if(parsed == "Connection") {
		action = "conn";	
		} else if(parsed == "Content-Type") {
		action = "ct";	
		}
		parsed = "";
		} else if(_raw[i] == '\r') {
		if(_raw[i-2] == '\r') {
		action = "content";
		}
		i++;
		parsed = "";
		} else {
		parsed += _raw[i];	
		}
	} else if(action == "timestamp") {
		if(_raw[i] == '\r') {
		i++;
		action = "reqparse";
		} else {
		_timestamp += _raw[i];	
		}
	} else if(action == "server") {
		if(_raw[i] == '\r') {
		i++;
		action = "reqparse";
		} else {
		_server += _raw[i];	
		}
	} else if(action == "cl") {
		if(_raw[i] == '\r') {
		i++;
		for(unsigned int j = 0; j < scl.length(); j++) {
		if(!isdigit(scl[j])) {
		throw SocketException("Content-Length is not a number!");	
		}
		}
		_cl = atoi(scl.c_str());
		scl = "";
		action = "reqparse";
	} else {
	scl += _raw[i];
	}
} else if(action == "conn") {
	if(_raw[i] == '\r') {
		i++;
		action = "reqparse";
		} else {
		_connection += _raw[i];	
		}
} else if(action == "ct") {
	if(_raw[i] == '\r') {
		i++;
		action = "reqparse";
		} else {
		_ct += _raw[i];	
		}
} else if(action == "content") {
	_content += _raw[i];
}
	}
}

void HTTPReply::addToContent(std::string cp) {
for(unsigned int i = 0; i < cp.length(); i++) {
_content += cp[i];
}	
}

std::string HTTPReply::getProtocol() {
	return _protocol;
}

std::string HTTPReply::getResponse() {
	return _response;	
}

std::string HTTPReply::getTimestamp() {
	return _timestamp;	
}

std::string HTTPReply::getServer() {
	return _server;	
}

unsigned int HTTPReply::getContentLength() {
	return _cl;	
}

std::string HTTPReply::getConnection() {
	return _connection;
}

std::string HTTPReply::getContentType() {
	return _ct;	
}

std::string HTTPReply::getContent() {
	return _content;	
}

std::string HTTPReply::getRaw() {
	return _raw;	
}

HTTPClientSocket::HTTPClientSocket(std::string host = NULL, std::string service = "http", std::string docRequest = "/"): ClientSocket(host, service, "TCP") {
	_request = "";
	_request += "GET ";
	_request += docRequest;
	_request += " HTTP/1.0\n";
	if(host != "") {
	_request += "Host: ";
	_request += host;	
	}
	_request += "\n\n";
	send(_request, 0);
	recv(0);
	std::string rawreply;
	rawreply = CStrToString(buf);
	HTTPReply reply(rawreply);
	_reply = reply;
	_reply.parse();
	std::string rawcontent = _reply.getContent();
	unsigned int cl = _reply.getContentLength();
	while(rawcontent.length() < cl) {
		for(int i = 0; i < 100000; i++) {
		buf[i] = 0;	
		}
		recv(0);
		_reply.addToContent(CStrToString(buf));
		rawcontent = _reply.getContent();
	}
}

HTTPReply HTTPClientSocket::getReply() {
return _reply;	
}

std::string HTTPClientSocket::getRequest() {
return _request;	
}
