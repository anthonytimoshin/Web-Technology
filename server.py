import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.bind(("127.0.0.1", 65000))  # Привязываем серверный сокет к localhost и 65000 порту.
s.listen(1)  # Начинаем прослушивать входящие соединения.
conn, addr = s.accept()  # Метод который принимает входящее соединение.

while True:
    data = conn.recv(1024)  # Получаем данные из сокета.
    if not data:
        break
    conn.sendall(data[::-1])  # Отправляем данные в сокет.
conn.close()
