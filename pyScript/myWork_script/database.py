from re import U
import pymysql

def loadDataBaseInfo(host,user,passwd,db,tb,sql = None):
    conn = pymysql.connect(host = host, user = user, password = passwd, database = db)
    if not conn:
        print("数据库连接出错!!!")
        exit()
    
    curosr = conn.cursor()
    
    if not curosr:
        print("获取游标失败...")
        exit()

    datas = None
    if sql:
        curosr.execute(sql)
        datas = curosr.fetchall()
    else:
        curosr.execute(f"SELECT * FROM {tb}")
        datas = curosr.fetchall()
        
    return datas         
    