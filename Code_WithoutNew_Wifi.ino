//For Motor Driver
const int IN1 = 6 ; // motor A (right) s1
const int IN2 = 7; // motor A (right)s2
const int IN3 = 3; // motor B (left)s3
const int IN4 = 11; // motor B (left)s4
const int EN_A = 9;
const int EN_B = 5;

//For US Sensor
const int TRIGGER_PIN = 13;
const int ECHO_PIN = 12;
long US_travel_time;
int US_distance;

//For IR Sensor
const int LEYE = A4; // Left sensor
const int REYE = A3; // Right sensor

const int unit = 1000; // assign unit to be one second for the time management

void stopmove (){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(EN_A, 0);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(EN_B, 0);

}
void Breaks (){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(EN_A, 0);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(EN_B, 0);

}
void moveforward(int speed){ // function to drive forward with int speed 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(EN_A, (speed));

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(EN_B, (speed+10));
}

void movebackward (int speed) { //funstion to drive backward wiht int speed
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(EN_A, (speed));

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(EN_B, (speed+5));
}

void forwardRight (int speed) {
  //motor a
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(EN_A, (speed));
//motor b
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(EN_B, (speed));
}

void forwardLeft (int speed) {
  //motor a
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(EN_A, (speed));
//motor b
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(EN_B, (speed));
}

void backwardturnRight (int speed){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(EN_A, speed);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(EN_B, (speed/2));
}

void backwardturnLeft (int speed){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(EN_A, speed/2);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(EN_B, (speed));
}

void setup() {
Serial.begin(9600);

//Motor Driver
pinMode (IN1, OUTPUT);
pinMode (IN2, OUTPUT);
pinMode (IN3, OUTPUT);
pinMode (IN4, OUTPUT);
pinMode (EN_A, OUTPUT);
pinMode (EN_B, OUTPUT);

//IR Sensors
pinMode( LEYE, INPUT ); // the IRn sensor1 
pinMode( REYE, INPUT ); // the IR sensor 2

//US Sensors
pinMode(TRIGGER_PIN, OUTPUT);
pinMode(ECHO_PIN, INPUT);

//End of setup
}

void loop() {
int value_SL = analogRead(LEYE);
int value_SR = analogRead (REYE);
Serial.print("left : ");
Serial.println(value_SL);
Serial.print("right : ");
Serial.println( value_SR);

//delay (2000);

if (value_SL>=100 && value_SR>=100){
  moveforward(80);
}else if (value_SL<100 && value_SR>=100){
  forwardLeft(70);
}else if (value_SL>=100 && value_SR<100){
  forwardRight(70);
}else if (value_SL<100 && value_SR<100){
  stopmove();
}

//US Sensor
//Clearing any history from the TRIGGER_PIN
digitalWrite(TRIGGER_PIN, LOW);
delayMicroseconds(2);

//Generating US wave
digitalWrite(TRIGGER_PIN, HIGH);
delayMicroseconds(10);
digitalWrite(TRIGGER_PIN, LOW);

//pulseIn function waits for the ECHO_PIN to get to high caused by the sound wave bouncing back. It starts a timer which ends when the ECHO_PIN goes to low again.
//pulseIn then returns the length of the pulse in micro seconds.
US_travel_time = pulseIn(ECHO_PIN, HIGH);

//0.034 is the speed of sound in cm/micro second. Divided by 2 as the wave travels to the object and back again
US_distance = US_travel_time*0.034/2;

  if (US_distance <= 10) {
    
    //Stops the motors if there is an object <= 10cm
    stopmove();
  } else {

    if (value_SL >= 100 && value_SR >= 100) {
      moveforward(80);
    } else if (value_SL < 100 && value_SR >= 100) {
      forwardLeft(70);
    } else if (value_SL >= 100 && value_SR < 100) {
      forwardRight(70);
    } else if (value_SL < 100 && value_SR < 100) {
      stopmove();
    }
  }

  delay(100);

//This is the end of the loop
}

/*if (pwmSL<=150 && pwmSR<=150){
  moveforward(50);
}else if (pwmSL>150 && pwmSR<=150){
  forwardturnLeft(50);
}else if ((pwmSL<=150 && pwmSR>150)){
  forwardturnRight(50);
}*/

/*Serial.print("left");
Serial.println(value_SL);
Serial.print("right");
Serial.println( value_SR);

delay (2000);*/
