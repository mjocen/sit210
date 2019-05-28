import RPi.GPIO as GPIO
import datetime
import time
import jwt
import paho.mqtt.client as mqtt
import sys
import Adafruit_DHT as DHT


ssl_private_key_filepath = '/home/pi/demo_private.pem'
ssl_algorithm = 'RS256' # Either RS256 or ES256
root_cert_filepath = '/home/pi/roots.pem'
project_id = 'photon-rasppberry-project'
gcp_location = 'asia-east1'
registry_id = 'my-registry'
device_id = 'raspJ'


# GPIO setup
# LED output
water = 16
light = 20
channel = 4
tmph = 17

GPIO.setmode(GPIO.BCM)
GPIO.setup(water, GPIO.OUT)
GPIO.setup(light, GPIO.OUT)

GPIO.setup(channel, GPIO.IN)
GPIO.setup(tmph, GPIO.IN)

cur_time = datetime.datetime.utcnow()

def create_jwt():
  token = {
      'iat': cur_time,
      'exp': cur_time + datetime.timedelta(minutes=60),
      'aud': project_id
  }

  with open(ssl_private_key_filepath, 'r') as f:
    private_key = f.read()

  return jwt.encode(token, private_key, ssl_algorithm)

_CLIENT_ID = 'projects/{}/locations/{}/registries/{}/devices/{}'.format(project_id, gcp_location, registry_id, device_id)
_MQTT_TOPIC = '/devices/{}/events'.format(device_id)

client = mqtt.Client(client_id=_CLIENT_ID)
# authorization is handled purely with JWT, no user/pass, so username can be whatever
client.username_pw_set(
    username='unused',
    password=create_jwt())

def error_str(rc):
    return '{}: {}'.format(rc, mqtt.error_string(rc))

def on_connect(unusued_client, unused_userdata, unused_flags, rc):
    print('on_connect', error_str(rc))

def on_publish(unused_client, unused_userdata, unused_mid):
    print('on_publish')

def callback(channel):
    if GPIO.input(channel):
        GPIO.output(water, GPIO.HIGH)
        print("no water detected")
    else:
        print("water detected")
        GPIO.output(water, GPIO.LOW)

def todayAt(hr, mins=0, secs=0, micros=0):
  now = datetime.datetime.now()
  return now.replace(hour=hr, minute=mins, second=secs, microsecond=micros)

def todayCompare(dt):
  early = todayAt(6, 30)
  late = todayAt(17, 30)

  if dt > early and dt < late:
    return True
  else:
    return False



GPIO.add_event_detect(channel, GPIO.BOTH, bouncetime=300)
GPIO.add_event_callback(channel, callback)

temperature = 0
humidity = 0

try:
    while True:
        cur_hum, cur_temp = DHT.read_retry(11,tmph)
        now_time = datetime.datetime.now()
        sw_light = todayCompare(now_time)

        if (sw_light):
            GPIO.output(light, GPIO.HIGH)
        else:
            GPIO.output(light, GPIO.LOW)
        

        if (cur_temp == temperature and cur_hum == humidity):
            time.sleep(1)
            continue

        temperature = cur_temp
        humidity = cur_hum
        pr_time = cur_time.strftime('%H:%M:%S')

        payload = '{{ "ts:" {}, "time:" {}, "temperature": {}, "humidity": {} }}'.format(int(time.time()),pr_time, temperature, humidity)

        client.publish(_MQTT_TOPIC, payload, qos=1)
        print("{}\n".format(payload))

        time.sleep(1)
        
except KeyboardInterrupt:
    GPIO.cleanup()

client.loop_stop()
