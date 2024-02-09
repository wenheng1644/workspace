import socket
import sys

import struct

import google.protobuf
import chatcmd_pb2
import time

def makeCmdHead(cmdtype, cmd_subtype, cmdlen, sendtime, version, checkcode):
    headcmd = struct.pack("=B B I Q B H", cmdtype, cmd_subtype, cmdlen, sendtime, version, checkcode)
    print(f"makeCmdHead | len headcmd = {len(headcmd)}")
    return headcmd

class Client:
    def __init__(self):
        self.fd = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
        
    def connect(self,addr, port):
        self.fd.connect((addr, port))
        
    def send(self, contents):
        
        bodycmd = chatcmd_pb2.chatMessageCmd()
        bodycmd.content = contents
        bodycmd.status = 3

        body_bytes = bodycmd.SerializeToString()

        timestamp = time.time()
        head_bytes = makeCmdHead(1,1, len(body_bytes), int(timestamp), 0, 122)

        sendbyts = head_bytes + body_bytes
        print(f"发生数据长度 = {len(sendbyts)}, body len = {len(body_bytes)}")

        b = self.fd.send(sendbyts)
        print(f"已发送字节数 = {b}")
        
    def recv(self):
        msg = self.recv()
        print(f"msg = {msg}, len = {len(msg)}")