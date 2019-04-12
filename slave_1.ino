#include <SoftwareSerial.h>
//include servo library

#define bt_en 4
#define bt_power 5

#define TxD 2
#define RxD 3

#define test_LED 13

SoftwareSerial mySerial_slave(RxD, TxD); // RX, TX for Bluetooth



void setup() {
  // put your setup code here, to run once:
  mySerial_slave.begin(38400);
  Serial.begin(9600);

  pinMode(test_LED, OUTPUT);
  pinMode(bt_power, OUTPUT);
  pinMode(bt_en, OUTPUT);

  digitalWrite(test_LED, LOW);
  digitalWrite(bt_power, LOW);
  digitalWrite(bt_en, LOW);

  delay(1000);
  //turn on the slave HC-05 in COM mode
  digitalWrite(bt_power, HIGH);

}

void blink_LED(){
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
}
void blink_LED_long(){
  digitalWrite(13, HIGH);
  delay(3000);
  digitalWrite(13, LOW);
  delay(3000);
}

void latch(){
  delay(1000);
}
void unlatch(){
  delay(1000);
}

void pan(){
  delay(1000);
}

void tilt(){
  delay(1000);
}

void move_forward(){
  latch();
  delay(1000);
  check_collision();
  unlatch();
}

void move_backward(){
  latch();
  delay(1000);
  check_collision();
  unlatch();
  
}

void light_on(){
  delay(1000);
}

void light_off(){
  delay(1000);
}
void dim(){
  delay(1000);
}

void brighten(){
  delay(1000);
}

void check_collision(){
  delay(1000);
}
void loop() {
  // put your main code here, to run repeatedly:
  byte x;
//  if (mySerial_slave.available()){
//    x = mySerial_slave.read();
//  }
  x = mySerial_slave.read();
  //should this be in the if statement above?
  switch(x){
    case '1':
      blink_LED();
      blink_LED();

      mySerial_slave.write('2');
      break;
    
    case 'l':
      latch();
    case 'u':
      unlatch();
      
    default:
      Serial.print("please send the right information");

      break;
  }
  

}
