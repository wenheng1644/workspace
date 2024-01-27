import socket
import sys


class Client:
    def __init__(self):
        self.fd = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
        
    def connect(self,addr, port):
        self.fd.connect((addr, port))
        
    def send(self,datas):
        bytes = self.fd.send(datas)
        print(f"发生数据长度 = {bytes}")
        
    def recv(self):
        msg = self.recv()
        print(f"msg = {msg}, len = {len(msg)}")