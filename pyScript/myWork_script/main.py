#用于数据库导入数据生成excel表使用

from fileinput import filename
import os

import database
import excelOper
import config

if __name__ == '__main__':
    Conf = config.configs
    
    dataBaseInfoConf    = "dataBaseInfo"
    host                = Conf[dataBaseInfoConf]["host"]
    user                = Conf[dataBaseInfoConf]["user"]
    password            = Conf[dataBaseInfoConf]["password"]
    db                  = Conf[dataBaseInfoConf]["database"]
    
    filename            = Conf["fileInfo"]["fileName"]
    
    datas = database.loadDataBaseInfo(host,user,password,db,"phone")
    
    excelOper.writeExcel(datas,filename)
    
    print("数据导入完成!!!")