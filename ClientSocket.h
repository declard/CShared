#ifndef ClientSocketH
#define ClientSocketH

#define GENERATE_BUG

#include <winsock2.h>
#include "XS.h"
#include "Delegates.h"
typedef unsigned int uint;
class ClientSocket {
	SOCKET sock;
	HANDLE thread;
	unsigned long ip;
	unsigned int port;
	static unsigned long __stdcall Read(void*obj);
	void Read();
public:
	Event OnConnect,OnConnecting,OnRead,OnWrite,OnDisconnect,OnError;
	ClientSocket(const XS ip,unsigned int port);
	bool Open();
	bool Close();
	bool Send(const XS str);
	bool Send(const char*,uint);
	~ClientSocket();
};
#endif
