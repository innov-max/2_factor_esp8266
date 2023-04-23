 

//Prateek
//wwww.prateeks.in
//https://www.youtube.com/c/JustDoElectronics/videos

#include <SoftwareSerial.h>
#include <Wire.h>
#include <Keypad.h>
#define relay 4

const byte ROWS = 4;
const byte COLS = 3;
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {13, 12, 11, 10};
byte colPins[COLS] = {9, 8, 7};
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);


SoftwareSerial sim800l(3, 2);
int irsensor = A0;
int otp;
String otpstring = "";
int i = 0;
void setup()
{

 
  sim800l.begin(4800);
  Serial.begin(115200);
  Serial.print("Welcome to SIM800L Project");
  sim800l.println("AT");
  updateSerial();
  pinMode(relay, OUTPUT);
 
  digitalWrite(relay, LOW);
  delay(500);
  sim800l.println("AT+CSQ");
  updateSerial();
  delay(1000);

}
void updateSerial()
{
  delay(500);
  while (Serial.available()) {
    sim800l.write(Serial.read());
  }
  while (sim800l.available()) {
    Serial.write(sim800l.read());
  }
}
void loop()
{
 
  
    otp = random(2000, 9999);
    otpstring = String(otp);
    Serial.println(otpstring);
    while (digitalRead(irsensor) == LOW) {}

    Serial.print("OTP is ");
    delay(100);
    Serial.println(otpstring);
    delay(100);
    SendSMS();
    getotp();
    delay (20000000);
  

}

void getotp() {

  String y = "";
  int a = y.length();
  while (a < 4)
  {
    char customKey = customKeypad.getKey();
    if (customKey) {
    
      y = y + customKey;
     
      a = y.length();
    }
  }
  Serial.print("Entered OTP is ");
  Serial.println(y);
  if (otpstring == y)
  {
    
    digitalWrite(relay, HIGH);
    delay(5000);
    digitalWrite(relay, LOW);
   
  }
  else
  {
    Serial.println("entered wrong otp");
    delay(3000);
  }


}
void SendSMS()
{
  Serial.println("Sending SMS...");
  sim800l.print("AT+CMGF=1\r");
  delay(100);
  sim800l.print ("AT+CSMP=17,167,0,0\r");
  delay(500);
  sim800l.print("AT+CMGS=\"+254774909759\"\r");
  delay(500);
  sim800l.print("Your OTP is " + otpstring + " Just Type OTP And Unlock The Door");
  delay(500);
  sim800l.print((char)26);
  delay(500);
  sim800l.println();
  Serial.println("Text Sent.");
  delay(500);

}
