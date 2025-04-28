#include <BluetoothSerial.h>
BluetoothSerial SerialBT;

// Motor driver pins
#define IN1  14
#define IN2  27
#define IN3  26
#define IN4  25

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Sentron"); // Bluetooth name

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopCar();
}

void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read();
    handleCommand(command);
  }
}

void handleCommand(char cmd) {
  switch (cmd) {
    case 'F': // Forward
      moveForward();
      break;
    case 'B': // Backward
      moveBackward();
      break;
    case 'L': // Turn Left
      turnLeft();
      break;
    case 'R': // Turn Right
      turnRight();
      break;
    case 'S': // Stop
      stopCar();
      break;
    case 'G': // Forward Right
      forwardRight();
      break;
    case 'H': // Backward Right
      backwardRight();
      break;
    case 'I': // Forward Left
      forwardLeft();
      break;
    case 'J': // Backward Left
      backwardLeft();
      break;
  }
}

// Basic movements
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void stopCar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// New movement functions
// void forwardRight() {
//   // Left motor full forward, right motor slow or stop (soft right)
//   digitalWrite(IN1, HIGH);
//   digitalWrite(IN2, LOW);
//   digitalWrite(IN3, LOW);
//   digitalWrite(IN4, LOW);
// }

// void backwardRight() {
//   // Left motor backward, right motor stop
//   digitalWrite(IN1, LOW);
//   digitalWrite(IN2, HIGH);
//   digitalWrite(IN3, LOW);
//   digitalWrite(IN4, LOW);
// }

// void forwardLeft() {
//   // Right motor full forward, left motor stop (soft left)
//   digitalWrite(IN1, LOW);
//   digitalWrite(IN2, LOW);
//   digitalWrite(IN3, HIGH);
//   digitalWrite(IN4, LOW);
// }

// void backwardLeft() {
//   // Right motor backward, left motor stop
//   digitalWrite(IN1, LOW);
//   digitalWrite(IN2, LOW);
//   digitalWrite(IN3, LOW);
//   digitalWrite(IN4, HIGH);
// }
void forwardRight() {
  // Right motor moves, left motor slow or stop
  digitalWrite(IN1, LOW);    // left motor stop
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);   // right motor forward
  digitalWrite(IN4, LOW);
}

void backwardRight() {
  // Right motor moves backward, left motor stop
  digitalWrite(IN1, LOW);    // left motor stop
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);    // right motor backward
  digitalWrite(IN4, HIGH);
}

void forwardLeft() {
  // Left motor moves, right motor stop
  digitalWrite(IN1, HIGH);   // left motor forward
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);    // right motor stop
  digitalWrite(IN4, LOW);
}

void backwardLeft() {
  // Left motor moves backward, right motor stop
  digitalWrite(IN1, LOW);    // left motor backward
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);    // right motor stop
  digitalWrite(IN4, LOW);
}