#define echoPin 2 // attach pin D2 Arduino to pin Echo of sesnor
#define trigPin 3 //attach pin D3 Arduino to pin Trig of sensor
#include<Wire.h>

// define variable
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
const int MPU_addr = 0x68; 
int16_t GyX, GyY, GyZ; 


void setup() {
  // Ultrasonic
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
  // Gyro
  Wire.begin(); 
  Wire.beginTransmission(MPU_addr); 
  Wire.write(0x6B);  
  Wire.write(0); 
  Wire.endTransmission(true); 

}

void loop() {
  // Gyro
  gyro();
  //led();

  // Ultrasonic
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  /*
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  */
  /*
  if (condition) {
    do_this;
  }
  else {
    do_this_if_false;
  }
  */
  if (distance <= 20){
    Serial.println("turn right");
  }
  else {
    Serial.println("Move foward");
  }
  delay(300);

}

void gyro() {
  Wire.beginTransmission(MPU_addr); 
  Wire.write(0x3B); 
  Wire.endTransmission(false); 
  Wire.requestFrom(MPU_addr, 14, true); 
  GyX = Wire.read() << 8|Wire.read(); 
  GyY = Wire.read() << 8|Wire.read(); 
  GyZ = Wire.read() << 8|Wire.read();
  GyX = GyX / 100;
  GyY = GyY / 100;
  GyZ = GyZ / 100;
  /*
  Serial.print(F("gyro x,y,z : "));
  Serial.print("| GyX = ");
  Serial.print(GyX);
  Serial.print("| GyY = ");
  Serial.print(GyY);
  Serial.print("| GyZ = ");
  Serial.print(GyZ);
  Serial.println();
  */
  delay(300);
}
/*
void led() {
    if (GyX >= -20 && GyX <= -10) {
    if (GyY >= -10 && GyY <= 0) {
    if (GyZ >= 145 && GyZ <= 155) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);
      digitalWrite(blue, HIGH);
  }
  }
  }
    else if (GyX >= 0 && GyX <= 10) {
    if (GyY >= -175 && GyY <= -165) {
    if (GyZ >= -20 && GyZ <= -10) {
      digitalWrite(red, HIGH);
      digitalWrite(green, LOW);
      digitalWrite(blue, LOW);
  }
  }
  }
    else if (GyX >= 165 && GyX <= 175) {
    if (GyY >= -10 && GyY <= 0) {
    if (GyZ >= 10 && GyZ <= 20) {
      digitalWrite(red, LOW);
      digitalWrite(green, HIGH);
      digitalWrite(blue, LOW);
  }
  }
  }
    else if (GyX >= -155 && GyX <= -145) {
    if (GyY >= -5 && GyY <= 5) {
    if (GyZ >= -40 && GyZ <= -30) {
      digitalWrite(red, LOW);
      digitalWrite(green, LOW);
      digitalWrite(blue, HIGH);
  }
  }
  }
  else {
    digitalWrite(red, LOW);
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
  }
}*/
