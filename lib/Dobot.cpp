#include "Arduino.h"
#include "Dobot.h"
#include "SoftwareSerial.h"

//Globals:
SoftwareSerial mySerial = SoftwareSerial(2,3);  //Rx, Tx
byte  getPose[] = {170,170,2,10,0,246};
byte incomingByte; //to collect the response from Dobot
byte message[100];  //longer than the longest possible message
int i;
//Union type makes converting from byte array to float easy:
union coord {
  byte cByte[4];
  float cFloat;
};
coord cart[4];  //position of the arm in cartesian coordinates
coord pol[4];  //position of the arm in polar coordinates
///////////////////////////////////////////////////////////////

///////////////////////////  Empty Constructor  ///////////////
Dobot::Dobot(){
};
///////////////////////////////////////////////////////////////

////////////////////////////// Setup //////////////////////////
void Dobot::begin(){
    Serial.begin(115200);
    pinMode(2,INPUT);
    pinMode(3,OUTPUT);
    mySerial.begin(115200);  //Dobot baud rate
}


////////////////////////////////////  Print Current Pose  ///////////
void  Dobot::printPose(){

for(int i=0;i<6;i++){
  mySerial.write(getPose[i]);
}

delay(50);  //allow time for the Dobot to serial send a response
//Read response back from Dobot:
i=0;
while (mySerial.available() > 0){
  message[i] = mySerial.read();
  i++;
}

//distribute the Dobot position bytes to the appropriate coordinates:
for(i=0;i<=3;i++){
  cart[0].cByte[i] = message[i+5];
  cart[1].cByte[i] = message[i+9];
  cart[2].cByte[i] = message[i+13];
  cart[3].cByte[i] = message[i+17];
  pol[0].cByte[i] = message[i+21];
  pol[1].cByte[i] = message[i+25];
  pol[2].cByte[i] = message[i+29];
  pol[3].cByte[i] = message[i+33];
}
Serial.print("Cartesian: ");
Serial.print(cart[0].cFloat);  //The union type means the float equivalent is available
Serial.print(" ");
Serial.print(cart[1].cFloat);
Serial.print(" ");
Serial.print(cart[2].cFloat);
Serial.print(" ");
Serial.print(cart[3].cFloat);
Serial.print(" Polar: ");
Serial.print(pol[0].cFloat);
Serial.print(" ");
Serial.print(pol[1].cFloat);
Serial.print(" ");
Serial.print(pol[2].cFloat);
Serial.print(" ");
Serial.println(pol[3].cFloat);

Serial.println("Full dobot message: ");
for(int i=0; i<38; i++){
Serial.print(message[i]);
Serial.print(' ');
}
Serial.println();
delay(1000);
}
//////////////////////////////////////////////////////////////////////////////




void Dobot::commandFrame(byte comFrame[]){
  
for(int i=0;i<(comFrame[2]+4);i++){   //The third comFrame byte gives the number of payload bytes; total number of bytes is 4 more than this
  mySerial.write(comFrame[i]);
}
delay(50);

//read response and send it to the serial monitor:
Serial.print ("Dobot response:  ");
while (mySerial.available() > 0){
  message[0] = mySerial.read();
  Serial.print(message[0]);
  Serial.print(' ');
  }
  Serial.println();
}