#include <Servo.h> 

int PUL = 7;
int DIR = 6;
int ENA = 5;
Servo myservo;
int pos = 0;

void setup() {
  // put your setup code here, to run once:
pinMode(PUL,OUTPUT);
pinMode(DIR, OUTPUT);
pinMode(ENA, OUTPUT);
myservo.attach(9);
}

void loop(){

  myservo.write(0);
  delay(1500);

  //myservo.write(0);
  //delay(150);
 // 6794 is full 53.5 inches of belt. 
  
  for(int i = 0; i < 5254; i++){
    delayMicroseconds(5000);
    digitalWrite(DIR,LOW);
    digitalWrite(ENA,HIGH);
    digitalWrite(PUL,HIGH);
    delayMicroseconds(50);
    digitalWrite(PUL,LOW);
  }
  
  myservo.write(60);
  delay(2500);
   
  //go backward
   for (int i=0; i<5254; i++)   //Backward 5000 steps
  {
    delayMicroseconds(3500);
    digitalWrite(DIR,HIGH);
    digitalWrite(ENA,HIGH);
    digitalWrite(PUL,HIGH);
    delayMicroseconds(50);
    digitalWrite(PUL,LOW);
  }
    delay(10000);

}
