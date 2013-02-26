#ifndef _SERVERSOCKET_H
#define _SERVERSOCKET_H
#include "NetSocket.h"
#include "NetworkException.h"
#include "SocketException.h"
/// \file ServerSocket.h
/// \brief An implementation of a server socket.
/// \author Phitherek_
/// \date 2013
/// \version 0.1

/// \fn sigchld_handler(int s)
/// \brief Signal handler, needed for implementation purposes
/// \param s Needed for implementation purposes
inline void sigchld_handler(int s) {
while(waitpid(-1, NULL, WNOHANG) > 0);	
}

/// \namespace NetSocketPP
/// \brief A namespace for all library names
namespace NetSocketPP {
/// \class ServerFunctionArgs
/// \brief A class for storing server function arguments.
class ServerFunctionArgs {
private:
	std::string* _tab;
	unsigned int _size;
public:
ServerFunctionArgs(); ///< A constructor.
ServerFunctionArgs(ServerFunctionArgs& sfa); ///< \brief A copy constructor.
///< \param sfa An object to be copied.
~ServerFunctionArgs(); ///< A destructor.
void addArgument(std::string arg); ///< \brief Function adding an argument to the list.
///< \param arg An argument to be added, of type std::string.
std::string getArgument(unsigned int idx); ///< \brief Function returning the argument of given index number.
///< \param idx Index of the argument.
///< \return The argument.
std::string operator[](unsigned int idx); ///< \brief Operator[] returning the argument of given index number.
///< \param idx Index of the argument.
///< \return The argument.
};
/// \class ServerSocket
/// \brief An implementation of the server socket.
class ServerSocket: public NetSocket {
private:
int _newDescriptor;
char _buf[100000];
struct sigaction _sa;
public:
ServerSocket(std::string host, std::string service, std::string protocol); ///< \brief A constructor with parameters.
///< \param host A hostname or IP adress of socket destination, defaults to NULL.
///< \param service Port or service that socket should be connected with.
///< \param protocol Socket protocol, TCP or UDP.
~ServerSocket(); ///< A destructor.
void startServer(ServerFunctionArgs& functionOutput ,ServerFunctionArgs& (*serverMain)(ServerFunctionArgs, ServerSocket*), ServerFunctionArgs functionInput, bool infinite, unsigned int iternum, int connectionLimit); ///< \brief A function that starts TCP server.
///< \param functionOutput A ServerFunctionArgs object that will store server function result.
///< \param serverMain An user-defined function, that returns ServerFunctionArgs object - results of the server function with arguments: ServerFunctionArgs object - arguments to the server function and pointer to ServerSocket object - for passing socket information in that order.
///< \param functionInput A ServerFunctionArgs object with server function arguments.
///< \param infinite Determines if server loop should be infinite.
///< \param iternum Number of accept() iterations for non-infinite loops.
///< \param connectionLimit Maximum number of accepted connections.
int send(std::string msg, int flags=0); ///< \brief A function that sends data through the socket.
///< \param msg A message/data to send, of type std::string.
///< \param flags Send flags, defaulting to 0.
///< \return Number of bytes sent.
int recv(int flags = 0); ///< \brief A function that receives data through the socket.
///< \param flags Receive flags, defaulting to 0.
///< \return Number of bytes received.
std::string get(); ///< \brief A function returning received data.
///< \return Received data as string.
};
}
#endif
