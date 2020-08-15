#!/usr/bin/env python

# import socket
from socket import socket, AF_INET, SOCK_STREAM


class EthernetInterface:

    def __init__(self, ip, port):
        ip_server = ip
        port = port
        self.socket_handle = socket(AF_INET, SOCK_STREAM)
        self.socket_handle.connect((ip_server, port))

    def __del__(self):
        self.socket_handle.close()

    def send(self, message):
        self.socket_handle.send(message.data)

    def receive(self):
        return self.socket_handle.recv(1024)
