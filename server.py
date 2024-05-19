import socket
import time

file = "/Users/anton/code/stepik/logfile_server.txt"
f = open(file, "a+")

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_socket.bind(("127.0.0.1", 65000))  # Привязываем серверный сокет к localhost и 65000 порту.
server_socket.listen(1)  # Начинаем прослушивать входящие соединения.

f.write("Time of starting: " + time.ctime() + "\n")  # Логируем начало работы сервера

while True:
    conn, addr = server_socket.accept()  # Метод, который принимает входящее соединение.
    start = time.time()

    f.write("Connection time: " + time.ctime(start) + "\n")  # Логируем время подключения клиента к серверу

    data = conn.recv(1024)  # Получаем данные из сокета.

    f.write("Recieve time: " + time.ctime() + "\n")  # Логируем время получения сообщения
    f.write("User message: " + data.decode("UTF-8") + "\n")  # Логируем полученное сообщение

    if (time.time() - start) >= 30.0:  # Отключаем клиента от сервера через 30 секунд задержки
        data = "Server timed out, connection closed. Try again. Server was written by Timoshin A.A. M3O-107B-23 \0"
        conn.sendall(data.encode('UTF-8'))
        conn.close()

    if not data:
        break

    data = data.decode('UTF-8')[::-1]  # Разворачиваем сообщение клиента
    message = " Сервер написан Тимошиным А.А. М3О-107Б-23 \0"
    data = data + message

    f.write("Server message: " + data[:-2] + "\n")  # Логируем отправленное сообщение

    time.sleep(5.0)  # Имитация работы сервера (задержка в 5 секунд)
    conn.sendall(data.encode('UTF-8'))  # Отправляем данные в сокет.

    f.write("Time of sending: " + time.ctime() + "\n")  # Логируем время отправки сообщения

conn.close()

f.write("Disconnection time: " + time.ctime() + "\n\n\n")  # Логируем отключение клиента от сервера
f.close()

server_socket.close()
