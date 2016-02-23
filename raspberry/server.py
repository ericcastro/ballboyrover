import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), './lib'))

import serial
import asyncore
import socket

ser = serial.Serial(
    port='/dev/ttyAMA0',
    baudrate=9600,
#    parity=serial.PARITY_ODD,
#    stopbits=serial.STOPBITS_TWO,
#    bytesize=serial.SEVENBITS
)


class CommandForwarder(asyncore.dispatcher_with_send):

    def handle_read(self):
        data = self.recv(8192)
        if data:
            self.send(data)
            ser.write(data)


class CommandServer(asyncore.dispatcher):

    def __init__(self, host, port):
        asyncore.dispatcher.__init__(self)
        self.create_socket(socket.AF_INET, socket.SOCK_STREAM)
        self.set_reuse_addr()
        self.bind((host, port))
        self.listen(5)

    def handle_accept(self):
        pair = self.accept()
        if pair is not None:
            sock, addr = pair
            print 'Incoming connection from %s' % repr(addr)
            handler = CommandForwarder(sock)

server = CommandServer('0.0.0.0', 5555)

ser.open()

try:
    asyncore.loop()

except KeyboardInterrupt:
    server.close()
    ser.close()
