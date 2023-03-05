import os

def readFile(filename):
    path = os.getcwd()
    print(f"current work dir = {path}")
    filename = path + f"\\{filename}"
    if not os.path.exists(filename):
        print("this file: " + filename + "not exist")
        return
    print(f"cur filename = {filename}")
    fd = open(filename, "r")
    if not fd:
        print("can't open this file: " + filename)

    i = 1
    for line in fd:
        print(f"line{i}: {line}")
        i = i + 1

    fd.close()

def writeFile():
    filename = input("input your filename:")
    while filename == "":
        print("filename is empty, please enter again")
        filename = input("input your filename:")

    fd = open(filename, "w")
    if not fd:
        print("fd open error")
        return

    while True:
        str = input("your input:")
        if str == "q" or str == "Q":
            print("input end")
            break
        print(f"line str = {str}")
        fd.write(str + "\n")

    fd.close()


def listDir():
    dir = "."
    if type(dir) != str or dir == "":
        print(f"dir =  {dir}, type(dir) = {type(dir)}")
        return

    if not os.path.exists(dir):
        print(f"{dir} not exist")
        return

    for fd in os.listdir(dir):
        if os.path.isdir(fd):
            print(f"{fd} is dir")
        if os.path.isfile(fd):
            print(f"f{fd} is file")

def listDir2():
    dir = os.getcwd()
    print(f"current dir = {dir}")

    for root, dirs, filenames in os.walk(dir):
        print(f"root = {root}")
        if filenames:
            print("files: ")
            for file in filenames:
                print(f"file = {file}")

        if dirs:
            print("dirs: ")
            for dir in dirs:
                print(f"dir = {dir}")

