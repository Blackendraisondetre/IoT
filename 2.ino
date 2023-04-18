#include "DFRobot_RGBLCD1602.h"

String Index[11] = {"0","1","2","3","4","5","6","7","8","9","."};
String Sub[11] = {"A","B","C","D","E","F","G","H","J","K","."};

String dataDec[5];

//String Index[11] = "0123456789.";
//String Sub = "ABCDEFGHJK.";


char data;

int button = 13;
int i = 0;
String msg[20];

DFRobot_RGBLCD1602 lcd(0x60, 16, 2);

void setup() {
  pinMode(button,INPUT_PULLUP);
  Serial.begin(9600);
  Serial.setTimeout(3);
  lcd.init();
  lcd.print("Hello");
  delay(500);
  lcd.clear();
}

void decryption() {



  for(int j=0;j<i;j++) {
    for(int z=0;z<11;z++) {  
        
        
        //Serial.print(msg[j]);
        //Serial.print(Sub[z]);
        //Serial.print(z);

        if (msg[j] == Sub[z]){        
          dataDec[j] = Index[z];   
          lcd.print(dataDec[j]);}       
        }   }   
    
    
  String dataDec[5];
  i = 0;
    
  }
      

void Readmsg() {
  if(Serial.available()) {
    msg[i] = Serial.readString();
    i++;
    delay(50);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  Readmsg();
  if(digitalRead(button) == 0) {

    for(int j=0;j<i;j++) {
      lcd.print(msg[j]);
    }

    delay(200);      
    lcd.clear();

    decryption();
    delay(200);
  }
  }

