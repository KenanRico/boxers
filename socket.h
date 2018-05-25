#include <WinSock2.h>
#include <stdexcept>
#include <windows.h>
#include <tchar.h>
#include <string>

//get access to winsock lib functions
#pragma comment(lib, "ws2_32.lib")


#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

class ClientSocket{
	private:
		//socket related
		static bool winsock_started;
		struct SocketInfo{
			const char* host;
			short port;
		} socket_info;
		bool connected;
		SOCKADDR_IN address;
		SOCKET connection;
		//thread
		struct ThreadInfo{
			DWORD ID;
			HANDLE rthread;
			HANDLE wthread;
			bool started;
		} thread_info;
		//game related
		bool local_updated;
		std::string send;
		bool server_updated;
		std::string receive;

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
		void connectToServer();
		bool isConnected() const;
		void runMsgHandlingThread();
		void disconnect();
		std::string getCurrentMessage() const;

	friend DWORD WINAPI readLoop(LPVOID);
	friend DWORD WINAPI writeLoop(LPVOID);
};

#endif
