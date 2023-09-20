#include "DFRobot_RGBLCD1602.h"
#include "AESLib.h"
#include "BigNumber.h"

DFRobot_RGBLCD1602 lcd(0x60, 16, 2);

#define KEY_SIZE 16

byte data[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
byte key[KEY_SIZE] = {0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C};
byte iv[KEY_SIZE] = {0x8C, 0x78, 0x1A, 0xB5, 0x23, 0xBE, 0xF3, 0xAA, 0x01, 0x47, 0x27, 0x12, 0x7A, 0x8B, 0x5D, 0x6C};

int buttonPin = 13;

void setup() {

  pinMode(buttonPin, INPUT_PULLUP);
  lcd.init();
  Serial.begin(9600);
  lcd.print("Pivo");

  
  BigNumber p = 23;
  BigNumber g = 5;

  randomSeed(228);
  int y = random(1, int(p) - 1);

  lcd.print(y);
  delay(2000);

  BigNumber temp = g.pow(y);
  BigNumber Y = temp%p;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Y = ");
  lcd.print(Y);
  
  BigNumber X;
  
  if (Serial.available() < 32) {
    X = Serial.parseInt();
    Serial.print(Y);

    lcd.setCursor(0, 1);
    lcd.print("X = ");
    lcd.print(X);

    temp = X.pow(y);
    BigNumber k = temp%p;

    byte bytes[32];

    for (int i = 0; i < 32; i++) {
      if (i < sizeof(k)) {
        bytes[i] = (k >> (8 * i)) & 0xFF;
      } else {
        bytes[i] = 0;
      }
    }
    for (int i = 0; i < 32; i++) {
      key[i] = bytes[i];
      //lcd.print(key[i]);
    }
    lcd.clear();
    lcd.print("Erfolg");
    delay(500);
    lcd.clear();
  }
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    byte receivedData[32];
    Serial.readBytes(receivedData, sizeof(receivedData));

    lcd.setCursor(0, 0);
    lcd.print("Value : ");
    lcd.print(receivedData[0]);

    aes128_cbc_dec(key, iv, receivedData, sizeof(receivedData));
    
    lcd.setCursor(0, 1);
    lcd.print("Value : ");
    lcd.print(receivedData[0]);

    
  }
  
}
