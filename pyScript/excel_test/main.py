# 这是一个示例 Python 脚本。
import os
import sys

# 按 Shift+F10 执行或将其替换为您的代码。
# 按 双击 Shift 在所有地方搜索类、文件、工具窗口、操作和设置。
import excelManager
import assert_excise
import login
import GUI_excise
import BookExcise

def main(argv):
    # 在下面的代码行中使用断点来调试脚本。
    # excelManger = excelManager.excelManager()
    # filename = input("输入你的文件名: ")
    # print(f"filename = {filename}")
    # excelManger.read(filename)

    # GUI_excise.windowsShow(argv)
    BookExcise.excise3("test.xlsx")
# 按间距中的绿色按钮以运行脚本。
if __name__ == '__main__':
    main(sys.argv)
    # os.system("pause")

# 访问 https://www.jetbrains.com/help/pycharm/ 获取 PyCharm 帮助
