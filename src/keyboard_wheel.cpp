#include <iostream>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <curses.h>

using namespace std;

#define _KEY_UP 'A'
#define _KEY_DOWN 'B'
#define _KEY_RIGHT 'C'
#define _KEY_LEFT 'D'
#define _KEY_STOP 'E'//press eny key to stop

ros::Publisher wheel_command_publisher;

char read_arrow_key()
{
    if(getch() == 27)
    {
        getch();
        return getch();
    }
    return 0;
}

void publish_wheel_command(char key)
{
    geometry_msgs::Twist msg;
    switch(key){
        case _KEY_UP:
        
        msg.linear.x = 0.1;
        msg.angular.z= 0.0; 
        ROS_INFO("KEY_UP\r");
        break;
        case _KEY_DOWN:
        msg.linear.x = -0.1;
        msg.angular.z= 0.0; 
        ROS_INFO("KEY_DOWN\r");
        break;
        case _KEY_LEFT:
        msg.linear.x = 0.0;
        msg.angular.z= 0.5; 
        ROS_INFO("KEY_LEFT\r");
        break;
        case _KEY_RIGHT:
        msg.linear.x = 0.0;
        msg.angular.z= -0.5; 
        ROS_INFO("KEY_RIGHT\r");
        break;
        case _KEY_STOP:
        msg.linear.x = 0.0;
        msg.angular.z= 0.0; 
        ROS_INFO("KEY_STOP\r");
        break;
    }

    wheel_command_publisher.publish(msg);
} 



int main(int argc, char **argv)
{
  ros::init(argc, argv, "keyboard_wheel");
  ros::NodeHandle node;
  wheel_command_publisher = node.advertise<geometry_msgs::Twist>("cmd_vel", 1000);   
  ros::Rate loop_rate(10);

  initscr();
  cbreak;
  char key;

  while (ros::ok())
  {
    key = read_arrow_key();
    cout <<"\e[1;1H\e[2J";
    
    publish_wheel_command(key);
  }

  endwin();
  return 0;
}
