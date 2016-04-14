/* 
 * rosserial Subscriber Example
 * Blinks an LED on callback
 */

#include <ros.h>
#include <geometry_msgs/Point.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"


ros::NodeHandle  nh;

geometry_msgs::Point p;
ros::Publisher motorSend("motor", &p);

const int pingPin = 7;  //Pin for the ultrasonic sensor

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_StepperMotor *myMotor = AFMS.getStepper(360, 2);

// variables for ultrasonic sensor
double angle, newAngle, angleDiff;
double counter = 0;
double backAngle;

void visionCallback( const geometry_msgs::Point& msgIn)
{
  nh.loginfo("Recieved From Vision Group");
  p = msgIn;
  detectAvoid();

  motorSend.publish( &p);
  nh.spinOnce(); //sends messages

}


ros::Subscriber<geometry_msgs::Point> sub("vision", &visionCallback );



void setup()
{ 

  nh.initNode();
  nh.advertise(motorSend);
  nh.subscribe(sub);

  AFMS.begin();
  myMotor->setSpeed(80);

}

void loop()
{ 

  nh.spinOnce(); //listens for incoming
  delay(1); //not sure if delay should be used
}

void detectAvoid(){
  newAngle = coorToAng();
  angleDiff = newAngle - counter;
  if (angleDiff > 0) {
    go(angleDiff, 1);
  } else if (angleDiff < 0) {
    go(angleDiff, 0);
  } else {
    idle();
  }
    angle = newAngle;
  counter = newAngle;
}

// Scan the direction facing, return the distance of the obsticle
long getDist() {
  long duration;

  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  long cm = duration / 29 / 2;

  return cm;
}

// check the direction of the new coordinate, if obsticle, turn sensor right 90,
//if something there, turn left 100, if somthing left reverse
void checkDir() {
  long cm = getDist();
  if (cm < 50) {
    //x = 0;
    //y = 0;
    myMotor->step(50, 0, DOUBLE);
    long sideCM = getDist();
    if (sideCM < 20) {
      myMotor->step(100, 1, DOUBLE);
      sideCM = getDist();
      myMotor->step(50, 0, DOUBLE);
      if (sideCM < 20) {
        p.x *= -1;
        p.y *= -1;
      } else {
        angToCoor(90);
      }
    } else {
      angToCoor(-90);
      myMotor->step(50, 0, DOUBLE);
    }
  }
}

void go(double angle, int direct) {
  angle = abs(angle);
  int steps = angle / 1.8;
  myMotor->step(steps, direct, DOUBLE);

  checkDir();
  delay(100);
}

void idle() {
  delay(1);
}

//Coord to angle
double coorToAng() {
  double ang = atan2(p.y, p.x);
  ang = ang * (180 / 3.14159265359);
  return ang;
}

//get Coord from angle
void angToCoor(int w) {
  p.y = tan(newAngle + w) * p.x;
}

