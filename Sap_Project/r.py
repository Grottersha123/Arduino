import requests
import time
import json
import sys
import urllib
from urllib.request import *
#import urllib2

TOKEN = "115666ccda8e12ffcd176f9a2c14b72"
NAME_ACCOUNT = "1942369040trial"
MESSAGE = "289ffc0c7adba1446c17"


def send_data(lat, lon):
    headers = {
        "Authorization": "Bearer {token}".format(token=TOKEN),
        "Content-Type": "application/json;charset=UTF-8",
    }

    url = "https://iotmmsp{account}.hanatrial.ondemand.com/com.sap.iotservices.mms/v1/api/http/data/9d791d17-f73f-47d7-941b-69ea6c670939". \
        format(account=NAME_ACCOUNT)

    data = {
        "mode": "async",
        "messageType": "289ffc0c7adba1446c17",
        "messages": [
            {
                "timestamp": int(time.time()),
                "Latitude": round(float(lat), 6),
                "Longitude": round(float(lon), 6),
            }
        ]
    }

    r = requests.post(
        url=url,
        json=data,
        headers=headers,
    )
    return r.status_code


def send_data_urllib(lat, lon):
    headers = {
        "Authorization": "Bearer {token}".format(token=TOKEN),
        "Content-Type": "application/json;charset=UTF-8",
    }

    url = "https://iotmmsp{account}.hanatrial.ondemand.com/com.sap.iotservices.mms/v1/api/http/data/9d791d17-f73f-47d7-941b-69ea6c670939". \
        format(account=NAME_ACCOUNT)

    data = {
        "mode": "async",
        "messageType": "289ffc0c7adba1446c17",
        "messages": [
            {
                "timestamp": int(time.time()),
                "Latitude": round(float(lat), 6),
                "Longitude": round(float(lon), 6),
            }
        ]
    }

    req = Request(url, json.dumps(data), headers)
    response = urlopen(req)
    return response.code


if __name__ == "__main__":
    lat = sys.argv[-2]
    lon = sys.argv[-1]
    # status = send_data(lat, lon)
    status = send_data_urllib(lat, lon)
    print(status)
