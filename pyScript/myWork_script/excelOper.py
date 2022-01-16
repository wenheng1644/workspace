import openpyxl,pprint

def writeExcel(datas,filename):
    wb = openpyxl.Workbook()
    sheet = wb.active
    
    print("get datas from database")
    print(pprint.pformat(datas))
    
    for row in range(1,len(datas) + 1):
        for col in range(1,len(datas[row]) + 1):
            sheet.cell(row = row,column = col).value = datas[row][col]
    
    wb.save(filename = filename)