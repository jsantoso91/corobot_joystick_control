/*
 * rosserial Servo Control Example
 *
 * This sketch demonstrates the control of hobby R/C servos
 * using ROS and the arduiono
 * 
 * For the full tutorial write up, visit
 * www.ros.org/wiki/rosserial_arduino_demos
 *
 * For more information on the Arduino Servo Library
 * Checkout :
 * http://www.arduino.cc/en/Reference/Servo
 */

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include <WProgram.h>
#endif

#include <Servo.h> 
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <corobot_motor_control/motor_command.h>

ros::NodeHandle  nh;

Servo left_motor;
Servo right_motor;

void servo_cb( const corobot_motor_control::motor_command& cmd_msg){
  left_motor.write(cmd_msg.left_speed); //set servo angle, should be from 0-180  
  right_motor.write(cmd_msg.right_speed);
  digitalWrite(13, HIGH-digitalRead(13));  //toggle led
}


ros::Subscriber<corobot_motor_control::motor_command> cmd_sub("cmd_robot", servo_cb);

void setup(){
  pinMode(13, OUTPUT);

  nh.initNode();
  nh.subscribe(cmd_sub);
  
  left_motor.attach(9); 		//attach it to pin 9
  right_motor.attach(10);
}

void loop(){
  nh.spinOnce();
  delay(5);
}
