import json
import os
import getpass

filename = "loginload.json"

def checkLoadFile():
    if not os.path.exists(filename):
        with open(filename, "w") as f:
            json.dump([], f)


def readLoginData():
    checkLoadFile()
    with open(filename) as f:
        datas = json.load(f)

    return datas

def writeToLoginData(datas):
    with open(filename, "w") as f:
        json.dump(datas, f)


def zhuceAccount(name, code):
    datas = readLoginData()
    data = {"name": name, "code": code}
    datas.append(data)

    writeToLoginData(datas)

def findAccount(name):
    datas = readLoginData()

    for index, data in enumerate(datas):
        if data["name"] == name:
            return True, data["code"], index
    return False, None, -1


def login():
    checkLoadFile()
    name = input("what's your name?: ")

    isFind, code = findAccount(name)

    if not isFind:
        enter_code = getpass.getpass("zhu ce your new account, enter your new code: ")
        zhuceAccount(name, enter_code)
        print(f"ok, zhu ce successfully, {name}: {enter_code}")
    else:
        enter_code = getpass.getpass("enter your code now: ")
        if enter_code == code:
            print(f"welcome back, {name}")
        else:
            print(f"enter wrong code: {enter_code}, goodbye...")




