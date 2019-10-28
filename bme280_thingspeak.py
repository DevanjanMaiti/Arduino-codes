import wiringpi
import urllib2
import requests
import smbus2
import bme280
import plivo

wiringpi.wiringPiSetup()

myAPI = 'MWHPXY032EYIMHOP'
thingspeakURL = 'https://api.thingspeak.com/update?api_key=%s' % myAPI

auth_id = "MANWFIYMJJMDY0ZMNMZD"
auth_token = "ODJiMDIwNzc0YzZiOTUzYzE2OTU4Y2U3YWExNWU3"

plivo = plivo.RestClient(auth_id, auth_token)

port = 1
address = 0x76
bus = smbus2.SMBus(port)

calibration_params = bme280.load_calibration_params(bus, address)

# Make an outbound call
response = plivo.calls.create(
    from_='+919640551703',
    to_='+917406849484',
    answer_url='http://plivo.devmaiti.com/plivo.xml',
    answer_method='GET'
)

while 1:
  data = bme280.sample(bus, address, calibration_params)
  temp = data.temperature
  temp = '%.3f' % temp
  #print(temp)
  conn = urllib2.urlopen(thingspeakURL + '&field1=%s' % (temp))
  #print conn.read()
  conn.close()
  ifttt_req = requests.post('https://maker.ifttt.com/trigger/temperature_read/with/key/bAlWaq1XqBRa1FAOHXpmxx',params={"value1" : temp})
  wiringpi.delay(3600000)
  #wiringpi.delay(20000)



# the compensated_reading class has the following attributes
#print(data.id)
#print(data.timestamp)
#print(data.temperature)
#print(data.pressure)
#print(data.humidity)

# there is a handy string representation too
#print(data)