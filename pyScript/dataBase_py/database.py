import pymysql

def queryDb(m_host,m_user,m_passwd,m_db):
    db = pymysql.connect(host=m_host, user=m_user, password=m_passwd, database=m_db);

    curosr = db.cursor()

    curosr.execute("SELECT * FROM phone WHERE name = '徐伟镇';")

    datas = curosr.fetchall();

    for data in datas:
        id      = data[0]
        name    = data[1]
        phone   = data[2]

        print(f"id: {id}\tname: {name}\tphone: {phone}")

    db.close()