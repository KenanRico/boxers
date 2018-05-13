#include <WinSock2.h>
#include <stdexcept>

//get access to winsock lib functions
#pragma comment(lib, "ws2_32.lib")


#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

class ClientSocket{
	private:
		struct SocketInfo{
			const char* host;
			short port;
		};
	private:
		static bool winsock_started;
		struct SocketInfo socket_info;
		SOCKADDR_IN address;
		SOCKET connection;

	public:
		ClientSocket(const char*, int);
		~ClientSocket();
	private:
		ClientSocket() = delete;
		ClientSocket(const ClientSocket&) = delete;
		ClientSocket& operator=(const ClientSocket&) = delete;
		
	public:
		static void init();
		static void deinit();
	public:
		void connectToServer() const;
		void disconnect() const;
		void read() const;
		void write() const;
};

#endif
