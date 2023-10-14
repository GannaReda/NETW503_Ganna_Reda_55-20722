import socket
import select
import sys
server_socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
port=5608
server_socket.bind(('127.0.0.1',port))
server_socket.listen(5)
while True :
 client,add = server_socket.accept()
 while True:
  message=client.recv(1024)
  decoded_message = message.decode('utf-8')
  if decoded_message == "CLOSE SOCKET":
   client.close()
   break
  else:
   print("Received message is: ", decoded_message)
   response=decoded_message.upper()
   client.send(response.encode('utf-8'))
   if decoded_message == "CLOSE SOCKET":
    client.close()



