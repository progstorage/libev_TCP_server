import socket

HOST = "127.0.0.1"
PORT = 5000

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
    client_socket.connect((HOST, PORT))
    print("Connected to the server successfully!")

    while True:
        message = input("Enter a message (or 'exit' to quit): ")
        if message.lower() == "exit":
            break

        client_socket.sendall(message.encode())
        data = client_socket.recv(1024)
        print(f"Server response: {data.decode()}")
