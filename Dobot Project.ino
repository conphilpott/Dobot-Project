#include <Dobot.h>
Dobot dobot = Dobot();

void setup() {
  // put your setup code here, to run once:
  dobot.begin();
  Serial.begin(9600);
  homeDobot();
}



void loop() {
  


  dobot.printPose();

  delay(10000);
}


void getPose() {
  byte messageHead[] = {170, 170};
  byte messageLen = 2;
  byte messagePayload[] = {10, 0};
  int payloadLen = sizeof(messagePayload)/sizeof(byte);
  byte messageChecksum;
  //byte message[16] = {};
  Serial.println("Get Pose");
  sendCommand(messageHead, messageLen, messagePayload, payloadLen);
}

void suckerOn() {
  byte messageHead[] = {170, 170};
  byte messageLen = 4;
  byte messagePayload[] = {62, 1, 1, 1};
  int payloadLen = sizeof(messagePayload)/sizeof(byte);
  byte messageChecksum;
  //byte message[16] = {};
  Serial.println("Sucker On");
  sendCommand(messageHead, messageLen, messagePayload, payloadLen);
}

void suckerOff() {
  byte messageHead[] = {170, 170};
  byte messageLen = 4;
  byte messagePayload[] = {62, 1, 1, 0};
  int payloadLen = sizeof(messagePayload)/sizeof(byte);
  byte messageChecksum;
  //byte message[16] = {};
  Serial.println("Sucker Off");
  sendCommand(messageHead, messageLen, messagePayload, payloadLen);
}

void homeDobot() {
  byte messageHead[] = {170, 170};
  byte messageLen = 6;
  byte messagePayload[] = {31, 1, 1, 0, 0, 0};
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

