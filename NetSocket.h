#ifndef NETSOCKET_H
#define NETSOCKET_H
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string>
/// \file NetSocket.h
/// \brief A library designed to simplify the use of UNIX Network Sockets in the means of OOP.
/// \author Phitherek_
/// \date 2012
/// \version 0.1

/// \namespace NetSocket
/// \brief A namespace for all library names.
namespace NetSocket {

/// \class NetSocket
/// \brief A class, that represents network connection - socket.
class NetSocket {
protected:
int _descriptor; ///< Socket descriptor.
const int _yes; ///< Needed for implementation purposes.
int _status; ///< Needed for implementation purposes.
char _caddr[INET6_ADDRSTRLEN]; ///< A structure that stores IP address.
addrinfo _hints; ///< Needed for implementation purposes.
addrinfo *_servinfo; ///< Needed for implementation purposes.
std::string _host; ///< A host to which a socket is connecting to/on which a server socket is opened.
std::string _service; ///< A port or a string identyfing service that socket is connecting to/which server is being opened.
std::string _protocol; ///< A protocol of the socket: TCP/UDP.
void *get_in_addr(sockaddr* sa); ///< Needed for implementation purposes.
public:
	NetSocket(std::string host = NULL, std::string service, std::string protocol); ///< \brief A constructor with parameters, that creates a socket.
	///< \param host A hostname or IP address of socket destination.
	///< \param port A port or service identifier, where socket is to be opened.
	///< \param protocol A protocol of the socket, TCP or UDP.
	std::string getIP(); ///< \brief A function that returns IP of a host.
	///< \return IP address of a host as std::string.
	int getDesc(); ///< \brief A function that returns socket descriptor.
	///< \return A socket descriptor.
	~NetSocket(); ///< A destructor, that frees the memory.
};	
}
#endif
