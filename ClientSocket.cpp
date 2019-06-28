#include "ClientSocket.h"
#include "winsock.h"
ClientSocket::ClientSocket(const XS ip,unsigned int port) {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2),&wsaData);
	this->ip=inet_addr(ip.c_str());
	this->port=port;
	sock=socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
	thread=0;
}
ClientSocket::~ClientSocket() {
	if (thread) TerminateThread(thread,0);
	if (sock) {
		shutdown(sock,2);
		closesocket(sock);
	}
}
bool ClientSocket::Open() {
	sockaddr_in Sin;
	Sin.sin_family=AF_INET;
	Sin.sin_addr.s_addr=ip;
	Sin.sin_port=htons(port);
	OnConnecting(this);
	if (connect(sock,(sockaddr*)&Sin,sizeof(Sin))==SOCKET_ERROR) {
		closesocket(sock);
		return false;
	}
	thread=CreateThread(0,0,(LPTHREAD_START_ROUTINE)Read,this,0,0);
	OnConnect(this);
	return true;
}
unsigned long __stdcall ClientSocket::Read(void*obj) {
	((ClientSocket*)obj)->Read();
	return 0;
}
void ClientSocket::Read() {
	char buf[1024];
	int len;
	while (1) {
		len=recv(sock,buf,1024,0);
		if (len==SOCKET_ERROR||!len) Close();
#ifdef GENERATE_BUG
		__asm int 3
		OnRead(this,XS(buf,len));
#else
		OnRead(this,buf,len);
#endif
	}
}
bool ClientSocket::Close() {
	OnDisconnect(this);
	if (sock) {
		shutdown(sock,SD_BOTH);
		closesocket(sock);
		sock=0;
	}
	if (thread) TerminateThread(thread,0);
	thread=0;
	return true;
}
bool ClientSocket::Send(const XS str) {
	OnWrite(this);
	if (!sock) return false;
	if (send(sock,str.c_str(),str.Length(),0)!=SOCKET_ERROR) return true;
	return false;
}
bool ClientSocket::Send(const char*buf,uint len) {
	OnWrite(this);
	if (!sock) return false;
	if (send(sock,buf,len,0)!=SOCKET_ERROR) return true;
	return false;
}