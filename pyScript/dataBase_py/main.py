# 这是一个示例 Python 脚本。

# 按 Shift+F10 执行或将其替换为您的代码。
# 按 双击 Shift 在所有地方搜索类、文件、工具窗口、操作和设置。
import database
import excl_myoper
import readCensusExcel
import write_excel

def print_hi(name):
    # 在下面的代码行中使用断点来调试脚本。
    print(f'Hi, {name}')  # 按 Ctrl+F8 切换断点。
    # database.queryDb("localhost","root","xwz111598","myinfo")
    # excl_myoper.read_excelTable("./src/example.xlsx",0,0,True)
    # readCensusExcel.test_readProject("./src/censuspopdata.xlsx")
    # write_excel.writeToExcel("./src/write1.xlsx")
    # write_excel.project_write()

    write_excel.excise_excel("./src/lover.xlsx")

# 按间距中的绿色按钮以运行脚本。
if __name__ == '__main__':
    print_hi('PyCharm')

# 访问 https://www.jetbrains.com/help/pycharm/ 获取 PyCharm 帮助
