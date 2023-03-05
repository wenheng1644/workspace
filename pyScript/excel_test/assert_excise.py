import json
import getpass

def assert_excise():
    num1 = input("number1: ")
    while not num1.isdigit():
        num1 = input("num1 is not a number, please enter again: ")

    num2 = input("number2: ")
    while not num2.isdigit():
        num2 = input("num2 is not a number, please enter again: ")

    num1 = int(num1)
    num2 = int(num2)
    ans = 0
    try:
        ans = num1 / num2
    except ZeroDivisionError:
        print(f"your num2 is zero: {num2}")
        num2 = input("number2: (not zero!!!)")
        while int(num2) == 0:
            num2 = input("number2 (not zero!!!): ")

        ans = num1 / int(num2)

    print(f"ok your ans = {ans}")


def isFile(filename):
    try:
        fd = open(filename, "r")
    except FileNotFoundError:
        # print("your file is not found: {}".format(filename))
        pass
    else:
        for line in fd:
            print(line, end="")

def excise1():
    while True:
        try:
            num1 = input("num1: ")
            num2 = input("num2: ")

            if num2 == "q" or num1 == "q":
                break

            ans = int(num1) + int(num2)
        except ValueError:
            print("not dighit...")
        else:
            print(f"your ans = {ans}")


def excise2():
    filename = "loadfile.json"
    datas = [{"name": "xwz", "sex": "male", "phone": "13424070047"}, {"name": "lyy", "sex": "female", "phone": "?"}]
    with open(filename, "w") as f:
        json.dump(datas, f)

def excise2_load():
    filename = "loadfile.json"
    with open(filename) as f:
        datas = json.load(f)

    print(f"type(datas) = {type(datas)}", datas)
