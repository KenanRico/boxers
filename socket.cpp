#include "socket.h"
#include "gamecomponents.h"
#include "box.h"


#include <WinSock2.h>
#include <iostream>
#include <cstring>
#include <sstream>

#pragma comment(lib, "ws2_32.lib")



bool ClientSocket::winsock_started = false;

ClientSocket::ClientSocket(const char* target_addr, int target_port): 
socket_info((struct SocketInfo){target_addr, target_port}),
connected(false),
connection(INVALID_SOCKET),
send_str(""){
	address.sin_addr.s_addr = inet_addr(target_addr);
	//address.sin_addr.s_addr = gethostbyname(target_addr);
	address.sin_port = htons(target_port);
	address.sin_family = AF_INET;
	connection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	thread_info.started = false;
}

ClientSocket::~ClientSocket(){
	//do what
	if(thread_info.started){
		WaitForSingleObject(thread_info.rthread, INFINITE);
		WaitForSingleObject(thread_info.wthread, INFINITE);
	}else;
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

void ClientSocket::connectToServer(){
	std::cout<<"Attempting to connect to "<<socket_info.host<<":"<<socket_info.port<<"\n";
	if(connect(connection, (SOCKADDR*)&address, sizeof(address))>=0){
		connected = true;
		std::string name = GameComponents::getMyBox()->getName();
		send(connection, name.c_str(), name.size(), 0);
		std::cout<<"Connect successful!\n";
	}else{
		closesocket(connection);
		throw std::runtime_error("Failed to connect!");
	}
}

bool ClientSocket::isConnected() const{
	return connected;
}


DWORD WINAPI readLoop(LPVOID);
DWORD WINAPI writeLoop(LPVOID);

void ClientSocket::runMsgHandlingThread(){
	thread_info.started = true;
	thread_info.rthread = CreateThread(nullptr, 0, readLoop, (LPVOID)this, 0, &thread_info.ID);
	thread_info.wthread = CreateThread(nullptr, 0, writeLoop, (LPVOID)this, 0, &thread_info.ID);
}

DWORD WINAPI readLoop(LPVOID arg){
	ClientSocket* socket = (ClientSocket*)arg;
	while(socket->connected){
		//mutex(receive).lock
		//recv(SOCKET, char[], int, 0);
		//mutex(receive).release
		memset(socket->recv_str, 0, sizeof(socket->recv_str));
		recv(socket->connection, socket->recv_str, sizeof(socket->recv_str), 0);
	}
	return 0;
}

DWORD WINAPI writeLoop(LPVOID arg){
	ClientSocket* socket = (ClientSocket*)arg;
	Box const * box = GameComponents::getMyBox();
	while(socket->connected){
		//if updated, write
		if(GameComponents::isUpdated()){
			//mutex(send).lock
			//send(SOCKET, char*, int, 0);
			//mutex(send).release
			std::string temp("");
			std::stringstream ss;
			ss<<box->getX()<<" "<<box->getY();
			socket->send_str = ss.str();
			send(socket->connection, socket->send_str.c_str(), socket->send_str.size(), 0);
		}else;
	}
	return 0;
}

void ClientSocket::disconnect(){
		closesocket(connection);
		connected = false;
}

std::string ClientSocket::getCurrentMessage() const{
	return std::string(recv_str);
}
