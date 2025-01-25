#include <Dobot.h>
Dobot dobot = Dobot();

bool slowMode = false; // enable slow mode, 5 second delay between command transmission

int buttonA = 5;
int buttonB = 6;
int buttonC = 7;
int movementCount = 0;

void setup() {

  // setup button inputs
  pinMode(buttonA, INPUT); 
  pinMode(buttonB, INPUT);
  pinMode(buttonC, INPUT); 

  dobot.begin(); // setup comms with dobot using Dobot library
  Serial.begin(9600); // setup serial comms with pc using baudrate of 9600
  delay(1000); // wait 1s for everything to stablise
  //getMovementParams(); // get current acceleration and velocity parameters from the dobot
  getJumpHeight(); // get current jump parameters
  setJumpHeight();
  getJumpHeight(); // get new jump parameters
  ctrlQueue(245); // clear command queue
  suckerCtrl(0);
  homeDobot(); // home the dobot
}

void loop() {
  
  dobot.printPose();
  //ctrlQueue(245); // clear command queue

char buttonSel;

if (digitalRead(buttonA)) {
  setPosA();
  suckerCtrl(1);
  dobotDelay(250);
    switch (movementCount) {
    case 0:
      setPosDel3();
      setPosDel1();
      suckerCtrl(0);
      setPosRest();
      movementCount++;
      break;
    case 1:
      setPosDel3();
      setPosDel2();
      suckerCtrl(0);
      setPosRest();
      movementCount++;
      break;
    case 2:
      setPosDel3();
      suckerCtrl(0);
      setPosRest();
      movementCount = 0;
      break;
    }
} else if (digitalRead(buttonB)) {
  setPosB();
  suckerCtrl(1);
  dobotDelay(250);
    switch (movementCount) {
    case 0:
      setPosDel3();
      setPosDel1();
      suckerCtrl(0);
      setPosRest();
      movementCount++;
      break;
    case 1:
      setPosDel3();
      setPosDel2();
      suckerCtrl(0);
      setPosRest();
      movementCount++;
      break;
    case 2:
      setPosDel3();
      suckerCtrl(0);
      setPosRest();
      movementCount = 0;
      break;
    }
} else if (digitalRead(buttonC)) {
  setPosC();
  suckerCtrl(1);
  dobotDelay(250);
    switch (movementCount) {
    case 0:
      setPosDel3();
      setPosDel1();
      suckerCtrl(0);
      setPosRest();
      movementCount++;
      break;
    case 1:
      setPosDel3();
      setPosDel2();
      suckerCtrl(0);
      setPosRest();
      movementCount++;
      break;
    case 2:
      setPosDel3();
      suckerCtrl(0);
      setPosRest();
      movementCount = 0;
      break;
    }
}

 delay(5000);

  // setPosC();
  // delay(2000);
  // suckerCtrl(1);
  // delay(250);
  // setPosDel1();
  // suckerCtrl(0);

  // setPosB();
  // delay(2000);
  // suckerCtrl(1);
  // delay(250);
  // setPosDel2();
  // suckerCtrl(0);

  // setPosA();
  // delay(2000);
  // suckerCtrl(1);
  // delay(250);
  // setPosDel3();
  // suckerCtrl(0);

  // setPosRest();
  // dobotDelay(5000);

  // setPosDel3();
  // delay(2000);
  // suckerCtrl(1);
  // delay(250);
  // setPosA();
  // suckerCtrl(0);

  // setPosDel2();
  // delay(2000);
  // suckerCtrl(1);
  // delay(250);
  // setPosB();
  // suckerCtrl(0);

  // setPosDel1();
  // delay(2000);
  // suckerCtrl(1);
  // delay(250);
  // setPosC();
  // suckerCtrl(0);

  // setPosRest();

  // dobotDelay(5000);

}

void setJumpHeight() {
  byte messageHead[] = {170, 170};
  byte messageLen = 10;
  byte messagePayload[] = {82, 1, 50000, 51266};
  int payloadLen = sizeof(messagePayload)/sizeof(byte);
  Serial.println("Set Jump Height");
  sendCommand(messageHead, messageLen, messagePayload, payloadLen);
}

