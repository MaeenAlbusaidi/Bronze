#include <WiFiS3.h>  // WiFi library for Arduino UNO R4 WiFi

// WiFi setup
WiFiServer server(5200);
WiFiClient client;
const char* ssid = "X10";  
const char* password = "12345678";

// Motor control pins
const int IN1 = 7;
const int IN2 = 8;
const int IN3 = 4;
const int IN4 = 11;
const int EN_A = 9;
const int EN_B = 5;

// IR sensor pins
const int LEYE = A4; 
const int REYE = A3; 

// Ultrasonic sensor pins
const int TRIGGER_PIN = 13;
const int ECHO_PIN = 12;

// Encoder pins
const int Encoder_L = 3;
const int Encoder_R = 2;

// PID control variables
volatile int leftCount = 0;
volatile int rightCount = 0;
unsigned long prevTimeL = 0, prevTimeR = 0;
float leftRPM = 0, rightRPM = 0;

double error, sumError, rateError, lastError = 0;
int PID;
int targetSpeed = 150;  // Default target speed (RPM)
double Kp = 1.5, Ki = 0.02, Kd = 0.5;

// Ultrasonic sensor variables
long US_travel_time;
int US_distance;

// Control flags
bool robotRunning = false;
bool alert = false;
bool objectFollowingMode = false;

// Interrupt Service Routine (ISR) for encoders
void leftEncoderISR() { leftCount++; }
void rightEncoderISR() { rightCount++; }

// Stop motors
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(EN_A, 0);
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(EN_B, 0);
}

// Move forward with given speed
void moveForward(int speedL, int speedR) {
  int leftSpeed = controlSpeed(speedL);
  int rightSpeed = controlSpeed(speedR);
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(EN_A, leftSpeed);
  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(EN_B, rightSpeed);
}

// Turn slightly right
void forwardRight(int speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(EN_A, speed);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(EN_B, speed);
}

// Turn slightly left
void forwardLeft(int speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(EN_A, speed);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(EN_B, speed);
}

// Measure speed from encoders
int measureSpeedLeft() {
  unsigned long currentTime = millis();
  if (currentTime - prevTimeL >= 100) {
    leftRPM = (leftCount / 8) * 60.0;
    leftCount = 0;
    prevTimeL = currentTime;
  }
  return leftRPM;
}

int measureSpeedRight() {
  unsigned long currentTime = millis();
  if (currentTime - prevTimeR >= 100) {
    rightRPM = (rightCount / 8) * 60.0;
    rightCount = 0;
    prevTimeR = currentTime;
  }
  return rightRPM;
}

// PID control for speed
int controlSpeed(int speed) {
  unsigned long currentTime = millis();
  double elapsedTime = currentTime - prevTimeL;

  error = targetSpeed - speed;
  sumError += error * elapsedTime;
  rateError = (error - lastError) / elapsedTime;
  
  PID = constrain(Kp * error + Ki * sumError + Kd * rateError, 50, 255);
  
  lastError = error;
  prevTimeL = currentTime;
  
  return PID;
}

// Get Ultrasonic Distance
int getDistance() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  US_travel_time = pulseIn(ECHO_PIN, HIGH);
  return US_travel_time * 0.034 / 2;
}

// Object following control
void followObject() {
  US_distance = getDistance();
  int error = US_distance - 15;  // Target distance 15cm
  int pidOutput = Kp * error;
  int motorSpeed = constrain(targetSpeed + pidOutput, 0, 255);
  moveForward(motorSpeed, motorSpeed);
}

// Line following control
void lineFollowLoop() {
  int value_SL = analogRead(LEYE);
  int value_SR = analogRead(REYE);

  if (value_SL >= 100 && value_SR >= 100) {
    moveForward(targetSpeed, targetSpeed);
  } else if (value_SL < 100 && value_SR >= 100) {
    forwardLeft(80);
  } else if (value_SL >= 100 && value_SR < 100) {
    forwardRight(80);
  } else {
    moveForward(targetSpeed, targetSpeed);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(EN_A, OUTPUT); pinMode(EN_B, OUTPUT);
  pinMode(LEYE, INPUT); pinMode(REYE, INPUT);
  pinMode(TRIGGER_PIN, OUTPUT); pinMode(ECHO_PIN, INPUT);
  
  Serial.println("Starting Access Point...");
  WiFi.beginAP(ssid, password);
  server.begin();
  
  pinMode(Encoder_L, INPUT_PULLUP); pinMode(Encoder_R, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Encoder_L), leftEncoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(Encoder_R), rightEncoderISR, CHANGE);
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        String command = client.readStringUntil('\n');
        command.trim();

        if (command == "START") robotRunning = true;
        if (command.startsWith("SPEED")) { objectFollowingMode = false; targetSpeed = command.substring(5).toInt(); }
        if (command == "STOP") { robotRunning = false; stopMotors(); }
        if (command == "OBJECT") objectFollowingMode = true;
      }
      if (robotRunning) objectFollowingMode ? followObject() : lineFollowLoop();
    }
    client.stop();
  }
}
