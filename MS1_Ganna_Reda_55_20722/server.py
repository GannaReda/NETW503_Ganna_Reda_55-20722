import socket
import threading

PORT = 5605
ADDR = ('127.0.0.1', PORT)
clients_info=[]
info=[]

def threaded(conn, addr):
    print("[NEW CONNECTION] " + str(addr) + " connected.")
    info=[conn,addr]
    clients_info.append(info)

    while True:
        message = conn.recv(1024).decode('utf-8')
        print(f"Received message from {addr}: {message}")
        if message == 'CLOSE SOCKET':
                for info in clients_info:
                    if info[1] == addr:
                        clients_info.remove(info)
                        print(f"[CONNECTION CLOSED] {addr}")
                        conn.close()
                        break
        else :
          response = message.upper()
          conn.send(response.encode('utf-8'))

def main():
    print("Server is starting...")
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(ADDR)
    server.listen()
    while True:
        conn, addr = server.accept()
        threading.Lock().acquire()
        thread=threading.Thread(target=threaded, args=(conn, addr))
        thread.start()
        print(f"[ACTIVE CONNECTIONS] {threading.activeCount() - 1}")

if __name__ == "__main__":
    main()
