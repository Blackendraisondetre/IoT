#include "DFRobot_RGBLCD1602.h"
#include "AESLib.h"
#include "BigNumber.h"

DFRobot_RGBLCD1602 lcd(0x60, 32, 2);

#define KEY_SIZE 16

byte data[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
byte key[KEY_SIZE] = {0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C};
byte iv[KEY_SIZE] = {0x8C, 0x78, 0x1A, 0xB5, 0x23, 0xBE, 0xF3, 0xAA, 0x01, 0x47, 0x27, 0x12, 0x7A, 0x8B, 0x5D, 0x6C};

int buttonPin = 13;
int gasSensorPin = 7;

void setup() {

  pinMode(gasSensorPin, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(0, sendStatus, FALLING);
  lcd.init();
  Serial.begin(9600);
  lcd.print("Pivo");
  
  
  BigNumber p = 23;
  BigNumber g = 5;
  
  randomSeed(1337);
  int x = random(1, int(p) - 1);

  lcd.print(x);
  delay(2000);

  BigNumber temp = g.pow(x);
  BigNumber X = temp%p;
  
  Serial.print(X);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("X = ");
  lcd.print(X);

  delay(900);
  BigNumber Y;
  if (Serial.available() < 32) {
    Y = Serial.parseInt();
  
  lcd.setCursor(0, 1);
  lcd.print("Y = ");
  lcd.print(Y);

  temp = Y.pow(x);
  BigNumber k = temp%p;
  lcd.print(k);
  
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
  }
  lcd.clear();
  lcd.print("Erfolg");
  delay(500);
  lcd.clear();
  }
}


void sendStatus() {
  
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    for (byte i = 0; i < 32; i++) {
      data[i]=i+1;
    }
    data[0] = digitalRead(gasSensorPin);
    lcd.setCursor(0, 0);
    lcd.print("Value : ");
    lcd.print(data[0]);
    aes128_cbc_enc(key, iv, data, 32);

    lcd.setCursor(0, 1);
    lcd.print("Value : ");
    lcd.print(data[0]);
    
    Serial.write(data, sizeof(data));

    delay(1000);
    lcd.clear();
  }
}
