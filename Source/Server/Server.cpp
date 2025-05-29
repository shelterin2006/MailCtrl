#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <tchar.h>
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS 
using namespace std;

int main() {
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        // Xử lý lỗi
        cerr << "WSAStartup failed with error: " << result << endl;
        return 1;
    }
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        // Xử lý lỗi: WSAGetLastError()
        cerr << "Socket creation failed with error: " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    }

    int port = 55555;
    sockaddr_in service;
    service.sin_family = AF_INET;
    InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
    service.sin_port = htons(port);
    if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        cout << "bind() failed:" << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 0;
    }
    else {
        cout << "bind() is OK" << endl;
    }

    if(listen(serverSocket, 1) == SOCKET_ERROR){
        cout<<"listen() : error listening on socket"<<WSAGetLastError()<<endl;
    }else cout<<"Listen() is OK, I'm waiting for connctions..."<<endl;

    SOCKET acceptSocket;
    acceptSocket = accept(serverSocket, NULL, NULL);
    if(acceptSocket == INVALID_SOCKET){
        cout<<"accept failed:"<<WSAGetLastError()<<endl;
        WSACleanup();
        return -1;
    }else cout<<"accept() is working"<<endl;

    WSACleanup();
    return 0;
}