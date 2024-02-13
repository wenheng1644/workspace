import sys
import client
import random
import time
import threading

def test__():
    c = client.Client()
    c.connect("192.168.147.194", 8888)
    
    
    while True:
        content = input("content:")
        if not content:
            print("请输入内容")
            continue
        if content == "q" or content == "Q":
            print("输入终止")
            break
    
        c.send(content)
    c.fd.close()


contents = ["hello linux", "这是测试11111111",  "服务器测压..."]
def clinetToTest():
    c = client.Client()
    c.connect("192.168.31.145", 8888)

    while True:
        i = random.randint(0, len(contents) - 1)
        content = contents[i]

        c.send(content)

        randV = random.randint(100, 1000)
        print(f"睡眠 {randV / 1000}秒")
        time.sleep(randV / 1000)


def testserver():
    num = 5000
    threads = list()
    for i in range(1, num):
        t = threading.Thread(target=clinetToTest)
        threads.append(t)
        t.start()

    # for t in threads:
    #     t.start()

def main():
    print("hello python!!!")
    # testserver()
    test__()
    
    
    
if __name__ == "__main__":
    main()