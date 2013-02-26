#ifndef _SOCKETEXCEPTION_H
#define _SOCKETEXCEPTION_H
/// \file SocketException.h
/// \brief An implementation of socket exception.
/// \author Phitherek_
/// \date 2012
/// \version 0.1
#include <exception>
#include <string>
/// \namespace NetSocketPP
/// \brief A namespace for all library names
namespace NetSocketPP {
/// \class SocketException
/// \brief A class representing an exception with socket classes
class SocketException: public std::exception {
private:
	std::string _msg;
public:
	SocketException(std::string msg); ///< \brief A constructor with parameters.
	///< \param msg What has happened.
	~SocketException() throw(); ///< A destructor, as needed by std::exception.
	const char* what() const throw(); ///< \brief A function, that returns error message, as needed by std::exception.
	///< \return Error message.	
};
}
#endif
