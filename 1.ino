#include "DHT.h"
#include "DFRobot_RGBLCD1602.h"


#define DHTPIN 2
#define DHTYPE DHT11

char charVal[10];

DHT dht (DHTPIN, DHTYPE);

char Sub[10] = {'A','B','C','D','E','F','G','H','J','K'};
DFRobot_RGBLCD1602 lcd(/*RGBAddr*/0x60 ,/*lcdCols*/16,/*lcdRows*/2);  //16 characters and 2 lines of show

String msg = "99.99";

int button = 13;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(button,INPUT_PULLUP);

  lcd.init();
  lcd.print("Hello!");
  delay(500);
  lcd.clear();
}

void encrypt(String bruh){
  
  int msgLength = bruh.length();
  String dataEncrypt[5];

  for (int i = 0; i < msgLength; i++){
    if (bruh[i]=='.'){
      dataEncrypt[i]='.';}
    else{
      int pain = bruh[i]-'0';
      dataEncrypt[i] = Sub[pain];}
    
    delay(30);
    Serial.print(dataEncrypt[i]);
    delay(30);
    lcd.print(dataEncrypt[i]);
    }
}

void loop() {
  if(digitalRead(button)==0) {
    float t = dht.readTemperature();

    msg = String(t,1);
    lcd.print(msg);
    delay(30);
    lcd.clear();
    encrypt(msg);
    }
  }
