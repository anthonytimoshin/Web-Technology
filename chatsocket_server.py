import socket
import time
import multiprocessing

file = "/Users/anton/code/stepik/messenger.txt"
f = open(file, "a+")
clients = []


def authorization(conn, addr):
    while True:
        # инициализация пользователя, ввод никнейма
        conn.send("Enter your nickname: ".encode("utf-8"))
        nickname = conn.recv(1024).decode("UTF-8")
        clients.append((nickname, addr[0], addr[1]))
        if not nickname:
            break

        print(f'New connection from {nickname}: {addr}')
        print(clients)

        # блок отправки последних 10 сообщений клиенту
        send_last_10_messages(conn)

        return nickname


def send_last_10_messages(conn):
    f.seek(0)
    messages = f.readlines()[-10:]
    sent = ''
    for msg in messages:
        msg = msg.strip() + "\n"
        sent += msg
    print(sent)
    conn.send(sent.encode("utf-8"))


def message(conn, addr):
    nickname = authorization(conn, addr)
    nick = nickname
    print(nick)

    # блок получения сообщений от клиента
    while True:
        message = conn.recv(1024).decode("UTF-8")

        if not message:
            break
        if message == "exit":
            conn.close()
            break

        f.write(nickname + ": " + message + "\n")
        print(nickname + ": " + message)


if __name__ == '__main__':
    server_socket = socket.socket()
    server_socket.bind(("127.0.0.1", 65000))
    server_socket.listen(5)  # максимальное количество подключений одновременно - 5

    while True:
        conn, addr = server_socket.accept()

        process = multiprocessing.Process(target=message, args=(conn, addr))
        process.start()
