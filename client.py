import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.connect(("127.0.0.1", 65000))  # Подключаемся к нашему серверу.
message = str(input("Enter your message: "))  # Получаем сообщение от пользователя
s.sendall(message.encode('utf-8'))  # Отправляем фразу.
data = s.recv(1024)  # Получаем данные из сокета.

with (open('log_client.txt', 'a+') as f):
    text = data.decode('utf-8')
    f.write(text)
    f.write("\n")
    f.close()

s.close()
