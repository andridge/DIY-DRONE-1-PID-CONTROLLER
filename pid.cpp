#include "pid.h"

double calcPid(double error, double elapsedTime, double previousError) {
  static double integral = 0;
  integral += error * elapsedTime;
  double derivative = (error - previousError) / elapsedTime;
  return (KP * error) + (KI * integral) + (KD * derivative);
}
