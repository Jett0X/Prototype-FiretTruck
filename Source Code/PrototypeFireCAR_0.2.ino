#define Flame_Sensor_Pin A0
#define Motor_Pin_3 4
#define Motor_Pin_1 2
#define Motor_Pin_4 6
#define Motor_Pin_2 5
#define threshold 500
#define pumpRelayPin 7
///////////////
#define servoPin1 12 // Servo 1 pin
#define servoPin2 13 // Servo 2 pin

#include <Servo.h> // Include the Servo library
int direction = 1;

Servo servo1; // Create servo object to control a servo 
Servo servo2; // Create servo object to control a servo

void setup() {
  Serial.begin(9600);
  pinMode(Motor_Pin_1, OUTPUT);
  pinMode(Motor_Pin_2, OUTPUT);
  pinMode(Motor_Pin_3, OUTPUT);
  pinMode(Motor_Pin_4, OUTPUT);
  pinMode(pumpRelayPin, OUTPUT); 
  servo1.attach(servoPin1); //Attach servo1 to pin 12
  servo2.attach(servoPin2); //Attach servo2 to pin 13
   //////
  servo1.write(60);
  delay(1150); 
}

void loop() {
  int sensorValue = analogRead(Flame_Sensor_Pin);

  if (sensorValue > threshold) {
    stopMotors();
    activatePump();
    //Example:  Move servos to a specific position when flame is detected
    servo1.write(0); //Example position for servo1 
    servo2.write(0);  //Example position for servo2
  } else {
    moveForward(30);
    delay(690);
    stopMotors();
    stopMotors();
    deactivatePump();
    //Example: Move servos to a different position when no flame is detected
    servo1.write(0);  //Example position for servo1
    servo211();
    delay(150);
  }
  delay(150);
}

void moveForward(int speed) {
  digitalWrite(Motor_Pin_3, HIGH);
  digitalWrite(Motor_Pin_1, HIGH);
  digitalWrite(Motor_Pin_4, HIGH);
  digitalWrite(Motor_Pin_2, HIGH);
}

void stopMotors() {
  digitalWrite(Motor_Pin_3, LOW);
  digitalWrite(Motor_Pin_1, LOW);
  digitalWrite(Motor_Pin_4, LOW);
  digitalWrite(Motor_Pin_2, LOW);
}

void activatePump() {
  digitalWrite(pumpRelayPin, HIGH);
}

void deactivatePump() {
  digitalWrite(pumpRelayPin, LOW);
}

void servo211(){
  for (int position = 0; position <= 180; position++) {
      servo2.write(position);
      if (position == 180) direction = 0;
      delay(10);
    }
}