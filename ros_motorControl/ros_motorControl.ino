/* 
 * rosserial Subscriber Example
 * Blinks an LED on callback
 */

#include <ros.h>
#include <geometry_msgs/Point.h>


ros::NodeHandle  nh;

void messageCb( const geometry_msgs::Point& p){

   float x = p.x;
   float y = p.y; // and z

 
    nh.loginfo("Recieved from Detect and Avoid Group");
  
}

ros::Subscriber<geometry_msgs::Point> sub("motor", &messageCb );

void setup()
{ 

 
  nh.initNode();
  nh.subscribe(sub);
  

}

void loop()
{ 
  //Listen for command on delay(1)
  nh.spinOnce();
  delay(1);


}

