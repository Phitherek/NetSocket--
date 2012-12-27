#ifndef _NETWORKEXCEPTION_H
#define _NETWORKEXCEPTION_H
/// \file NetworkException.h
/// \brief An implementation of network exception.
/// \author Phitherek_
/// \date 2012
/// \version 0.1
#include <exception>
#include <string>
/// \namespace NetSocket
/// \brief A namespace for all library names
namespace NetSocket {
/// \class NetworkException
/// \brief A class representing an exception with network.
class NetworkException: public std::exception {
private:
	std::string _cmd;
	std::string _msg;
public:
	NetworkException(std::string cmd, std::string msg); ///< \brief A constructor with parameters.
	///< \param cmd A command, where exception occured.
	///< \param msg What has happened.
	~NetworkException() throw(); ///< A destructor, as needed by std::exception.
	const char* what() const throw(); ///< \brief A function, that returns error message, as needed by std::exception.
	///< \return Error message.	
};
}
#endif
