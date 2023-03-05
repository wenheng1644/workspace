import os.path
import shutil
import zipfile

import send2trash

copyDir = "./desDir"

def copy1():
    print(shutil.copy(__file__, copyDir))

def test_zip(zipFilename):
    exampleZip = zipfile.ZipFile(zipFilename)

    for name in exampleZip.namelist():
        info = exampleZip.getinfo(name)

        print(f"name = {name} and % = {round(info.compress_size /info.file_size, 2)}")

    # extractall
    exampleZip.extractall(copyDir)
    exampleZip.close()

def deleteTrash(path, endwiths):
    if not os.path.exists(path):
        return

    for foldername, subfolders, filenames in os.walk(path):
        print(f"current foldername = {foldername}")

        for filename in filenames:
            if str(filename).endswith(endwiths):
                print(f"filename = {filename}")
                send2trash.send2trash(foldername + '\\'+filename)


