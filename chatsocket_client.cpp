#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "chrono"

using namespace std;

int main()
{
    char sinAddr[16];
    int sinPort;

    cout << "Введите IPv4 адрес сервера: ";
    cin >> sinAddr;
    cout << "Введите порт: ";
    cin >> sinPort;
    cout << "Подключение к серверу IPv4: " << sinAddr << " Port: " << sinPort;

    in_addr ip_to_num;
    inet_pton(AF_INET, sinAddr, &ip_to_num);

    // creating socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // specifying address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;      // IPv4
    serverAddress.sin_port = htons(sinPort); // Port
    serverAddress.sin_addr = ip_to_num;      // Binds the socket to sinAddr from config.txt
    // INADDR_ANY - to all available interfaces

    // sending connection request
    connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    char answer[1024];
    recv(clientSocket, answer, sizeof(answer), 0);
    cout << endl << answer;

    // receiving nickname from user
    string message;
    getline(cin,message);

    // sending nickname
    send(clientSocket, message.c_str(), message.length(), 0);

    while (true) {
        getline(cin, message);
        send(clientSocket, message.c_str(), message.length(), 0); // здесь или снизу (гипотеза - exit принимается сервером, проверяется условие, закрывается сокет)
        if (message == "exit") {
            cin.ignore();
            break;
        }
        char sent[1024];
        recv(clientSocket, sent, sizeof(sent), 0);
        cout << sent << endl;
        sent[0] = '0';
        cout << "Введите сообщение: ";
    }

    // closing socket
    close(clientSocket);

    return 0;
}
