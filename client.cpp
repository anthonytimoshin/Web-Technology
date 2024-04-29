#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include "fstream"

using namespace std;

int main()
{
    // creating socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // specifying address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(65000);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // sending connection request
    connect(clientSocket, (struct sockaddr*)&serverAddress,
            sizeof(serverAddress));

    // receiving data from user
    string message;
    cout << "Введите сообщение: ";
    getline(cin, message);

    // sending data
    send(clientSocket, message.c_str(), message.length(), 0);

    // receiving answer from server
    char answer[1024];
    recv(clientSocket, answer, sizeof(answer), 0);

    // logging
    ofstream file;
    file.open("/Users/anton/code/stepik/logfile.txt",std::ios::app);
    file << answer << "\n";
    file.close();

    // closing socket
    close(clientSocket);

    return 0;
}
