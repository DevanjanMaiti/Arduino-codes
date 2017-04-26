int val;
String cmd;

String cmd1 = "GET /update?key=RCG9Q2D4NO5KRRHF&field1=";
String cmd2 = "&field2="; // NOT USED

void setup() {
  // put your setup code here, to run once:
  pinMode(A0,INPUT);
  Serial.begin(115200);
    
  // reset ESP8266
  Serial.println("AT+RST");
}

void loop() {
  
  delay(15000);

  val = analogRead(A0);
  if (val > 500) {
    digitalWrite(13,HIGH);
  } else {
    digitalWrite(13,LOW);
  }
  
  String string_val = String(val);
  cmd = cmd1;
  cmd += string_val;
  
  Serial.println("AT+CIPSTART=\"TCP\",\"184.106.153.149\",80");
  delay(5000);

  Serial.println("AT+CIPSEND=60");
  delay(5000);

  Serial.println(cmd);
  delay(5000);
    
  Serial.println("AT+CIPCLOSE");

}
