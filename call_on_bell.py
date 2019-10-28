import wiringpi
import requests
import plivo

wiringpi.wiringPiSetupGpio()
wiringpi.pinMode(17,0)
wiringpi.pinMode(27,1)

auth_id = "MANWFIYMJJMDY0ZMNMZD"
auth_token = "ODJiMDIwNzc0YzZiOTUzYzE2OTU4Y2U3YWExNWU3"

plivo = plivo.RestClient(auth_id, auth_token)


while 1:
  if wiringpi.digitalRead(17) == 0:
    wiringpi.delay(200)
    if wiringpi.digitalRead(17) == 0:
      #print("Button pressed")
      wiringpi.digitalWrite(27,1)
      # Make an outbound call and print the response
      response = plivo.calls.create(
          from_='+919640551703',
          to_='+917406849484',
          answer_url='http://plivo.devmaiti.com/plivo.xml',
          answer_method='GET'
      )
      ifttt_req = requests.post('https://maker.ifttt.com/trigger/bell_rang/with/key/bAlWaq1XqBRa1FAOHXpmxx')
      wiringpi.digitalWrite(27,0)
      wiringpi.delay(1000)