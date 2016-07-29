#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int16MultiArray.h"
#include "std_msgs/Int16.h"
#include "std_msgs/Float32.h"

#include <stdlib.h>

#include <sstream>

int co2_sim;
float temp_sim;
int pose_sim[16];
int speed_sim[2];



int main(int argc, char **argv)
{

  ros::init(argc, argv, "pub_sim");


  ros::NodeHandle n;


  ros::Publisher temp_pub = n.advertise<std_msgs::Float32>("temper", 1);
  ros::Publisher co2_pub = n.advertise<std_msgs::Int16>("co2", 1);
  ros::Publisher pose_pub = n.advertise<std_msgs::Int16MultiArray>("pose_robot", 1);
  ros::Publisher speed_pub = n.advertise<std_msgs::Int16MultiArray>("motor_speed", 1);



  ros::Rate loop_rate(100);  // Hz

  co2_sim = 0;
  temp_sim = 0.0;

  // Initial robot POSE
  pose_sim[0] = 0;          // Body Roll
  pose_sim[1] = 0;         // Body Pitch
  pose_sim[2] = 0;         // Body Yaw
  pose_sim[3] = 0;         // FL
  pose_sim[4] = 0;         // FR
  pose_sim[5] = 0;         // BL
  pose_sim[6] = 0;         // BR
  pose_sim[7] = 0;         // J1
  pose_sim[8] = 0;         // J2
  pose_sim[9] = 0;         // J3
  pose_sim[10] = 0;        // J4
  pose_sim[11] = 0;         // Hokuyo Roll
  pose_sim[12] = 0;         // Hokuyo Pitch
  pose_sim[13] = 0;         // Hokuyo Yaw

  speed_sim[0] = 0;
  speed_sim[1] = 0;

  std_msgs::Float32 temp;
  std_msgs::Int16 co2;
  std_msgs::Int16MultiArray robot_pos;
  std_msgs::Int16MultiArray motor_spd;


  while (ros::ok())
  {



    if(co2_sim >= 1999)
        co2_sim = 0;
    if(temp_sim >= 123)
        temp_sim = 0;

    // Robot Position Limit
    if(pose_sim[0] > 45)
        pose_sim[0] = -45;
    if(pose_sim[1] > 90)
        pose_sim[1] = -90;
    if(pose_sim[2] > 270)
        pose_sim[2] = -270;
    if(pose_sim[3] > 359)
        pose_sim[3] = 0;
    if(pose_sim[4] > 359)
        pose_sim[4] = 0;
    if(pose_sim[5] > 359)
        pose_sim[5] = 0;
    if(pose_sim[6] > 359)
        pose_sim[6] = 0;
    if(pose_sim[7] > 90)
        pose_sim[7] = 0;
    if(pose_sim[8] > 90)
        pose_sim[8] = 0;
    if(pose_sim[9] > 90)
        pose_sim[9] = 0;
    if(pose_sim[10] > 90)
        pose_sim[10] = 0;
    if(pose_sim[11] > 45)
        pose_sim[11] = 0;
    if(pose_sim[12] > 45)
        pose_sim[12] = 0;
    if(pose_sim[13] > 45)
        pose_sim[13] = 0;


    if(speed_sim[0] > 99)
        speed_sim[0] = 0;
    if(speed_sim[1] > 99)
        speed_sim[1] = 0;


    temp.data = temp_sim;
    co2.data = co2_sim;


    speed_sim[0] = rand() % 99 + 1;
    speed_sim[1] = rand() % 99 + 1;

    //speed_sim[0] = 20;
    //speed_sim[1] = 35;

    for(int i=0;i<=1;i++)
        motor_spd.data.push_back(speed_sim[i]);
    for(int i=0;i<=13;i++)
        robot_pos.data.push_back(pose_sim[i]);


    temp_pub.publish(temp);
    co2_pub.publish(co2);
    pose_pub.publish(robot_pos);
    speed_pub.publish(motor_spd);

    co2_sim++;
    temp_sim = temp_sim + 0.2;

    /*pose_sim[0]++;
    pose_sim[1]++;
    pose_sim[2]++;*/
    //pose_sim[3]++;
    //pose_sim[4]++;
    //pose_sim[5]++;
    //pose_sim[6]++;
    //pose_sim[7]++;
    pose_sim[8]++;
    pose_sim[9]++;
    pose_sim[10]++;
    /*pose_sim[11]++;
    pose_sim[12]++;
    pose_sim[13]++;*/


    robot_pos.data.clear();
    motor_spd.data.clear();

    ros::spinOnce();
    loop_rate.sleep();
  }


  return 0;
}
