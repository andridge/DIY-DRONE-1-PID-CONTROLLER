#include "imu.h"

ImuData readImuData() {
  ImuData data;
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(REG_ACCEL_X);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, NUM_REGISTERS_TO_READ, true);
  data.acc_x = Wire.read() << 8 | Wire.read();
  data.acc_y = Wire.read() << 8 | Wire.read();
  data.acc_z = Wire.read() << 8 | Wire.read();
  data.gyr_x = Wire.read() << 8 | Wire.read();
  data.gyr_y = Wire.read() << 8 | Wire.read();
  data.gyr_z = Wire.read() << 8 | Wire.read();
  return data;
}
