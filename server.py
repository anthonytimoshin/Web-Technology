import socket
import time

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.bind(("127.0.0.1", 65000))  # Привязываем серверный сокет к localhost и 65000 порту.
s.listen(1)  # Начинаем прослушивать входящие соединения.
conn, addr = s.accept()  # Метод который принимает входящее соединение.

while True:
    data = conn.recv(1024)  # Получаем данные из сокета.
    if not data:
        break
    data = data[::-1]
    message = " Сервер написал Тимошин А.А. М3О-107Б-23"
    data = data + message.encode('utf-8')
    time.sleep(1.0)  # имитация работы сервера (задержка в 1 секунду)
    conn.sendall(data)  # Отправляем данные в сокет.

conn.close()
