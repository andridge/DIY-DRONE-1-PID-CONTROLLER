#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

// Pin constants for motor control
#define PWM_1 3
#define AIN_1 4
#define AIN_2 5
#define PWM_2 6
#define BIN_1 7
#define BIN_2 8

// Set motor speeds
void setMotorSpeeds(double leftSpeed, double rightSpeed);

#endif
