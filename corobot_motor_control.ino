#include <Servo.h>

Servo left_motor;  // create servo object to control a servo
Servo right_motor;  // create servo object to control a servo
int val_left = 120;
int val_right = 90;

void setup() {
  left_motor.attach(9);  // attaches the servo on pin 9 to the servo object
  right_motor.attach(10);  // attaches the servo on pin 9 to the servo object
}

void loop() {
//  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
//  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  left_motor.write(val_left);                  // sets the servo position according to the scaled value
  right_motor.write(val_right);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there
}
