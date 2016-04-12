/* 
 * rosserial Subscriber Example
 * Blinks an LED on callback
 */

#include <ros.h>
#include <geometry_msgs/Point.h>


ros::NodeHandle  nh;

geometry_msgs::Point p;
ros::Publisher motorSend("motor", &p);


void visionCallback( const geometry_msgs::Point& msgIn)
{
  nh.loginfo("Recieved From Vision Group");
  p.x=0;
  p.y=0;
  p.z=0;

  motorSend.publish( &p);
  nh.spinOnce(); //sends messages

}


ros::Subscriber<geometry_msgs::Point> sub("vision", &visionCallback );



void setup()
{ 

  nh.initNode();
  nh.advertise(motorSend);
  nh.subscribe(sub);


}

void loop()
{ 

  nh.spinOnce(); //listens for incoming
  delay(1); //not sure if delay should be used
}


