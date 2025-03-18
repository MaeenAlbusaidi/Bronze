/*
 * Object Following Code with Placeholder PID Function
 * ------------------------------------------------------
 * This code is structured to allow integration with PID controller.
 * The function getPIDOutput() currently uses a simple proportional gain (Kp).
 * Replace getPIDOutput() with full PID algorithm.
 */

//pins for the ultrasonic sensor
const int TRIGGER_PIN = 13;
const int ECHO_PIN = 12;

//pins for motor control
const int IN1 = 6;
const int IN2 = 7;
const int IN3 = 3;
const int IN4 = 11;
const int EN_A = 9;
const int EN_B = 5;

//constants for object following
const int TARGET_DISTANCE = 15;  //distance from object (cm)
const int BASE_SPEED = 90;       //base motor speed when at target distance
const float Kp = 5.0;            //placeholder for PID

//function prototypes
float getDistance();
float getPIDOutput(float error);
void setMotorSpeed(int speed);
void stopMotors();
void followObject();

void setup() {
  Serial.begin(9600);

  //set up motor control pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN_A, OUTPUT);
  pinMode(EN_B, OUTPUT);

  //set up ultrasonic sensor pins
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.println("Object Following Test: Replace getPIDOutput() with your PID code as needed.");
}

void loop() {
  followObject();
  delay(100); //adjust loop delay as needed for stability
}

//reads the distance from the ultrasonic sensor
float getDistance() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2; //convert travel time to cm
  return distance;
}

/*
 * Placeholder PID function.
 * Replace this function with full PID controller logic.
 * It should take the error
 * and return the computed control output.
 */
float getPIDOutput(float error) {
  // Currently using simple proportional control:
  return Kp * error;
}

//sets the motor speed for forward motion
void setMotorSpeed(int speed) {
  // Motor A (right)
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(EN_A, speed);
  
  //motor B (left) with slight speed offset for balance
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(EN_B, speed + 10);
}

//stops both motors
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(EN_A, 0);
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(EN_B, 0);
}

//main function for following an object at the target distance
void followObject() {
  float distance = getDistance();
  float error = distance - TARGET_DISTANCE;
  
  //get PID output (control signal); replace getPIDOutput() with your PID code if needed.
  float pidOutput = getPIDOutput(error);
  
  //calculate motor speed based on base speed plus PID output
  int motorSpeed = BASE_SPEED + (int)pidOutput;
  motorSpeed = constrain(motorSpeed, 0, 255);  // Ensure speed stays in valid range
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm, Error: ");
  Serial.print(error);
  Serial.print(" PID Output: ");
  Serial.print(pidOutput);
  Serial.print(" Motor Speed: ");
  Serial.println(motorSpeed);
  
  //simple decision logic:
  // - If the object is farther than the target (plus a small buffer), move forward.
  // - If it's too close, stop.
  // - Otherwise, maintain a steady pace.
  if (distance > TARGET_DISTANCE + 2) {
    setMotorSpeed(motorSpeed);
  } else if (distance < TARGET_DISTANCE - 2) {
    stopMotors();
  } else {
    setMotorSpeed(BASE_SPEED);
  }
}
