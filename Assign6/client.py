import socket

def echo_client(message):
    # Create a socket object
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    # Connect to the server
    client_socket.connect(('localhost', 5999))
    
    # Send data to the server
    client_socket.sendall(message.encode())
    
    # Receive data from the server
    data = client_socket.recv(1024)
    
    # Print the echoed message
    print("Received:", data.decode())
    
    # Close the connection
    client_socket.close()

if __name__ == "__main__":
    message = input("Enter message to send: ")
    echo_client(message)
