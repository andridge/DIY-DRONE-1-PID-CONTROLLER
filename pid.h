#ifndef PID_H
#define PID_H

#include <Arduino.h>

// Constants for PID controller
#define KP 3.55
#define KI 0.005
#define KD 2.05

// Calculate control signal for PID controller
double calcPid(double error, double elapsedTime, double previousError);

#endif
