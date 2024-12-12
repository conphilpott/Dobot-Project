#include <Dobot.h>
Dobot dobot = Dobot();

void setup() {
  // put your setup code here, to run once:
  dobot.begin();
  Serial.begin(9600);
  delay(500);
  clearQueue();
  homeDobot();
  delay(10000);
}

void loop() {
  
  setPosA();
  delay(2000);
  suckerOn();
  delay(250);
  setPosDel1();
  suckerOff();

  setPosB();
  delay(2000);
  suckerOn();
  delay(250);
  setPosDel2();
  suckerOff();

  setPosC();
  delay(2000);
  suckerOn();
  delay(250);
  setPosDel3();
  suckerOff();

  delay(10000000);
}

void setPosA() {
  byte messageHead[] = {170, 170};
  byte messageLen = 19;
  byte messagePayload[] = {84, 3, 0, 209, 247, 227, 193, 180, 248, 100, 195, 198, 111, 46, 194, 47, 48, 194, 194};
  int payloadLen = sizeof(messagePayload)/sizeof(byte);
  byte messageChecksum;
  //byte message[16] = {};
  Serial.println("Set PosA");
  sendCommand(messageHead, messageLen, messagePayload, payloadLen);
}

void setPosB() {
  byte messageHead[] = {170, 170};
  byte messageLen = 19;
  byte messagePayload[] = {84, 3, 0, 23, 30, 181, 66, 144, 149, 76, 195, 22, 117, 62, 194, 62, 63, 132, 194};
  int payloadLen = sizeof(messagePayload)/sizeof(byte);
  byte messageChecksum;
  //byte message[16] = {};
  Serial.println("Set PosB");
  sendCommand(messageHead, messageLen, messagePayload, payloadLen);
}

void setPosC() {
  byte messageHead[] = {170, 170};
  byte messageLen = 19;
  byte messagePayload[] = {84, 3, 0, 221, 13, 52, 67, 252, 137, 13, 195, 10, 239, 45, 194, 172, 174, 24, 194};
  int payloadLen = sizeof(messagePayload)/sizeof(byte);
  byte messageChecksum;
  //byte message[16] = {};
  Serial.println("Set PosC");
  sendCommand(messageHead, messageLen, messagePayload, payloadLen);
}

void setPosDel1() {
  byte messageHead[] = {170, 170};
  byte messageLen = 19;
  byte messagePayload[] = {84, 3, 0, 111, 84, 105, 67, 45, 59, 34, 65, 150, 86, 71, 194, 113, 63, 31, 64};
  int payloadLen = sizeof(messagePayload)/sizeof(byte);
  byte messageChecksum;
  //byte message[16] = {};
  Serial.println("Set PosDel1");
  sendCommand(messageHead, messageLen, messagePayload, payloadLen);
}

void setPosDel2() {
  byte messageHead[] = {170, 170};
  byte messageLen = 19;
  byte messagePayload[] = {84, 3, 0, 86, 165, 97, 67, 232, 222, 196, 64, 92, 155, 157, 193, 75, 232, 199, 63};
  int payloadLen = sizeof(messagePayload)/sizeof(byte);
  byte messageChecksum;
  //byte message[16] = {};
  Serial.println("Set PosDel2");
  sendCommand(messageHead, messageLen, messagePayload, payloadLen);
}

void setPosDel3() {
  byte messageHead[] = {170, 170};
  byte messageLen = 19;
  byte messagePayload[] = {84, 3, 0, 45, 18, 100, 67, 250, 60, 192, 64, 192, 221, 22, 64, 132, 33, 193, 63};
  int payloadLen = sizeof(messagePayload)/sizeof(byte);
  byte messageChecksum;
  //byte message[16] = {};
  Serial.println("Set PosDel3");
  sendCommand(messageHead, messageLen, messagePayload, payloadLen);
}

void getPose() {
  byte messageHead[] = {170, 170};
  byte messageLen = 2;
  byte messagePayload[] = {10, 1};
  int payloadLen = sizeof(messagePayload)/sizeof(byte);
  byte messageChecksum;
  //byte message[16] = {};
  Serial.println("Get Pose");
  sendCommand(messageHead, messageLen, messagePayload, payloadLen);
}

void suckerOn() {
  byte messageHead[] = {170, 170};
  byte messageLen = 4;
  byte messagePayload[] = {62, 3, 1, 1};
  int payloadLen = sizeof(messagePayload)/sizeof(byte);
  byte messageChecksum;
  //byte message[16] = {};
  Serial.println("Sucker On");
  sendCommand(messageHead, messageLen, messagePayload, payloadLen);
}

void suckerOff() {
  byte messageHead[] = {170, 170};
  byte messageLen = 4;
  byte messagePayload[] = {62, 3, 1, 0};
  int payloadLen = sizeof(messagePayload)/sizeof(byte);
  byte messageChecksum;
  //byte message[16] = {};
  Serial.println("Sucker Off");
  sendCommand(messageHead, messageLen, messagePayload, payloadLen);
}

void homeDobot() {
  byte messageHead[] = {170, 170};
  byte messageLen = 6;
  byte messagePayload[] = {31, 3, 1, 0, 0, 0};
  int payloadLen = sizeof(messagePayload)/sizeof(byte);
  byte messageChecksum;
  byte message[16] = {};
  Serial.println("Home Dobot");
  sendCommand(messageHead, messageLen, messagePayload, payloadLen);
}

void clearQueue() {
  byte messageHead[] = {170, 170};
  byte messageLen = 2;
  byte messagePayload[] = {246, 1};
  int payloadLen = sizeof(messagePayload)/sizeof(byte);
  byte messageChecksum;
  byte message[16] = {};
  Serial.println("Home Dobot");
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

  return;
}

byte calcChecksum(byte *payload, int arraySize) {
  // calculate the checksum required for the dobot and return it as a byte
  // future, can this function automatically append the checksum to the array?

  //int payload[] = { 84, 1, 1, 209, 240, 78, 67, 178, 239, 73, 192, 148, 191, 46, 194, 0, 0, 0 }; // test array

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

