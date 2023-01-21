#ifndef IMU_H
#define IMU_H

#include <Wire.h>

// Constants for IMU
#define MPU_ADDR 0x68
#define REG_ACCEL_X 0x3B
#define NUM_REGISTERS_TO_READ 6

// Struct to store raw IMU data
struct ImuData {
  int16_t acc_x;
  int16_t acc_y;
  int16_t acc_z;
  int16_t gyr_x;
  int16_t gyr_y;
  int16_t gyr_z;
};

// Read raw data from IMU
ImuData readImuData();

#endif
