#define FlameSensorCenter A0
#define FlameSensorLeft A1
#define FlameSensorRight A2
#define MotorPin3 4
#define MotorPin1 2
#define MotorPin4 6
#define MotorPin2 5
#define threshold 500
#define pumpRelayPin 7
#define servoPin1 12
#define servoPin2 13

#include <Servo.h>
int direction = 1;

Servo servo1;
Servo servo2;

void setup() {
  Serial.begin(9600);
  pinMode(MotorPin1, OUTPUT);
  pinMode(MotorPin2, OUTPUT);
  pinMode(MotorPin3, OUTPUT);
  pinMode(MotorPin4, OUTPUT);
  pinMode(pumpRelayPin, OUTPUT);
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo1.write(90);
  delay(1150);
}

void loop() {
  int sensorValueCenter = analogRead(FlameSensorCenter);
  int sensorValueLeft = analogRead(FlameSensorLeft);
  int sensorValueRight = analogRead(FlameSensorRight);

  if (sensorValueCenter > threshold || sensorValueLeft > threshold || sensorValueRight > threshold) {
    stopMotors();
    activatePump();
    servo1.write(0);
    servo2.write(0);

    // Determine which sensor detected the flame (for potential directional response)
    if(sensorValueLeft > sensorValueRight && sensorValueLeft > sensorValueCenter){
        Serial.println("Left Flame Detected!");
        // Add code to handle left flame detection here (e.g., turn left)
    } else if (sensorValueRight > sensorValueLeft && sensorValueRight > sensorValueCenter){
        Serial.println("Right Flame Detected!");
        // Add code to handle right flame detection here (e.g., turn right)
    } else {
        Serial.println("Center Flame Detected!");
        // Add code to handle center flame detection here (e.g., stop)

    }
  } else {
    moveForward(30);
    deactivatePump();
    servo1.write(0);
    servo211();
  }
  delay(100);
}


//Motor Control Functions (Remember to adjust for your motor driver!)
void moveForward(int speed) {
  digitalWrite(MotorPin3, HIGH);
  digitalWrite(MotorPin1, HIGH);
  digitalWrite(MotorPin4, HIGH);
  digitalWrite(MotorPin2, HIGH);
}

void moveLeft() {
  digitalWrite(MotorPin3, HIGH);
  digitalWrite(MotorPin1, HIGH);
  digitalWrite(MotorPin4, LOW);
  digitalWrite(MotorPin2, LOW);
}

void moveRight() {
  digitalWrite(MotorPin3, LOW);
  digitalWrite(MotorPin1, LOW);
  digitalWrite(MotorPin4, HIGH);
  digitalWrite(MotorPin2, HIGH);
}

void stopMotors() {
  digitalWrite(MotorPin3, LOW);
  digitalWrite(MotorPin1, LOW);
  digitalWrite(MotorPin4, LOW);
  digitalWrite(MotorPin2, LOW);
}

void activatePump() {
  digitalWrite(pumpRelayPin, HIGH);
}

void deactivatePump() {
  digitalWrite(pumpRelayPin, LOW);
}

void servo211() {
  for (int position = 0; position <= 180; position++) {
    servo2.write(position);
    if (position == 180) direction = 0;
    delay(10);
  }
}