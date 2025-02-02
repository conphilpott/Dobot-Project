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
  setJumpHeight(); // set slightly higher jump parameters
  getJumpHeight(); // get new jump parameters
  ctrlQueue(245); // clear command queue
  suckerCtrl(0);
  homeDobot(); // home the dobot
}

void loop() {
  
  delay(100); // 100ms delay for button polling
  
  if (digitalRead(buttonA)) {
    setPosA();
    suckerCtrl(1);
    dobotDelay(250);
    switch (movementCount) {
      case 0:
        setPosDel1();
        suckerCtrl(0);
        setPosRest();
        movementCount++;
        break;
      case 1:
        setPosDel2();
        suckerCtrl(0);
        setPosRest();
        movementCount++;
        break;
      case 2:
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
        setPosDel1();
        suckerCtrl(0);
        setPosRest();
        movementCount++;
        break;
      case 1:
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
        setPosDel1();
        suckerCtrl(0);
        setPosRest();
        movementCount++;
        break;
      case 1:
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
}

void setJumpHeight() {
  byte messageHead[] = {170, 170};
  byte messageLen = 10;
  byte messagePayload[] = {82, 1, 0, 0, 255, 65, 0, 0, 255, 65};
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

void dobotDelay(byte delay) {
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
  //byte messagePayload[] = {84, 3, 0, 209, 247, 227, 193, 180, 248, 100, 195, 198, 111, 46, 194, 47, 48, 194, 194}; // old position
  byte messagePayload[] = {84, 3, 0, 157, 164, 49, 67, 130, 245, 18, 195, 152, 224, 47, 194, 99, 102, 30, 194}; // new position
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

void suckerCtrl(byte state) {
  // control the suction cup effector state
  byte messageHead[] = {170, 170};
  byte messageLen = 4;
  byte messagePayload[] = {62, 3, 1, state};
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

void ctrlQueue(byte mode) {
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
  
  int headerLen = sizeof(header)/sizeof(byte); // calclate the length of the header
  //Serial.println(headerLen);
  int lengthLen = sizeof(length)/sizeof(byte); // calculate the length of the "length"
  //Serial.println(payloadLen);
  byte checksum = calcChecksum(payload, payloadLen); // function call for calcChecksum to calculate the checksum of the payload
  byte message[(headerLen + lengthLen + payloadLen + 1)] = {}; // construct an empty message byte array with the correct length

  // Serial.print("Checksum is: ");
  // Serial.println(checksum);

  for (int i = 0; i < headerLen; i++) {
    message[i] = header[i]; // dump the header to the message byte array
  }
  for (int i = headerLen; i < (headerLen + lengthLen); i++) {
    message[i] = length; // dump the length to the message byte array
  }
  int j = 0;
  for (int i = headerLen + lengthLen; i < (headerLen + lengthLen + payloadLen); i++) {
    message[i] = payload[j]; // dump the payload to the message byte array
    j++;
  }
  message[headerLen + lengthLen + payloadLen] = checksum; // dump the checksum to the message byte arrey

  // print the message byte array to the serial monitor
  int messageSize = sizeof(message)/sizeof(byte);
  //Serial.print(messageSize);
  Serial.print("Sending command: ");
  for (int i = 0; i < messageSize; i++) {
    Serial.print(message[i]);
    Serial.print(", ");
  }
  Serial.println();

  // send the message byte array to the dobot using the library
  dobot.commandFrame(message);
  // optional slow mode for debugging
  if (slowMode == true) {
    delay(5000);
  }
  return;
}

byte calcChecksum(byte *payload, int arraySize) {
  // calculate the checksum required for the dobot and return it as a byte

  int payloadSum = 0; // cast payloadSum as an int to prevent overflow
  byte result = 0;
  
  // calculate the sum of the payload array
  for (int i = 0; i < arraySize; i++) {
    payloadSum += payload[i];
  }
  // calculate the final checksum
  result = 256 - (payloadSum % 256);

  //Serial.print("Calculated checksum is: ");
  //Serial.println(result);
  return result;
}

