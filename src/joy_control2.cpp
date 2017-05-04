#include <ros/ros.h>
#include <std_msgs/UInt16.h>
#include <sensor_msgs/Joy.h>
#include <corobot_motor_control/motor_command.h>

class Servo
{
public:
  Servo();

private:
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);

  // axis indices for joystick controller
  int left_;
  int right_;
  int lin_scale_;

  ros::NodeHandle nh_;

 // Joystick tuning params
  int linear_, angular_;
  double l_scale_, a_scale_;

  // Joystick dev to listen to
  ros::Subscriber joy_sub_;

  // Robot bits to control
  ros::ServiceClient create_client;
  ros::ServiceClient servo_client;

  // Publisher for motor_command
  ros::Publisher robot_control_pub_;

  // Message ro be published 
  corobot_motor_control::motor_command msg_;  

};


Servo::Servo()
{
  lin_scale_ = 1;
  left_ = 1;
  right_ = 4;
  robot_control_pub_ = nh_.advertise<corobot_motor_control::motor_command>("cmd_robot", 10);
  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &Servo::joyCallback, this);
}  

void Servo::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  msg_.left_speed = 90 + 90*lin_scale_*joy->axes[left_];
  msg_.right_speed = 90 + 90*lin_scale_*joy->axes[right_];
  robot_control_pub_.publish(msg_);
}


int main(int argc, char** argv) 
{
  ros::init(argc, argv, "servo_joy");
  Servo servo_joy;

  ros::spin();
}
