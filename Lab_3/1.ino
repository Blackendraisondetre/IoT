#include "DFRobot_RGBLCD1602.h"
#include <HCSR04.h>
#include "AESLib.h"

#define KEY_SIZE 16
const byte triggerPin = 3;
const byte echoPin = 4;
const int button = 13;

UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);
DFRobot_RGBLCD1602 lcd(/*RGBAddr*/0x60 ,/*lcdCols*/16,/*lcdRows*/2);

byte data[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
byte key[KEY_SIZE] = {0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C};
byte iv[KEY_SIZE] = {0x8C, 0x78, 0x1A, 0xB5, 0x23, 0xBE, 0xF3, 0xAA, 0x01, 0x47, 0x27, 0x12, 0x7A, 0x8B, 0x5D, 0x6C};

void setup() {

  Serial.begin(9600);
  pinMode(button,INPUT_PULLUP);
  lcd.init();
  lcd.print("Hello!");
  delay(500);
  lcd.clear();
}

void loop() {

  if(digitalRead(button)==0) {
    lcd.setCursor(0, 0);
    lcd.print("Distance : ");  
    for (byte i = 0; i < 32; i++) {data[i]=i+1;}
    data[0] = distanceSensor.measureDistanceCm();
    lcd.print(data[0]);    
    lcd.setCursor(0, 1);
    lcd.print("Distance : ");
    aes128_cbc_enc(key, iv, data, 32);
    lcd.print(data[0]);
    Serial.write(data, sizeof(data));
    delay(1000);
    lcd.clear();
    }
}