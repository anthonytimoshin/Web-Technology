#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "fstream"
#include "chrono"

using namespace std;

int main()
{
    ifstream config("/Users/anton/code/stepik/config.txt");

    char sinAddr[16];
    int sinPort;
    config >> sinAddr >> sinPort;

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

    // sending connection request and logging
    connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    auto connectionTime = chrono::system_clock::now();
    ofstream file;
    file.open("/Users/anton/code/stepik/logfile.txt",std::ios::app);
    file << "Connection time: "<< connectionTime << "\n";
    file << "Server adress: IPv4: " << sinAddr << " Port: " << sinPort << "\n";

    // receiving data from user
    string message;
    cout << "Введите сообщение: ";
    getline(cin, message);

    // sending data and logging
    sleep(5);
    send(clientSocket, message.c_str(), message.length(), 0);
    auto sendTime = chrono::system_clock::now();
    file << "Time of sending: " << sendTime << "\n";
    file << "User Message: " << message << "\n";

    // receiving answer from server and logging
    char answer[1024];
    recv(clientSocket, answer, sizeof(answer), 0);
    auto receiveTime = chrono::system_clock::now();
    file << "Receive time: " << receiveTime << "\n";
    file << "Server message: " << answer << "\n\n";

    file.close();

    // closing socket
    close(clientSocket);

    return 0;
}
