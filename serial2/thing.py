#!/opt/local/bin/python

import requests

headers = { 'Accept' :  '*/*',
            'User-agent' : 'Particle HttpClient'}

url = 'http://www.timeapi.org/utc/now'
url = 'http://hotdot.pro/en/404/'

r = requests.get(url,headers=headers)
print r.status_code

791E915460D2903E
