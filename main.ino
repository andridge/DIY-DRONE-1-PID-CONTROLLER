#include "imu.h"
#include "pid.h"
#include "motor.h"
// Global variables for program 
unsigned long previousMillis = 0; 
int INTERVAL = 10;
float radToDeg = 180 / 3.141592654;
float DESIRED_ANGLE = 0;
double THROTTLE = 650;
float elapsedTime, time, timePrev;
float accelerationAngle[2];
float gyroAngle[2];
float totalAngle[2];
double pid;
double pwmLeft;
double pwmRight;
double error;
double previousError;
int inputByte = 'Z';
void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(250000);
  time = millis();
  pinMode(PWM_1, OUTPUT);
  pinMode(AIN_1, OUTPUT);
  pinMode(AIN_2, OUTPUT);
  pinMode(PWM_2, OUTPUT);
  pinMode(BIN_1, OUTPUT);
  pinMode(BIN_2, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= INTERVAL) {
    previousMillis = currentMillis;

    // Read raw data from IMU
    ImuData imuData = readImuData();

    // Calculate angles from raw IMU data
    timePrev = time;
    time = millis();
    elapsedTime = (time - timePrev) / 1000;
    accelerationAngle[0] = atan2(imuData.acc_y, imuData.acc_z + abs(imuData.acc_x)) * RAD_TO_DEG;
    accelerationAngle[1] = atan2(imuData.acc_x, imuData.acc_z + abs(imuData.acc_y)) * RAD_TO_DEG;
    gyroAngle[0] += (imuData.gyr_x / 131.0) * elapsedTime;
    gyroAngle[1] += (imuData.gyr_y / 131.0) * elapsedTime;

    // Calculate total angle using complementary filter
    totalAngle[0] = 0.98 * (totalAngle[0] + gyroAngle[0] * elapsedTime) + 0.02 * accelerationAngle[0];
    totalAngle[1] = 0.98 * (totalAngle[1] + gyroAngle[1] * elapsedTime) + 0.02 * accelerationAngle[1];

    // Calculate error for PID controller
    error = DESIRED_ANGLE - totalAngle[1];
    Serial.println(error);    
    // Calculate control signal for PID controller
    pid = calcPid(error, elapsedTime, previousError);
    previousError = error;
    Serial.println(pid);
    // Set motor speeds based on PID control signal
    pwmLeft = THROTTLE + pid;
    pwmRight = THROTTLE - pid;
    Serial.println(pwmLeft);
    Serial.println(pwmRight);
    Serial.println(THROTTLE);
    setMotorSpeeds(pwmLeft, pwmRight);

    // Read input from PS2 controller
    if (Serial.available()) {
      inputByte = Serial.read();
    }

    // Process input from PS2 controller
    switch (inputByte) {
      case 'Z':
        // Do nothing
        break;
      case 'W':
        // Increase throttle
        THROTTLE += 10;
        break;
      case 'S':
        // Decrease throttle
        THROTTLE -= 10;
        break;
      case 'A':
        // Decrease desired angle
        DESIRED_ANGLE -= 1;
        break;
      case 'D':
        // Increase desired angle
        DESIRED_ANGLE += 1;
        break;
      default:
        // Do nothing
        break;
    }
    previousMillis = currentMillis;
  }
}