void getJumpHeight() {
  byte messageHead[] = {170, 170};
  byte messageLen = 2;
  byte messagePayload[] = {82, 0};
  int payloadLen = sizeof(messagePayload)/sizeof(byte);
  Serial.println("Get Jump Height");
  sendCommand(messageHead, messageLen, messagePayload, payloadLen);
}

// void setMovementParams() {
//   byte messageHead[] = {170, 170};
//   byte messageLen = 10;
//   byte messagePayload[] = {83, 1};
//   int payloadLen = sizeof(messagePayload)/sizeof(byte);
//   Serial.println("Set Movement Params");
//   sendCommand(messageHead, messageLen, messagePayload, payloadLen);
// }

// void getMovementParams() {
//   byte messageHead[] = {170, 170};
//   byte messageLen = 2;
//   byte messagePayload[] = {83, 0};
//   int payloadLen = sizeof(messagePayload)/sizeof(byte);
//   Serial.println("Get Movement Params");
//   sendCommand(messageHead, messageLen, messagePayload, payloadLen);
// }

void dobotDelay(int delay) {
  // Sets a delay in the dobot queue of "delay" milliseconds
  byte messageHead[] = {170, 170};
  byte messageLen = 6;
  byte messagePayload[] = {110, 3, delay};
  int payloadLen = sizeof(messagePayload)/sizeof(byte);
  Serial.print("Delay Dobot ");
  Serial.print(delay);
  Serial.println("ms");
  sendCommand(messageHead, messageLen, messagePayload, payloadLen);
}

void setPosRest() {
  byte messageHead[] = {170, 170};
  byte messageLen = 19;
  byte messagePayload[] = {84, 3, 1, 27, 122, 86, 67, 248, 243, 183, 64, 6, 56, 83, 66, 231, 132, 196, 63};
  int payloadLen = sizeof(messagePayload)/sizeof(byte);
  Serial.println("Set PosA");
  sendCommand(messageHead, messageLen, messagePayload, payloadLen);
}

void setPosA() {
  byte messageHead[] = {170, 170};
  byte messageLen = 19;
  byte messagePayload[] = {84, 3, 0, 209, 247, 227, 193, 180, 248, 100, 195, 198, 111, 46, 194, 47, 48, 194, 194};
  int payloadLen = sizeof(messagePayload)/sizeof(byte);
  Serial.println("Set PosA");
  sendCommand(messageHead, messageLen, messagePayload, payloadLen);
}

void setPosB() {
  byte messageHead[] = {170, 170};
  byte messageLen = 19;
  byte messagePayload[] = {84, 3, 0, 23, 30, 181, 66, 144, 149, 76, 195, 22, 117, 62, 194, 62, 63, 132, 194};
  int payloadLen = sizeof(messagePayload)/sizeof(byte);
  Serial.println("Set PosB");
  sendCommand(messageHead, messageLen, messagePayload, payloadLen);
}

void setPosC() {
  byte messageHead[] = {170, 170};
  byte messageLen = 19;
  byte messagePayload[] = {84, 3, 0, 221, 13, 52, 67, 252, 137, 13, 195, 10, 239, 45, 194, 172, 174, 24, 194};
  int payloadLen = sizeof(messagePayload)/sizeof(byte);
  Serial.println("Set PosC");
  sendCommand(messageHead, messageLen, messagePayload, payloadLen);
}

void setPosDel1() {
  byte messageHead[] = {170, 170};
  byte messageLen = 19;
  byte messagePayload[] = {84, 3, 0, 111, 84, 105, 67, 45, 59, 34, 65, 150, 86, 71, 194, 113, 63, 31, 64};
  int payloadLen = sizeof(messagePayload)/sizeof(byte);
  Serial.println("Set PosDel1");
  sendCommand(messageHead, messageLen, messagePayload, payloadLen);
}

