#include <Dobot.h>
Dobot dobot = Dobot();

bool slowMode = false; // enable slow mode, 5 second delay between command transmission

void setup() {
  dobot.begin(); // setup comms with dobot using Dobot library
  Serial.begin(9600); // setup serial comms with pc using baudrate of 9600
  delay(1000); // wait 1s for everything to stablise
  getMovementParams(); // get current acceleration and velocity parameters from the dobot
  getJumpHeight(); // get current jump parameters
  ctrlQueue(245); // clear command queue
  homeDobot(); // home the dobot
}

void loop() {
  
  setPosition(03);
  delay(2000);
  suckerCtrl(1);
  delay(250);
  setPosition(10);
  suckerCtrl(0);

  setPosition(02);
  delay(2000);
  suckerCtrl(1);
  delay(250);
  setPosition(11);
  suckerCtrl(0);

  setPosition(01);
  delay(2000);
  suckerCtrl(1);
  delay(250);
  setPosition(12);
  suckerCtrl(0);

  //setPosition(00); // go to rest position

  delay(10000000);
}

void setJumpHeight() {
  byte messageHead[] = {170, 170};
  byte messageLen = 10;
  byte messagePayload[] = {82, 1, 50, 1000};
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

void setMovementParams() {
  byte messageHead[] = {170, 170};
  byte messageLen = 10;
  byte messagePayload[] = {83, 1};
  int payloadLen = sizeof(messagePayload)/sizeof(byte);
  Serial.println("Set Movement Params");
  sendCommand(messageHead, messageLen, messagePayload, payloadLen);
}

void getMovementParams() {
  byte messageHead[] = {170, 170};
  byte messageLen = 2;
  byte messagePayload[] = {83, 0};
  int payloadLen = sizeof(messagePayload)/sizeof(byte);
  Serial.println("Get Movement Params");
  sendCommand(messageHead, messageLen, messagePayload, payloadLen);
}

// void setPosA() {
//   byte messageHead[] = {170, 170};
//   byte messageLen = 19;
//   byte messagePayload[] = {84, 3, 0, 209, 247, 227, 193, 180, 248, 100, 195, 198, 111, 46, 194, 47, 48, 194, 194};
//   int payloadLen = sizeof(messagePayload)/sizeof(byte);
//   Serial.println("Set PosA");
//   sendCommand(messageHead, messageLen, messagePayload, payloadLen);
// }

// void setPosB() {
//   byte messageHead[] = {170, 170};
//   byte messageLen = 19;
//   byte messagePayload[] = {84, 3, 0, 23, 30, 181, 66, 144, 149, 76, 195, 22, 117, 62, 194, 62, 63, 132, 194};
//   int payloadLen = sizeof(messagePayload)/sizeof(byte);
//   Serial.println("Set PosB");
//   sendCommand(messageHead, messageLen, messagePayload, payloadLen);
// }

// void setPosC() {
//   byte messageHead[] = {170, 170};
//   byte messageLen = 19;
//   byte messagePayload[] = {84, 3, 0, 221, 13, 52, 67, 252, 137, 13, 195, 10, 239, 45, 194, 172, 174, 24, 194};
//   int payloadLen = sizeof(messagePayload)/sizeof(byte);
//   Serial.println("Set PosC");
//   sendCommand(messageHead, messageLen, messagePayload, payloadLen);
// }

// void setPosDel1() {
//   byte messageHead[] = {170, 170};
//   byte messageLen = 19;
//   byte messagePayload[] = {84, 3, 0, 111, 84, 105, 67, 45, 59, 34, 65, 150, 86, 71, 194, 113, 63, 31, 64};
//   int payloadLen = sizeof(messagePayload)/sizeof(byte);
//   Serial.println("Set PosDel1");
//   sendCommand(messageHead, messageLen, messagePayload, payloadLen);
// }

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

void setPosition(int position) {
  // set the position from a predefined list
  byte messageHead[] = {170, 170};
  byte messageLen = 19;
  int payloadLen = 0;
  byte messagePayload[19] = {};
  byte *messagePayloadPtr = messagePayload;
  char positionDesc[] = {};
  char *positionDescPtr = positionDesc;

  // define rest position
  byte messagePayloadRest[] = {84, 3, 0};

  // define bay positions
  byte messagePayloadBay01[] = {84, 3, 0, 209, 247, 227, 193, 180, 248, 100, 195, 198, 111, 46, 194, 47, 48, 194, 194};
  byte messagePayloadBay02[] = {84, 3, 0, 23, 30, 181, 66, 144, 149, 76, 195, 22, 117, 62, 194, 62, 63, 132, 194};
  byte messagePayloadBay03[] = {84, 3, 0, 221, 13, 52, 67, 252, 137, 13, 195, 10, 239, 45, 194, 172, 174, 24, 194};

  // define delivery positions
  byte messagePayloadDel01[] = {84, 3, 0, 111, 84, 105, 67, 45, 59, 34, 65, 150, 86, 71, 194, 113, 63, 31, 64};
  byte messagePayloadDel02[] = {84, 3, 0, 86, 165, 97, 67, 232, 222, 196, 64, 92, 155, 157, 193, 75, 232, 199, 63};
  byte messagePayloadDel03[] = {84, 3, 0, 45, 18, 100, 67, 250, 60, 192, 64, 192, 221, 22, 64, 132, 33, 193, 63};

  switch (position) {
    case 00:
    messagePayloadPtr = messagePayloadRest;
    positionDescPtr = "Rest";
    break;
    case 01:
    messagePayloadPtr = messagePayloadBay01;
    positionDescPtr = "Bay 1";
    break;
    case 02:
    messagePayloadPtr = messagePayloadBay02;
    positionDescPtr = "Bay 2";
    break;   
    case 03:
    messagePayloadPtr = messagePayloadBay03;
    positionDescPtr = "Bay 3";
    break;
    case 10:
    messagePayloadPtr = messagePayloadDel01;
    positionDescPtr = "Delivery level 0";
    break;
    case 11:
    messagePayloadPtr = messagePayloadDel02;
    positionDescPtr = "Delivery level 1";
    break;
    case 12:
    messagePayloadPtr = messagePayloadDel03;
    positionDescPtr = "Delivery level 2";
    break;
  }

  payloadLen = sizeof(messagePayload)/sizeof(byte);
  Serial.print("Set position to: ");
  Serial.println(positionDesc);
  sendCommand(messageHead, messageLen, messagePayload, payloadLen);
  return;
}

// void getPose() {
//   byte messageHead[] = {170, 170};
//   byte messageLen = 2;
//   byte messagePayload[] = {10, 0};
//   int payloadLen = sizeof(messagePayload)/sizeof(byte);
//   byte messageChecksum;
//   //byte message[16] = {};
//   Serial.println("Get Pose");
//   sendCommand(messageHead, messageLen, messagePayload, payloadLen);
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

// void suckerOff() {
//   byte messageHead[] = {170, 170};
//   byte messageLen = 4;
//   byte messagePayload[] = {62, 3, 1, 0};
//   int payloadLen = sizeof(messagePayload)/sizeof(byte);
//   Serial.println("Don't Suck");
//   sendCommand(messageHead, messageLen, messagePayload, payloadLen);
// }

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

void ctrlQueue(byte mode) {
  // control the queue of commands using dobot command ID
  byte messageHead[] = {170, 170};
  byte messageLen = 2;
  byte messagePayload[] = {0, 1};
  messagePayload[0] = mode;
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

