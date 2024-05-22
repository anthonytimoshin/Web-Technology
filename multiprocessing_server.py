import socket
import time
import multiprocessing

file = "/Users/anton/code/stepik/logfile_server.txt"
f = open(file, "a")


def handle_client(conn, addr):
    start = time.time()

    f.write("Connection time: " + time.ctime(start) + "\n")

    data = conn.recv(1024)

    f.write("Recieve time: " + time.ctime() + "\n")
    f.write("User message: " + data.decode("UTF-8") + "\n")

    if not data:
        conn.close()

    data = data.decode('UTF-8')[::-1]
    message = " Сервер написан Тимошиным А.А. М3О-107Б-23 \0"
    data = data + message

    f.write("Server message: " + data[:-2] + "\n")

    time.sleep(5.0)
    conn.sendall(data.encode('UTF-8'))

    f.write("Time of sending: " + time.ctime() + "\n")

    if (time.time() - start) >= 10.0:
        conn.close()
        f.write("Disconnection time: " + time.ctime() + "\n\n\n")


if __name__ == '__main__':
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(("127.0.0.1", 65000))
    server_socket.listen(5)  # максимальное количество подключений одновременно - 5

    f.write("Time of starting: " + time.ctime() + "\n")

    while True:
        conn, addr = server_socket.accept()
        process = multiprocessing.Process(target=handle_client, args=(conn, addr))
        process.start()

