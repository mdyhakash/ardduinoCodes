#include <BluetoothSerial.h>
BluetoothSerial SerialBT;

// Motor driver pins
#define IN1  14
#define IN2  27
#define IN3  26
#define IN4  25

// Ultrasonic sensor pins
#define trigPin 18
#define echoPin 19
const int obstacleDistance = 15; // cm threshold

// Buzzer pin
#define buzzerPin 13

char lastCommand = 'S'; // Default to Stop
bool obstacleDetected = false;

// Buzzer timing variables
unsigned long previousBeepMillis = 0;
bool buzzerState = false;
const int beepInterval = 100; // 100ms interval for buzzer ON/OFF

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Sentron"); // Bluetooth name

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW); // Buzzer off initially

  stopCar();
}

void loop() {
  // Read obstacle distance
  long distance = getDistance();

  if (distance != -1 && distance < obstacleDistance) {
    obstacleDetected = true;
  } else {
    obstacleDetected = false;
  }

  if (SerialBT.available()) {
    lastCommand = SerialBT.read();
  }

  if (obstacleDetected) {
    if (lastCommand == 'B') {
      moveBackward();
      digitalWrite(buzzerPin, LOW); // No beep for backward
    } else {
      stopCar();
      beepBuzzer(); // Non-blocking beep
    }
  } else {
    handleCommand(lastCommand);
    digitalWrite(buzzerPin, LOW); // Buzzer off when normal
    buzzerState = false;           // Reset buzzer state
  }
}

// Handle normal commands
void handleCommand(char cmd) {
  switch (cmd) {
    case 'F':
      moveForward();
      break;
    case 'B':
      moveBackward();
      break;
    case 'L':
      turnLeft();
      break;
    case 'R':
      turnRight();
      break;
    case 'S':
      stopCar();
      break;
    case 'G':
      forwardRight();
      break;
    case 'H':
      backwardRight();
      break;
    case 'I':
      forwardLeft();
      break;
    case 'J':
      backwardLeft();
      break;
    default:
      stopCar();
      break;
  }
}

// Non-blocking Buzzer function
void beepBuzzer() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousBeepMillis >= beepInterval) {
    previousBeepMillis = currentMillis;
    buzzerState = !buzzerState; // Toggle buzzer state
    digitalWrite(buzzerPin, buzzerState ? HIGH : LOW);
  }
}

// Motor movement functions
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

void forwardRight() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backwardRight() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void forwardLeft() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void backwardLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// Get distance from ultrasonic sensor
long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // Timeout 30ms
  if (duration == 0) {
    Serial.println("Ultrasonic sensor timeout!");
    return -1; // Invalid
  }
  long distanceCm = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distanceCm);
  return distanceCm;
}