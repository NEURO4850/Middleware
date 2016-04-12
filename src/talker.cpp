
//Necessary includes for ros & geometry objects
#include "ros/ros.h"
#include "geometry_msgs/Point.h"



int main(int argc, char **argv)
{
  //Your node is called visionGroup
  ros::init(argc, argv, "visionGroup");
  ros::NodeHandle n;
  //You are publishing to the topic of 'vision' with a publish queue of 1
  //This will ensure that the sense & avoid group only recieves the newest
  ros::Publisher chatter_pub = n.advertise<geometry_msgs::Point>("vision", 1);
  //This is the rate of which you send messages
  //Acts like a sleep
  //You might want to change this to something smaller
  ros::Rate loop_rate(1000);

//while ros is okay 
  while (ros::ok())
  {
    //We decided that things will be sent as points
    geometry_msgs::Point p;
    
    
    //PUT YOUR FUNCTION HERE
    
    
  //which means everyone has an x,y, and z to work with
  //The rand()%25 is in there just for show.
  //You will want to edit this to reflect what you will set as your x,y,z values
  //Check with sense and avoid to make sure you all agree on what is x, y, z
   p.x = rand()%25;
   p.y = rand()%25;
   p.z = 3;
   //this will publish your message of this point
   chatter_pub.publish(p);
   
   //keep this
    ros::spinOnce();
  //this sleeps for the loop_rate set above
    loop_rate.sleep();
  }
  return 0;
}
// %EndTag(FULLTEXT)%
