import sys
import shutil_test
import listDir

def main(argv):
    print("argv: ", argv)
    # shutil_test.copy1()
    listDir.listDir("E:\\", "刻晴")
    # shutil_test.test_zip("./desDir/甘雨.zip")

    # shutil_test.deleteTrash(".", ".jpeg")

if __name__ == "__main__":
    main(sys.argv)

