CXXFLAGS=-Wall -fPIC
CXXFLAGS2=-shared
TESTCXXFLAGS=-Wall -lnetsocketpp
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
	${CXX} ${TESTCXXFLAGS} -o tests/nstest tests/nstest.cpp
	${CXX} ${TESTCXXFLAGS} -o tests/tcpsrvtest tests/tcpsrvtest.cpp 
	${CXX} ${TESTCXXFLAGS} -o tests/tcpclitest tests/tcpclitest.cpp
	${CXX} ${TESTCXXFLAGS} -o tests/udprecvtest tests/udprecvtest.cpp
	${CXX} ${TESTCXXFLAGS} -o tests/udpsendtest tests/udpsendtest.cpp
	${CXX} ${TESTCXXFLAGS} -o tests/httptest tests/httptest.cpp

debugtest:
	${CXX} ${TESTCXXFLAGS} -g -o tests/nstest tests/nstest.cpp
	${CXX} ${TESTCXXFLAGS} -g -o tests/tcpsrvtest tests/tcpsrvtest.cpp 
	${CXX} ${TESTCXXFLAGS} -g -o tests/tcpclitest tests/tcpclitest.cpp 
	${CXX} ${TESTCXXFLAGS} -g -o tests/udprecvtest tests/udprecvtest.cpp 
	${CXX} ${TESTCXXFLAGS} -g -o tests/udpsendtest tests/udpsendtest.cpp 
	${CXX} ${TESTCXXFLAGS} -g -o tests/httptest tests/httptest.cpp 


