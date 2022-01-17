import openpyxl,pprint,os

def checkFile(filename):
    dir = os.path.dirname(filename)
    print(f"the path: {dir}")

    if not os.path.exists(dir):
        os.makedirs(dir)

def writeExcel(datas,filename):
    wb = openpyxl.Workbook()
    sheet = wb.active

    checkFile(filename)

    print("get datas from database")
    print(pprint.pformat(datas))

    for row in range(0,len(datas)):
        for col in range(0,len(datas[row])):
            sheet.cell(row = row+1,column = col+1).value = datas[row][col]
    
    wb.save(filename = filename)