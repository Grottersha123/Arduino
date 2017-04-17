#import requests
import time
import json
import sys
import urllib2
import TOKENS
first, second = 55.826090, 37.387760
third,fourth = 55.825867,  37.389916
n  = 10
#TOKEN1 = "72aa5381427f62e323ac3a7be704e7d"

"""TOKEN = "115666ccda8e12ffcd176f9a2c14b72"
NAME_ACCOUNT = "1942369040trial"
MESSAGE = "289ffc0c7adba1446c17"

MESSAGE_DEVICE = "9d791d17-f73f-47d7-941b-69ea6c670939"""


def send_data_urllib(lat, lon):
    headers = {
        "Authorization": "Bearer {token}".format(token=TOKENS.TOKEN),
        "Content-Type": "application/json;charset=UTF-8",
    }

    url = "https://iotmmsp{account}.hanatrial.ondemand.com/com.sap.iotservices.mms/v1/api/http/data/{device}". \
        format(account=TOKENS.NAME_ACCOUNT,device = TOKENS.MESSAGE_DEVICE)

    data = {
        "mode": "async",
        "messageType": TOKENS.MESSAGE,
        "messages": [
            {
                "timestamp": int(time.time()),
                "Latitude": round(float(lat), 6),
                "Longitude": round(float(lon), 6),
            }
        ]
    }

    req = urllib2.Request(url, json.dumps(data), headers)
    response = urllib2.urlopen(req)
    return response.code
def send_data_urllib_T(lat, lon):
    headers = {
        "Authorization": "Bearer {token}".format(token=TOKENS.TOKEN),
        "Content-Type": "application/json;charset=UTF-8",
    }

    url = "https://iotmmsp{account}.hanatrial.ondemand.com/com.sap.iotservices.mms/v1/api/http/data/{device}". \
        format(account=TOKENS.NAME_ACCOUNT,device = TOKENS.MESSAGE_DEVICE)

    data = {
        "mode": "async",
        "messageType": TOKENS.MESSAGE_1,
        "messages": [
            {
                "timestamp": int(time.time()),
                "Lat": round(float(lat), 6),
                "Lon": round(float(lon), 6),
            }
        ]
    }

    req = urllib2.Request(url, json.dumps(data), headers)
    response = urllib2.urlopen(req)
    return response.code
def send_data_urllib_A(id,hum,light,temp):
    headers = {
        "Authorization": "Bearer {token}".format(token=TOKENS.TOKEN),
        "Content-Type": "application/json;charset=UTF-8",
    }

    url = "https://iotmmsp{account}.hanatrial.ondemand.com/com.sap.iotservices.mms/v1/api/http/data/{device}". \
        format(account=TOKENS.NAME_ACCOUNT,device = TOKENS.MESSAGE_DEVICE)

    data = {
        "mode": "async",
        "messageType": TOKENS.MESSAGE_2,
        "messages": [
            {
                "ID": int(id),
                "Humanity": round(float(hum),3 ),
                "Light": round(float(light), 3),
                "Temperature" : round(float(temp),3)
            }
        ]
    }

    req = urllib2.Request(url, json.dumps(data), headers)
    response = urllib2.urlopen(req)
    return response.code
def coordinates(first, second, third, fourth, n):
    del1 = (third - first) / n
    del2 = (fourth - second) / n
    for i in range(0, n):
        first += del1
        second += del2
        status = send_data_urllib(first ,second)
        print(status)
if __name__ == "__main__":
    lat = sys.argv[-6]
    lon = sys.argv[-5]
    id = sys.argv[-4]
    hum = sys.argv[-3]
    light = sys.argv[-2]
    temp = sys.argv[-1]

    status_g = send_data_urllib_T(lat, lon)
    status_s = send_data_urllib_A(id,hum,light,temp)
    ##a = {55.826068:37.387976,55.826045:37.388191,55.826023:37.388407,55.826001:37.388622,55.825979:37.388838,55.825956:37.389054,55.825934:37.389269,55.825912:37.389485,55.825889:37.3897,55.825867:37.389916}
    #coordinates(first, second, third, fourth, n)

    print(status_g,status_s)
