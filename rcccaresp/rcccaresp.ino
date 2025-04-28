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
  }
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  // Reverse both motors
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  // Right motor forward, left motor stop
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  // Left motor forward, right motor stop
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
