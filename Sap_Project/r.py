#import requests
import time
import json
import sys
import urllib2
first, second = 55.826090, 37.387760
third,fourth = 55.825867,  37.389916
n  = 10
#import urllib2
#TOKEN1 = "72aa5381427f62e323ac3a7be704e7d"

TOKEN = "3a1b3115bfc3bd1cb1e68f1f48b01be9"
#NAME_ACCOUNT = "1942369040trial"
MESSAGE = "ec0ed02c5e42f9b71f59"

MESSAGE_DEVICE = "77933d28-960b-42e9-8042-d41d93847327"



TOKEN_1 = "3a1b3115bfc3bd1cb1e68f1f48b01be9"
#NAME_ACCOUNT = "1942369040trial"
MESSAGE_1 = "1868b4c60d23c9c1c773"

MESSAGE_DEVICE_1 = "77933d28-960b-42e9-8042-d41d93847327"


def send_data_urllib(lat, lon):
    headers = {
        "Authorization": "Bearer {token}".format(token=TOKEN),
        "Content-Type": "application/json;charset=UTF-8",
    }
#"https://iotmmsacb46ba78.hana.ondemand.com/com.sap.iotservices.mms/v1/api/http/app.svc/"
    url = "https://iotmmsacb46ba78.hana.ondemand.com/com.sap.iotservices.mms/v1/api/http/data/{device}". \
        format(device = MESSAGE_DEVICE)

    data = {
        "mode": "async",
        "messageType": MESSAGE,
        "messages": [
            {
               # "timestamp": int(time.time()),
                "Latitude": round(float(lat), 6),
                "Longtitude": round(float(lon), 6),
            }
        ]
    }

    req = urllib2.Request(url, json.dumps(data), headers)
    response = urllib2.urlopen(req)
    return response.code

def send_data_urllib_S(temp,light,hum,id ):
    headers = {
        "Authorization": "Bearer {token}".format(token=TOKEN),
        "Content-Type": "application/json;charset=UTF-8",
    }
#"https://iotmmsacb46ba78.hana.ondemand.com/com.sap.iotservices.mms/v1/api/http/app.svc/"
    url = "https://iotmmsacb46ba78.hana.ondemand.com/com.sap.iotservices.mms/v1/api/http/data/{device}". \
        format(device = MESSAGE_DEVICE)

    data = {
        "mode": "async",
        "messageType": MESSAGE_1,
        "messages": [
            {
               # "timestamp": int(time.time()),
                "Temperature": temp,
                "Light": light,
                "Humidity": hum,
                "ID": id,
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
    #lat = sys.argv[-2]
    #lon = sys.argv[-1]
    # status = send_data(lat, lon)
    ##a = {55.826068:37.387976,55.826045:37.388191,55.826023:37.388407,55.826001:37.388622,55.825979:37.388838,55.825956:37.389054,55.825934:37.389269,55.825912:37.389485,55.825889:37.3897,55.825867:37.389916}
    #coordinates(first, second, third, fourth, n)
    #send_data_urllib(100,100)
    send_data_urllib_S(123,34,54,1)
    #print(status)