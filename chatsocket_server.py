import socket
import time
import multiprocessing

file = "/Users/anton/code/stepik/messenger.txt"
f = open(file, "a+")
clients = []


def nickname(conn):
    while True:
        # инициализация пользователя, ввод никнейма
        nickname = conn.recv(1024).decode("UTF-8")
        if not nickname:
            break
        message = "Your nickname: " + nickname + + 50*" " + "\n"
        conn.send(message.encode("utf-8"))
        return nickname


def authorization(conn, addr):

    clients.append(conn)

    # блок отправки последних 10 сообщений клиенту
    f.seek(0)
    messages = f.readlines()[-10:]
    sent = ''
    for msg in messages:
        msg = msg.strip() + "\n"
        sent += msg
    print(sent)
    conn.send(sent.encode("utf-8"))

    conn.send("Enter your nickname: ".encode("utf-8"))
    nick = nickname(conn)
    print(nick)

    while True:
        message = conn.recv(1024).decode("UTF-8")
        if not message:
            break
        if message == "exit":
            conn.close()
            print(f"{addr} disconnected")
            break

        message = (nick + ": " + message + 50*" " + "\n")
        message.strip()
        conn.send(message.encode("utf-8"))
        f.write(message)
        print(message)


if __name__ == '__main__':
    server_socket = socket.socket()
    server_socket.bind(("127.0.0.1", 65000))
    server_socket.listen(5)  # максимальное количество подключений одновременно - 5

    while True:
        conn, addr = server_socket.accept()
        print(f'New connection from: {addr}')
        authorization(conn, addr)
        # process = multiprocessing.Process(target=authorization, args=(conn, addr))
        # process.start()
