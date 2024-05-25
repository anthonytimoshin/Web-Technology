#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "vector"
#include "fstream"

using namespace std;

void CachedMessages() {
    ifstream file("/Users/anton/code/stepik/cache.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
}


int main()
{
    CachedMessages();
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

    // Создание вектора для хранения сообщений cache
    vector<string> messages;

    while (true) {
        getline(cin, message);
        send(clientSocket, message.c_str(), message.length(), 0);

        // Добавление сообщения в вектор
        messages.push_back(message);

        // Проверка размера вектора и запись в файл, если нужно
        if (messages.size() > 5) {
            messages.erase(messages.begin());
        }

        // Запись сообщений в файл
        ofstream s("cached_messages.txt", ios::app); // cache
        for (const auto& msg : messages) {
            s << msg;
        }

        if (message == "exit") {
            break;
        }
        char buffer[1024];
        recv(clientSocket, buffer, sizeof(buffer), 0);
        cout << buffer << endl;
        buffer[0] = ' ';
    }

    // closing socket
    close(clientSocket);

    return 0;
}
