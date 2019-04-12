#include <SoftwareSerial.h>
// Define the data transmit/receive pins in Arduino
#define TxD 6
#define RxD 7

#define bt_en 8
#define bt_power 9

#define TxD_2 2
#define RxD_2 3

#define bt_en_2 4
#define bt_power_2 5

#define test_LED 13

//plug RX pin from hc-05 to D2 to communicate to it
// app HC-05
SoftwareSerial mySerial(RxD, TxD); // RX, TX for Bluetooth

//The Bluetooth connection for the second HC-05
// track-facing HC-05
SoftwareSerial mySerial_2(RxD_2, TxD_2);

void setup() {
  mySerial.begin(38400); // For Bluetooth
  mySerial_2.begin(38400); // For Bluetooth_2
  Serial.begin(9600); // For the IDE monitor Tools -> Serial Monitor
  
  pinMode(test_LED, OUTPUT);
  pinMode(bt_power, OUTPUT);
  pinMode(bt_en, OUTPUT);
  pinMode(bt_power_2, OUTPUT);
  pinMode(bt_en_2, OUTPUT);
  
  digitalWrite(test_LED, LOW);
  digitalWrite(bt_power, LOW);
  digitalWrite(bt_en, LOW);
  digitalWrite(bt_power_2, LOW);
  digitalWrite(bt_en_2, LOW);

  delay(1000);

  //turn the module on in comm mode bc we need to be able to receive info
  digitalWrite(bt_power, HIGH);
  delay(1000);
  
  //turn on the second module
  digitalWrite(bt_power_2, HIGH);
  delay(1000); 
}

void switch_to_COM(){
  //turn off the BT module
  digitalWrite(bt_power, LOW);
  delay(1000);
  //set enable to low
  digitalWrite(bt_en, LOW);
  delay(1000);
  //power the BT module back on
  //since EN is low, we will be in comm mode
  digitalWrite(bt_power, HIGH);
  delay(5000);
}
void switch_to_COM_2(){
  //turn off the BT module
  digitalWrite(bt_power_2, LOW);
  delay(1000);
  //set enable to low
  digitalWrite(bt_en_2, LOW);
  delay(1000);
  //power the BT module back on
  //since EN is low, we will be in comm mode
  digitalWrite(bt_power_2, HIGH);
  delay(5000);
}
void switch_to_AT(){
  //turn off the BT module
  digitalWrite(bt_power, LOW);
  delay(1000);
  //set enable to high
  digitalWrite(bt_en, HIGH);
  delay(1000);
  //power the BT module back on
  //since EN is high, we will be in AT mode
  digitalWrite(bt_power, HIGH);
  delay(5000);
}
void switch_to_AT_2(){
  //turn off the BT module
  digitalWrite(bt_power_2, LOW);
  delay(1000);
  //set enable to high
  digitalWrite(bt_en_2, HIGH);
  delay(1000);
  //power the BT module back on
  //since EN is high, we will be in AT mode
  digitalWrite(bt_power_2, HIGH);
  delay(5000);
}
void blink_LED(){
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
}
void blink_LED_long(){
  digitalWrite(13, HIGH);
  delay(5000);
  digitalWrite(13, LOW);
  delay(2000);
}
void change_role_to_master(){
 mySerial.write("AT+ROLE=1\r\n"); 
 delay(5000);
}

void bind_to_slave1(){
  mySerial_2.write("AT+CMODE=0\r\n");
  delay(1000);
  mySerial_2.write("AT+BIND=98d3,81,fd3777\r\n");
  delay(2000);
}

void bind_to_master(){
  mySerial_2.write("AT+CMODE=0\r\n");
  delay(1000);
  mySerial_2.write("AT+BIND=98d3,31,fc159d\r\n");
  delay(2000);
}

void change_role_to_slave(){
 mySerial.write("AT+ROLE=0\r\n"); 
 delay(5000);
}
void loop() {

  boolean isValidInput; 
  // initially listen on the first HC-05
  mySerial.listen();      
  do { 
    //String data type is 6 bytes
//    String c = ""; // get the next character from the bluetooth serial port
    byte c;
    
    while ( !mySerial.available() ) ; // LOOP...

        
    c = mySerial.read(); // Execute the option based on the character recieved
//    while(mySerial.available()){
//      c += mySerial.read();
//    }
//    blink_LED(); 

    mySerial.println(c);
    Serial.write(c); // Print the character received to the IDE serial monitor
    
    switch ( c ) {
      case 'a': // You've entered a
        mySerial.println( "You've entered an 'a'" );
        blink_LED();
        blink_LED();
        isValidInput = true;
        break;
       case 'b':
        //bind
        mySerial_2.listen();
        switch_to_AT_2();
        bind_to_slave1();
        
        switch_to_COM_2();
        
        mySerial_2.write('1');
        byte r;
//        if (mySerial_2.available()){
//          r = mySerial_2.read();
//        }
//        
//        if (r == '2'){
//          blink_LED_long();   
////          break;
//        }

        //we need the while loop to keep waiting for the response, but 
        //for some reason it takes forever, like 6 seconds
        mySerial_2.listen();
        while(mySerial_2.available()){
          r = mySerial_2.read();  
          blink_LED();
          if (r == '2'){
            blink_LED_long();   
            break;
          }
        }
        mySerial.println("Done with instruction");
        
        mySerial.listen();

        
        isValidInput = true;
        break;
        
       case 1:
        blink_LED();
        blink_LED();
        isValidInput = true;
        break;

       case 2:
        blink_LED_long();
        blink_LED_long();
        isValidInput = true;
        break;
        
      default:
        // Do the code you need when any other character is received.....
        mySerial.println( "Please enter a valid character" );
        isValidInput = false;
        break;
    }

  } while ( isValidInput == true ); // Repeat the loop

}
