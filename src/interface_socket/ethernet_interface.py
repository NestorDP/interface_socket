#!/usr/bin/env python

import socket


class EthernetInterface:

    def __init__(self, ip, port):
        ip_server = ip
        port = port
        self.socket_handle = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket_handle.connect((ip_server, port))

    def __del__(self):
        self.socket_handle.close()

    def send(self, message):
        self.socket_handle.send(message.data)
