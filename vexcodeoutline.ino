#include <Vex.h>
//b#include <LiquidCrystal.h>
// vex object named robot
Vex Robot;

// motor objects
Adafruit_DCMotor *motorA = Robot.setMotor(4); 
Adafruit_DCMotor *motorB = Robot.setMotor(3);

//
Gyro gyro;
float angleZ;
float angleX;
float angleY;


// ultrasonic sensors
#define echoPin 5 // front
#define trigPin 6 // front
#define echoPin2 10 // right wall
#define trigPin2 11 // right wall

long duration; // variable for the duration of sound wave travel
int distanceFront; // variable for the distance measurement
long duration2;
int distanceWall;

// Tracking Distance list
int array[] = {25};
int movefoward = 0;
int count = 0;

//lcd dsiplay
//LiquidCrystal lcd(12,11,5,4,3,2);


void setup() {
  Serial.begin(9600);
  Robot.begin();
  gyro.begin();
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin2, INPUT); // Sets the echoPin as an INPUT

  // set up the LCD's number of columns and rows:
  //lcd.begin(16, 2);
  
}

void loop() {
  //lcd display
  //lcd.setCursor(0,0);

  // Ultrasonics 1 & 2
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);  
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceWall = duration * 0.034 / 2; // Calculating the distance in cm

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distanceFront = duration2 * 0.034 / 2; // Calculating the distance in cm
  
  Serial.println("Distance Front: ");
  Serial.println(distanceFront);
  Serial.println("Distance Wall: ");
  Serial.println(distanceWall);
  delay(300);

//Movement
  
  if (distanceFront > 5) {
    Robot.moveTank(motorA,motorB,50,50,.5); 
    movefoward = movefoward + 1; // tracking distance
    Serial.println(movefoward);
    //lcd.print("Moving Foward");
  }
  else {
  // make a  left turn here
  Serial.println("Left turn");
  //lcd.print("Left turn");
  float current = gyro.getZAngle();
  float initial = current;
  Serial.print("First Angle: ");
  Serial.print(initial);

  if( initial >90 && initial < 180 ){ // for quadrant 3
    Serial.print("----------------------------------------------");
    while(current > 0){
      Serial.print("current: ");
      Serial.print(current);
      Robot.moveTank(motorA,motorB,20, -20,0.05); //move right motor forward and left motor backwards slowly to turn
      delay(200); //give robot time to stabilize before next gyro reading
      current = gyro.getZAngle(); //update current angle to the new position
    }
    float leftover = 90 - (180 - initial);
    float finall = -180 + leftover;
    Serial.println(leftover);
    Serial.println(finall);
    while( current < finall ){
      Serial.print("current: ");
      Serial.print(current);
      Robot.moveTank(motorA,motorB,20, -20,0.05); //move right motor forward and left motor backwards slowly to turn
      delay(200); //give robot time to stabilize before next gyro reading
      current = gyro.getZAngle(); //update current angle to the new position
    }
  }
  else{ // for quadrant 1,2,4
    Serial.print("++++++++++++++++++++++++++++++++++++++++++++++");
    float finall = initial + 90;
    Serial.print("Final: ");
    Serial.print(finall);
    while( current < finall){
      Serial.println("turning");
      Robot.moveTank(motorA,motorB,20, -20,0.05); //move right motor forward and left motor backwards slowly to turn
      delay(200); //give robot time to stabilize before next gyro reading
      current = gyro.getZAngle(); //update current angle to the new position
        Serial.print("Angle after turn");
        Serial.println(current);
    }
  }
  array[count] = movefoward;
  count = count + 1;
  Serial.println(movefoward);
  movefoward = 0;
  }
  // on lcd or serial monitor, print out the lengths of the walls
  //lcd.setCursor(0,1); // column 0, line 1 (second row)
  for (int x = 0; x < 10; x++)
  {
     Serial.println(array[x]);
     //lcd.print(array[x]);
     
  //stay near a wall
  //while (distanceWall > 15);
    //Robot.moveTank(motorA,motorB,-30, 30,0.2);
    //Robot.moveTank(motorA,motorB,30,30, 0.2);
  
  // determine number of walls counted
  if (count = 3){ // for a rectangular room
    Robot.end();
   }
  }
}
