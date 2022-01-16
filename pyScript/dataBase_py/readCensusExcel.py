import openpyxl,pprint

def test_readProject(filename):
    print("opening a workbook~")
    wb = openpyxl.load_workbook(filename)
    sheet = wb.get_sheet_by_name("Population by Census Tract")

    coutyData = {}

    print("reading the row...")

    for row in range(2,sheet.max_row + 1):
        state = sheet['B' + str(row)].value
        couty = sheet['C' + str(row)].value
        pop   = sheet['D' + str(row)].value

        coutyData.setdefault(state,{})
        coutyData[state].setdefault(couty,{"tracts" : 0,"pop" : 0})
        coutyData[state][couty]["tracts"] += 1
        coutyData[state][couty]["pop"] += int(pop)

    print("write the result~~")
    resFile = open("./src/census2010.py","w")
    if resFile:
        resFile.write("allData = " + pprint.pformat(coutyData))
        resFile.close()
    print("done...")