void setPosDel2() {
  byte messageHead[] = {170, 170};
  byte messageLen = 19;
  byte messagePayload[] = {84, 3, 0, 111, 84, 105, 67, 45, 59, 34, 65, 92, 155, 157, 193, 75, 232, 199, 63};
  int payloadLen = sizeof(messagePayload)/sizeof(byte);
  Serial.println("Set PosDel2");
  sendCommand(messageHead, messageLen, messagePayload, payloadLen);
}

void setPosDel3() {
  byte messageHead[] = {170, 170};
  byte messageLen = 19;
  byte messagePayload[] = {84, 3, 0, 111, 84, 105, 67, 45, 59, 34, 65, 192, 221, 22, 64, 132, 33, 193, 63};
  int payloadLen = sizeof(messagePayload)/sizeof(byte);
  Serial.println("Set PosDel3");
  sendCommand(messageHead, messageLen, messagePayload, payloadLen);
}

// void setPosDel2() {
//   byte messageHead[] = {170, 170};
//   byte messageLen = 19;
//   byte messagePayload[] = {84, 3, 0, 86, 165, 97, 67, 232, 222, 196, 64, 92, 155, 157, 193, 75, 232, 199, 63};
//   int payloadLen = sizeof(messagePayload)/sizeof(byte);
//   Serial.println("Set PosDel2");
//   sendCommand(messageHead, messageLen, messagePayload, payloadLen);
// }

// void setPosDel3() {
//   byte messageHead[] = {170, 170};
//   byte messageLen = 19;
//   byte messagePayload[] = {84, 3, 0, 45, 18, 100, 67, 250, 60, 192, 64, 192, 221, 22, 64, 132, 33, 193, 63};
//   int payloadLen = sizeof(messagePayload)/sizeof(byte);
//   Serial.println("Set PosDel3");
//   sendCommand(messageHead, messageLen, messagePayload, payloadLen);
// }

// void setPosition(int position) {
//   // set the position from a predefined list
//   byte messageHead[] = {170, 170};
//   byte messageLen = 19;
//   int payloadLen = 0;
//   byte messagePayload[19] = {};
//   byte *messagePayloadPtr = messagePayload;
//   char positionDesc[] = {};
//   char *positionDescPtr = positionDesc;

//   // define rest position
//   byte messagePayloadRest[] = {84, 3, 0};

//   // define bay positions
//   byte messagePayloadBay01[] = {84, 3, 0, 209, 247, 227, 193, 180, 248, 100, 195, 198, 111, 46, 194, 47, 48, 194, 194};
//   byte messagePayloadBay02[] = {84, 3, 0, 23, 30, 181, 66, 144, 149, 76, 195, 22, 117, 62, 194, 62, 63, 132, 194};
//   byte messagePayloadBay03[] = {84, 3, 0, 221, 13, 52, 67, 252, 137, 13, 195, 10, 239, 45, 194, 172, 174, 24, 194};

//   // define delivery positions
//   byte messagePayloadDel01[] = {84, 3, 0, 111, 84, 105, 67, 45, 59, 34, 65, 150, 86, 71, 194, 113, 63, 31, 64};
//   byte messagePayloadDel02[] = {84, 3, 0, 86, 165, 97, 67, 232, 222, 196, 64, 92, 155, 157, 193, 75, 232, 199, 63};
//   byte messagePayloadDel03[] = {84, 3, 0, 45, 18, 100, 67, 250, 60, 192, 64, 192, 221, 22, 64, 132, 33, 193, 63};

//   switch (position) {
//     case 0:
//     messagePayloadPtr = messagePayloadRest;
//     positionDescPtr = "Rest";
//     break;
//     case 1:
//     messagePayloadPtr = messagePayloadBay01;
//     positionDescPtr = "Bay 1";
//     break;
//     case 2:
//     messagePayloadPtr = messagePayloadBay02;
//     positionDescPtr = "Bay 2";
//     break;   
//     case 3:
//     messagePayloadPtr = messagePayloadBay03;
//     positionDescPtr = "Bay 3";
//     break;
//     case 10:
//     messagePayloadPtr = messagePayloadDel01;
//     positionDescPtr = "Delivery level 0";
//     break;
//     case 11:
//     messagePayloadPtr = messagePayloadDel02;
//     positionDescPtr = "Delivery level 1";
//     break;
//     case 12:
//     messagePayloadPtr = messagePayloadDel03;
//     positionDescPtr = "Delivery level 2";
//     break;
//   }

