#include "motor.h"

void setMotorSpeeds(double leftSpeed, double rightSpeed) {
  // Constrain speeds to range 0-1023
  leftSpeed = constrain(leftSpeed, 0, 1023);
  rightSpeed = constrain(rightSpeed, 0, 1023);

  // Set left motor speed
  if (leftSpeed > 0) {
    // Forward
    digitalWrite(AIN_1, LOW);
    digitalWrite(AIN_2, HIGH);
  } else if (leftSpeed < 0) {
    // Reverse
    digitalWrite(AIN_1, HIGH);
    digitalWrite(AIN_2, LOW);
    leftSpeed = -leftSpeed;
  } else {
    // Stop
    digitalWrite(AIN_1, LOW);
    digitalWrite(AIN_2, LOW);
  }
  analogWrite(PWM_1, leftSpeed);

  // Set right motor speed
  if (rightSpeed > 0) {
    // Forward
    digitalWrite(BIN_1, LOW);
    digitalWrite(BIN_2, HIGH);
  } else if (rightSpeed < 0) {
    // Reverse
    digitalWrite(BIN_1, HIGH);
    digitalWrite(BIN_2, LOW);
    rightSpeed = -rightSpeed;
    
  } else {
    // Stop
    digitalWrite(BIN_1, LOW);
    digitalWrite(BIN_2, LOW);
  }
  analogWrite(PWM_2, rightSpeed);
}
