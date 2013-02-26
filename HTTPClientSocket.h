#ifndef _HTTPCLIENTSOCKET_H
#define _HTTPCLIENTSOCKET_H
#include "ClientSocket.h"
#include "SocketException.h"
/// \file HTTPClientSocket.h
/// \brief An implementation of HTTP Client Socket.
/// \author Phitherek_
/// \date 2012
/// \version 0.1
/// \namespace NetSocketPP
/// \brief A namespace for all library names
namespace NetSocketPP {
/// \class HTTPReply
/// \brief A class representing HTTP Reply.
class HTTPReply {
private:
std::string _raw;
std::string _protocol;
std::string _response;
std::string _timestamp;
std::string _server;
unsigned int _cl;
std::string _connection;
std::string _ct;
std::string _content;
public:
HTTPReply(); ///< A constructor.
HTTPReply(std::string raw); ///< \brief A constructor with parameter
///< \param raw Raw reply from recv.
~HTTPReply(); ///< A destructor.
void parse(); ///< HTTP reply parser
void addToContent(std::string cp); ///< \brief A function, that adds more parts of the content to the reply if necessary
///< \param cp Part of the content to be added.
std::string getRaw(); ///< \brief A function returning raw HTTP reply.
	///< \return Raw HTTP reply.
	std::string getProtocol(); ///< \brief A function returning HTTP protocol information.
	///< \return HTTP protocol information.
	std::string getResponse(); ///< \brief A function returning HTTP response message.
	///< \return HTTP response message.
	std::string getTimestamp(); ///< \brief A function returning timestamp.
	///< \return Timestamp.
	std::string getServer(); ///< \brief A function returning server information.
	///< \return Server information.
	unsigned int getContentLength(); ///< \brief A function returning length of content.
	///< \return Length of content.
	std::string getConnection(); ///< \brief A function returning connection status.
	///< \return Connection status.
	std::string getContentType(); ///< \brief A function returning type of content.
	///< \return Type of content.
	std::string getContent(); ///< \brief A function returning received content.
	///< \return Received content.
};
/// \class HTTPClientSocket
/// \brief A class representing HTTP client socket.
class HTTPClientSocket: public ClientSocket {
private:
	HTTPReply _reply;
	std::string _request;
public:
	HTTPClientSocket(std::string host, std::string service, std::string docRequest); ///< \brief A constructor with parameters.
	///< \param host Hostname or IP of socket destination, defaults to NULL.
	///< \param service Service port or identifier, defaults to HTTP.
	///< \param docRequest A document to request from the server, defaults to root/index (/).
	HTTPReply getReply(); ///< \brief A function returning a HTTPReply.
	///< \return HTTPReply object containing received data.
	std::string getRequest(); ///< \brief A function returning the request used in the socket.
	///< \return The HTTP request used to obtain data.
};
}
#endif
