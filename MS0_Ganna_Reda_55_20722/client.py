import socket
import select

import sys
client_socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
port=5608
client_socket.connect(('127.0.0.1',port))
while True:
 message = input("enter your message: ")
 if message == 'CLOSE SOCKET':
        client_socket.send(message.encode('utf-8'))
        client_socket.close()
        break
 else:
     client_socket.send(message.encode('utf-8'))
     response = client_socket.recv(1024)
     dec_response= response.decode('utf-8')
     print("Received from server is:", dec_response)
    
