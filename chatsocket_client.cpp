#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "vector"
#include "fstream"

using namespace std;

int main()
{
    vector <string> cache;
    ofstream file("/Users/anton/code/stepik/cache.txt", ios::app);

    ifstream file_reader("/Users/anton/code/stepik/cache.txt");
    if (file_reader.is_open()) {
        string line;
        while (getline(file_reader, line)) {
            cout << line << endl;
        }
        file_reader.close();
    }
//    ofstream myFile("/Users/anton/code/stepik/cache.txt", ios::trunc);

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
            break;
        }
        char sent[1024];
        recv(clientSocket, sent, sizeof(sent), 0);
        cout << sent << endl;

        cache.push_back(sent);
        if (cache.size() > 5) {
            cache.erase(cache.begin());
        }

        cout << "Cообщение: ";
    }

    // closing socket
    close(clientSocket);

    // closing file
    for (int i = 0; i < 5; i++) {
        file << cache[i];
    }
    file.close();

    return 0;
}
