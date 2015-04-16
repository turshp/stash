#! /usr/bin/env python

"""
client of kshd.
"""

import socket

def do_shell(cmd, host, port = 44444):
    BUFSIZE = 4096

    tcpCliSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcpCliSock.connect((host, port))
    tcpCliSock.send(cmd)
    output = ''
    while True:
        data = tcpCliSock.recv(BUFSIZE)
        if not data:
            break
        output += data

    tcpCliSock.close()
    return output


