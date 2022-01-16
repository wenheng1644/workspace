import openpyxl,pprint
import src.products

def writeToExcel(filename):
    wb = openpyxl.load_workbook(filename)
    print(wb.get_sheet_names())
    sheet = wb.active
    print(f"old title: {sheet.title}")
    sheet.title = "test"
    print(wb.get_sheet_names())
    # wb.save("./src/write1.xlsx")
    mysheet = wb.create_sheet("first_sheet",0)
    print(wb.get_sheet_names())
    mysheet['A1'].value = "hello mygirl"
    mysheet['C3'].value = "刘烨仪"
    wb.save(filename)

def project_write(filename = None):
    proConf = src.products.products
    print(pprint.pformat(proConf))


    wb = openpyxl.load_workbook("./src/produceSales.xlsx")
    sheet = wb.get_sheet_by_name("Sheet")

    for rowNum in range(2,sheet.max_row + 1):
        productName = sheet.cell(rowNum,1).value
        if productName in proConf:
            sheet.cell(rowNum,2).value = proConf[productName]

    wb.save("./src/copy_product.xlsxS")
