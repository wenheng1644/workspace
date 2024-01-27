import sys
import client

def test__():
    c = client.Client()
    c.connect("192.168.31.26", 8888)
    
    datas = b"111111111111111111111111111"
    c.send(datas)
    
    while True:
        content = input("content:")
        if not content:
            print("请输入内容")
            continue
        if content == "q" or content == "Q":
            print("输入终止")
            break
    
        send_bytes = bytes(content, encoding='utf-8')
        c.send(send_bytes)
    c.fd.close()


def main():
    print("hello python!!!")
    test__()
    
    
    
if __name__ == "__main__":
    main()