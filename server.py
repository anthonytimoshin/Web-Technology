import socket
import time

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.bind(("127.0.0.1", 65000))  # Привязываем серверный сокет к localhost и 65000 порту.
s.listen(1)  # Начинаем прослушивать входящие соединения.

while True:
    conn, addr = s.accept()  # Метод, который принимает входящее соединение.
    start = time.time()

    data = conn.recv(1024)  # Получаем данные из сокета.

    if (time.time() - start) >= 30.0:  # Отключаем клиента от сервера через 30 секунд задержки
        data = "Server timed out, connection closed. Try again. Server was written by Timoshin A.A. M3O-107B-23 \0"
        conn.sendall(data.encode('UTF-8'))
        conn.close()
        print("Connection closed.")

    if not data:
        current_time = time.time()
        break

    data = data.decode('UTF-8')[::-1]  # Разворачиваем сообщение клиента
    message = " Сервер написан Тимошиным А.А. М3О-107Б-23 \0"
    data = data + message

    time.sleep(5.0)  # Имитация работы сервера (задержка в 5 секунд)
    conn.sendall(data.encode('UTF-8'))  # Отправляем данные в сокет.

conn.close()
