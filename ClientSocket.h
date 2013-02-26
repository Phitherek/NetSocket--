#ifndef _CLIENTSOCKET_H
#define _CLIENTSOCKET_H
#include "NetSocket.h"
#include "NetworkException.h"
/// \file ClientSocket.h
/// \brief An implementation of a client socket.
/// \author Phitherek_
/// \date 2012
/// \version 0.1

/// \namespace NetSocketPP
/// \brief A namespace for all library names
namespace NetSocketPP {
/// \class ClientSocket
/// \brief An implementation of a client socket. Inherits from NetSocket.
class ClientSocket: public NetSocket {
protected:
char buf[100000]; ///< A large buffer for data.
public:
	ClientSocket(std::string host, std::string service, std::string protocol); ///< \brief A constructor with parameters, that creates and connects the socket.
	///< \param host A hostname or IP address of socket destination.
	///< \param service A port or service identifier, where socket is to be opened.
	///< \param protocol A protocol of the socket, TCP or UDP.
	int send(std::string msg, int flags); ///< \brief A function, that sends data through the socket.
	///< \param msg A message to send.
	///< \param flags Socket flags, default 0.
	///< \return Number of bytes sent.
	int recv(int flags); ///< \brief A function, that receives data through the socket.
	///< \param flags Socket flags, default 0.
	///< \return Number of bytes received.
	std::string get(); ///< \brief A function returning recently recv-d data.
	///< \return Received data as std::string.
};
}
#endif
