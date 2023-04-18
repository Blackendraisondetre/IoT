int flag = 0;
String amogus;

void setup() {

  pinMode(2, INPUT_PULLUP);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  attachInterrupt(0, btnIsr, FALLING);
}

void btnIsr() {

    flag=(flag+1)%3;

}


void loop() {

  for (int i = 0; i < 4; i++)
  {
    digitalWrite(i+8, HIGH);
  }

    if (flag == 0){delay(500*3);}
    else if (flag == 0){delay(500);}
    else {delay(500/2);}
   
   for (int i = 0; i < 4; i++)
  {
    digitalWrite(i+8, LOW);
  }

    if (flag == 0){delay(500*5);}
    else if (flag == 0){delay(500*3);}
    else {delay(500);}

    }



 
