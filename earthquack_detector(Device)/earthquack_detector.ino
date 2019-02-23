#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
const int buzzer1 = 9; //buzzer to arduino pin 9
const int buzzer2 = 10; //buzzer to arduino pin 10

SoftwareSerial esp(7, 6);// RX, TX
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
String ssid ="john";
String password="asdcxz12345";
String server = "circuitbreakers.000webhostapp.com"; // www.example.com
String uri = "/collector.php";// page

const int PIEZO_PIN = A0; // Piezo output
int piezoADC;
int data;
String vibration;
//reset the esp8266 module

void reset() {
  lcd.setCursor(0, 1);
lcd.print("Reset Begin");
esp.println("AT+RST");


delay(1000);

if(esp.find("OK") ) { 
Serial.println("Module Reset");
lcd.setCursor(0, 1);
lcd.print("Module Reset");
}

}

//connect to your wifi network

void connectWifi() 
{

Serial.println("Connecting.....");
lcd.setCursor(0, 1);
lcd.print("Connecting.....");

String cmd = "AT+CWJAP=\"" +ssid+"\",\"" + password + "\"";

esp.println(cmd);

delay(4000);

if(esp.find("OK")) {

Serial.println("Connected!");
lcd.setCursor(0, 1);
lcd.print("Connected!");


}

else {

connectWifi();

Serial.println("Cannot connect to wifi");
lcd.setCursor(0, 1);
lcd.print("Cannot connect to wifi");
 }

}

void alert ()
 {
  for (int i = 0; i < 10; i ++) {
    lcd.setCursor(0, 0);
lcd.print(" Earthqake ....");
lcd.setCursor(0, 1);
lcd.print("Leave this Place");
    tone(buzzer1, 1000); // Send 1KHz sound signal...
    delay(200);        // ...for  sec
     noTone(buzzer1);     // Stop sound...
     delay(100);        // ...for 1sec
    
    tone(buzzer2, 1000); // Send 1KHz sound signal...
    delay(200);        // ...for  sec
     noTone(buzzer2);     // Stop sound...
     delay(100);        // ...for 1sec
      lcd.clear();
    
  }
}

int read_data () 
{

piezoADC = analogRead(PIEZO_PIN);
 
  //float piezoV = piezoADC / 1023.0 * 5.0;
  /* Serial.println(piezoV); // Print the voltage. */
  
  if(piezoADC >= 0.001)
  {
    Serial.println(piezoADC); // Print the reading.
    lcd.setCursor(0, 1);
  lcd.print(piezoADC);
  alert();
   lcd.clear();
  return piezoADC;
  }
  else
  {
  Serial.println(piezoADC); // Print the reading.
  lcd.setCursor(0, 1);
  lcd.print(piezoADC);
  }
 }

void httppost () {
  
Serial.println("Connecting to Server");
lcd.setCursor(0, 1);
lcd.print("Connecting to Server");

esp.println("AT+CIPSTART=\"TCP\",\"" + server + "\",80");//start a TCP connection.

if( esp.find("OK")) {

Serial.println("TCP connection ready");
lcd.setCursor(0, 1);
lcd.print("TCP connection ready");

} delay(1000);

String postRequest =

"POST " + uri + " HTTP/1.0\r\n" +

"Host: " + server + "\r\n" +

"Accept: *" + "/" + "*\r\n" +

"Content-Length: " + vibration.length() + "\r\n" +

"Content-Type: application/x-www-form-urlencoded\r\n" +

"\r\n" + vibration;

String sendCmd = "AT+CIPSEND=";//determine the number of caracters to be sent.

esp.print(sendCmd);

esp.println(postRequest.length() );

delay(500);

if(esp.find(">")) { 
Serial.println("Sending..");
lcd.setCursor(0, 1);
lcd.print("");

 esp.print(postRequest);

if( esp.find("SEND OK")) { 
Serial.println("Packet sent");
lcd.setCursor(0, 1);
lcd.print("");

while (esp.available()) {

String vibResp = esp.readString();

Serial.println(vibResp);

}

// close the connection

esp.println("AT+CIPCLOSE");

}

}}


void setup() {
lcd.begin(16, 2);

esp.begin(9600);

Serial.begin(9600);

pinMode(buzzer1, OUTPUT); // Set buzzer - pin 9 as an output
pinMode(buzzer2, OUTPUT); // Set buzzer - pin 10 as an output

reset();

connectWifi();

}



void loop () {

data = read_data ();
vibration = String(data);

httppost();

delay(1000);

}






