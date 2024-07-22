#include <Servo.h>
int horPin = 10;
int verPin = 9;
Servo hor;
int servoh = 90;
int servohLimitHigh = 160;
int servohLimitLow = 20;
Servo ver;
int servov = 90;
int servovLimitHigh = 160;
int servovLimitLow = 20;
int pos;
int tl; //top letf
int tr; //top right
int bl; //bot letf
int br; //bot right

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT); //br
  pinMode(A1, INPUT); //tr
  pinMode(A2, INPUT); //tl
  pinMode(A3, INPUT); //bl
  pinMode(horPin, OUTPUT);
  pinMode(verPin, OUTPUT);
  hor.attach(horPin);
  hor.write(0);
  ver.attach(verPin);
  ver.write(0);
  delay(500);
}

void loop() {
  servoh = hor.read();
  servov = ver.read();
  tl = analogRead(A2);
  tr = analogRead(A1);
  bl = analogRead(A3);
  br = analogRead(A0);
  delay(50);
  int avgtop = (tl + tr) / 2; //média top LDRs
  int avgbot = (bl + br) / 2; //média bottom LDRs
  int avgleft = (tl + bl) / 2; //média left LDRs
  int avgright = (tr + br) / 2; //média right LDRs
  
  //vertical movement
  if(avgtop < (avgbot-10)) // 10 de margem de erro
  {
    ver.write(servov += 2); // Incrementa a posição do servo em 2 graus
    if (servov > servovLimitHigh)
    {
    servov = servovLimitHigh;
    }
    delay(10);
  }
  else if(avgbot < (avgtop-10))
  {
    ver.write(servov -= 2);
    if(servov < servovLimitLow)
    {
    servov = servovLimitLow;
    }
    delay(10);
  }
  else
  {
    ver.write(servov);
  }


  //horizontal movement
  if ( (avgleft-10) > avgright)
  {
    hor.write(servoh += 2);
    if (servoh > servohLimitHigh)
    {
    servoh = servohLimitHigh;
    }
    delay(10);
  }
  else if ( (avgright-10) > avgleft)
  {
    hor.write(servoh -= 2);
    if (servoh < servohLimitLow)
    {
    servoh = servohLimitLow;
    }
    delay(10);
  }
  else
  {
    hor.write(servoh);
  }
  delay(10);
  
}
