# SoccerBot with ESP32

This project is a Bluetooth-controlled soccer bot using the ESP32 and various sensors to move the robot, including an ultrasonic sensor for obstacle detection and a buzzer for alerting. The robot can be controlled via Bluetooth commands, and the obstacle detection feature helps it avoid collisions.

## Features
- Bluetooth control via ESP32
- Movement controls for forward, backward, left, right, and stop
- Obstacle detection using the HC-SR04 ultrasonic sensor
- Buzzer alerts when an obstacle is detected
- Additional movement options for forward/backward with turns

## Equipment
- **4 DC Motors**: These drive the wheels of the robot.
- **L298N Motor Driver**: Controls the direction and speed of the motors.
- **Buzzer**: Alerts when the robot detects an obstacle.
- **HC-SR04 Ultrasonic Sensor**: Measures distance to detect obstacles in front of the robot.
- **ESP32 (38 pins)**: The microcontroller used to control the motors and Bluetooth communication.
- **2 x 3.7V Batteries**: Powers the ESP32 and the motors.
- **Switch**: Turns the robot on or off.
- **Jumper Wires**: For connecting the components together.

## Wiring Diagram

Here's a simple overview of how to wire the components:

- **DC Motors** connected to the **L298N Motor Driver**.
- **L298N Motor Driver** connected to the **ESP32** for controlling the motor direction and speed.
- **HC-SR04 Ultrasonic Sensor** connected to the **ESP32** to detect obstacles.
- **Buzzer** connected to the **ESP32** to provide an alert when an obstacle is detected.

## How to Use
1. Connect the components according to the wiring diagram.
2. Upload the code to the ESP32 using the Arduino IDE.
3. Pair your phone or computer with the ESP32 over Bluetooth (Bluetooth name: `Sentron`).
4. Send commands to the ESP32 using Bluetooth to control the robot:
   - `F` - Forward
   - `B` - Backward
   - `L` - Left
   - `R` - Right
   - `S` - Stop
   - `G` - Forward Right
   - `H` - Backward Right
   - `I` - Forward Left
   - `J` - Backward Left

The robot will move according to the commands sent via Bluetooth. If an obstacle is detected, the robot will stop, and the buzzer will alert.

## Installation
1. Install the necessary libraries in the Arduino IDE:
   - `BluetoothSerial` library for Bluetooth communication.
2. Connect the ESP32 to your computer via USB.
3. Select the correct board (`ESP32 Dev Module`) and port in the Arduino IDE.
4. Upload the provided code to the ESP32.
5. Connect the hardware components as per the wiring diagram.

## Future Updates
- Additional features like line following and advanced obstacle avoidance could be added.
- More movement options or control features might be introduced.

## License
This project is open-source. Feel free to use and modify the code, but please give credit if you do. 

---

Made with ❤️ by Md Yasin Hossain Akash
