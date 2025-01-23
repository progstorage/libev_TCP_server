import socket

def main():
    HOST = '127.0.0.1'
    PORT = 5000

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        s.sendall(b'Test message')
        data = s.recv(1024)
        print('Received', repr(data))

if __name__ == "__main__":
    main()
