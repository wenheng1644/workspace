import os

def listDir(path, targetname,endwiths = None):

    for foldername, subFolders,filenames in os.walk(path):
        print(f"current folder = {foldername}")

        for filename in filenames:
            # print(f"filename = {foldername}\\{filename} ")
            if filename == targetname:
                print(f"完整路径: {foldername}\\{filename}")
                return

        # for folder in subFolders:
            # print(f"folder = {foldername}\\{folder}")
    print(f"没有该文件: {targetname}")