//   payloadLen = sizeof(messagePayloadPtr)/sizeof(byte);
//   Serial.print("Set position to: ");
//   Serial.println(positionDescPtr);
//   sendCommand(messageHead, messageLen, messagePayloadPtr, payloadLen);
//   return;
// }

void suckerCtrl(byte state) {
  // control the suction cup effector state
  byte messageHead[] = {170, 170};
  byte messageLen = 4;
  byte messagePayload[] = {62, 3, 1, 0};
  messagePayload[3] = state;
  int payloadLen = sizeof(messagePayload)/sizeof(byte);
  Serial.print("Sucker Control set to: ");
  Serial.println(state);
  sendCommand(messageHead, messageLen, messagePayload, payloadLen);
}

void homeDobot() {
  // home the dobot
  byte messageHead[] = {170, 170};
  byte messageLen = 6;
  byte messagePayload[] = {31, 1, 1, 0, 0, 0};
  int payloadLen = sizeof(messagePayload)/sizeof(byte);
  Serial.println("Home Dobot");
  sendCommand(messageHead, messageLen, messagePayload, payloadLen);
  delay(20000);
}

// void clearQueue() {
//   byte messageHead[] = {170, 170};
//   byte messageLen = 2;
//   byte messagePayload[] = {245, 1};
//   int payloadLen = sizeof(messagePayload)/sizeof(byte);
//   Serial.println("Clear Queue");
//   sendCommand(messageHead, messageLen, messagePayload, payloadLen);
// }

void ctrlQueue(int mode) {
  // control the queue of commands using dobot command ID
  byte messageHead[] = {170, 170};
  byte messageLen = 2;
  byte messagePayload[] = {mode, 1};
  int payloadLen = sizeof(messagePayload)/sizeof(byte);
  Serial.println("Control Queue");
  sendCommand(messageHead, messageLen, messagePayload, payloadLen);
}

void sendCommand(byte *header, byte length, byte *payload, int payloadLen) {
  // construct message from input parameters, append checksum and send to dobot
  
  int headerLen = sizeof(header)/sizeof(byte);
  int lengthLen = sizeof(length)/sizeof(byte);
  //Serial.println(payloadLen);
  byte checksum = calcChecksum(payload, payloadLen);
  byte message[(headerLen + lengthLen + payloadLen + 1)] = {};

  // Serial.print("Checksum is: ");
  // Serial.println(checksum);

  for (int i = 0; i < headerLen; i++) {
    message[i] = header[i];
  }
  for (int i = headerLen; i < (headerLen + lengthLen); i++) {
    message[i] = length;
  }
  int j = 0;
  for (int i = headerLen + lengthLen; i < (headerLen + lengthLen + payloadLen); i++) {
    message[i] = payload[j];
    j++;
  }

  message[headerLen + lengthLen + payloadLen] = checksum;

  int messageSize = sizeof(message)/sizeof(byte);
  //Serial.print(messageSize);
  Serial.print("Sending command: ");
  for (int i = 0; i < messageSize; i++) {
    Serial.print(message[i]);
    Serial.print(", ");
  }
  Serial.println();

  dobot.commandFrame(message);
  if (slowMode == true) {
    delay(5000);
  }
  return;
}

byte calcChecksum(byte *payload, int arraySize) {
  // calculate the checksum required for the dobot and return it as a byte

  byte payloadSum = 0;
  byte result = 0;
  
  for (int i = 0; i < arraySize; i++) {
    payloadSum += payload[i];
  }
  result = 256 - (payloadSum % 256);

  //Serial.print("Calculated checksum is: ");
  //Serial.println(result);
  return result;
}

