# 这是一个示例 Python 脚本。

# 按 Shift+F10 执行或将其替换为您的代码。
# 按 双击 Shift 在所有地方搜索类、文件、工具窗口、操作和设置。

import filediff
import os

def print_hi():
    # 在下面的代码行中使用断点来调试脚本。

    for file in os.listdir("./src"):
        filediff.fileDiff("./src/" + file)


# 按间距中的绿色按钮以运行脚本。
if __name__ == '__main__':
    print_hi()

# 访问 https://www.jetbrains.com/help/pycharm/ 获取 PyCharm 帮助
