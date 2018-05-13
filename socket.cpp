#include "socket.h"

#include <WinSock2.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")


bool ClientSocket::winsock_started = false;

ClientSocket::ClientSocket(const char* target_addr, int target_port): socket_info((struct SocketInfo){target_addr, target_port}), connection(INVALID_SOCKET){
	address.sin_addr.s_addr = inet_addr(target_addr);
	//address.sin_addr.s_addr = gethostbyname(target_addr);
	address.sin_port = htons(target_port);
	address.sin_family = AF_INET;
	connection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

ClientSocket::~ClientSocket(){
	//do what
}

void ClientSocket::init(){
	if(!winsock_started){
		WSAData wsaData;
		WORD dll_version = MAKEWORD(2,2);
		winsock_started = (WSAStartup(dll_version, &wsaData) == 0);
		if(winsock_started){
			//good
		}else{
			throw std::runtime_error("Failed to init Winsock!");
		};
	}else{
		//winsock already started, do nothing
		throw std::runtime_error("Winsock already started!");
	}
}

void ClientSocket::deinit(){

}

void ClientSocket::connectToServer() const{
	std::cout<<"Attempting to connect to "<<socket_info.host<<":"<<socket_info.port<<"\n";
	if(connect(connection, (SOCKADDR*)&address, sizeof(address))>=0){
		std::cout<<"Connect successful!";
	}else{
		closesocket(connection);
		throw std::runtime_error("Failed to connect!");
	}
}

void ClientSocket::disconnect() const{
		closesocket(connection);
}

void ClientSocket::read() const{

}

void ClientSocket::write() const{

}
