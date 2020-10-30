#include<Arduino.h>
#include<Wire.h>
#include<Servo.h>
#include<ADXL345.h>
#include<MPU6050_light.h>

float setpoint_z = 0;
float setpoint_angle_xz;
float setpoint_angle_yz;

int Servo_xz;
int Servo_yz;

Servo ServoXZ;
Servo ServoYZ;
Servo Thruster;

ADXL345 ACC(ADXL345_STD);
MPU6050 mpu(Wire);

void setup()
{
    Serial.begin(9600);
    Wire.begin();
  
    ServoXZ.attach(9);
    ServoYZ.attach(13);
  
     //Setup the sensors (ADXL345)
    mpu.begin();
    mpu.calcGyroOffsets();
}

void loop()
{

}