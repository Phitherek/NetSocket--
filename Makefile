CXXFLAGS=-Wall -fPIC
CXXFLAGS2=-shared
TESTCXXFLAGS=-Wall
all:
	${CXX} ${CXXFLAGS} -c *.cpp
	${CXX} ${CXXFLAGS2} -Wl,-soname,libnetsocketpp.so.0 -o libnetsocketpp.so.0.1 *.o
install:
	cp libnetsocketpp.so.0.1 /usr/lib
	mkdir /usr/include/NetSocket++
	cp *.h /usr/include/NetSocket++
	ln -sf /usr/lib/libnetsocketpp.so.0.1 /usr/lib/libnetsocketpp.so.0
	ln -sf /usr/lib/libnetsocketpp.so.0.1 /usr/lib/libnetsocketpp.so
test:
	${CXX} ${TESTCXXFLAGS} -o tests/nstest tests/nstest.cpp NetSocket.cpp ClientSocket.cpp HTTPClientSocket.cpp ServerSocket.cpp NetworkException.cpp SocketException.cpp
debugtest:
	${CXX} ${TESTCXXFLAGS} -g -o tests/nstest tests/nstest.cpp NetSocket.cpp ClientSocket.cpp HTTPClientSocket.cpp ServerSocket.cpp NetworkException.cpp SocketException.cpp

