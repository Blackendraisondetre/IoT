int flag = 0;
int arr[6];

void setup() {

  pinMode(2, INPUT_PULLUP);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  attachInterrupt(0, btnIsr, FALLING);
}

void btnIsr() {

  for (int i = 0; i < 7; i++)
  {
    arr[i] = random(2); 
  }
}


void loop() {

  for (int i = 0; i < 7; i++)
  {
    if(arr[i]==1){digitalWrite(i+5, HIGH);}
    else{digitalWrite(i+5, LOW);}

  }
    }
