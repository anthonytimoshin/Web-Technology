#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include "fstream"
#include "chrono"

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
    auto connectionTime = chrono::system_clock::now();
    ofstream file;
    file.open("/Users/anton/code/stepik/logfile.txt",std::ios::app);
    file << "Connection time: "<< connectionTime << "\n";
    file << "Server adress: " << "..." << "\n"; // !!!

    // receiving data from user
    string message;
    cout << "Введите сообщение: ";
    getline(cin, message);

    // sending data
    sleep(5);
    send(clientSocket, message.c_str(), message.length(), 0);
    auto sendTime = chrono::system_clock::now();
    file << "Time of sending: " << sendTime << "\n";
    file << "User Message: " << message << "\n";

    // receiving answer from server
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
