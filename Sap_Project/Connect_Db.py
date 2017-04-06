import pyhdb
""""Instance number  :
  User             : DEV_3EDSG495VBCTM0XHQYAWFMT82
  Password         : Iu7dJcyRawHqqIq
"""
connection = pyhdb.connect(host="localhost",port=30015,user="DEV_3EDSG495VBCTM0XHQYAWFMT82", password="Iu7dJcyRawHqqIq")
cursor = connection.cursor()

cursor.execute("select C_LAT,C_LON from NEO_114I6H15R6HTHNY9ZXGJO4RE6.T_IOT_281DD4F1519D9EF19E17")


tables = cursor.fetchall()
print(tables)
