/*
This is program aims to control the thrust vector control (TVC) vehicle
using Arduino library and C programming Language
Author: Mark Chen (陳皓圓) and 許哲維
//Version: 0.1 (0 means that this is a initial script for the control system, testing and verification are required)
//System Control Concept:
//Stabilisation = (expectation - setpoint)*damper
//Stabilisation <=> Fuzzy Control Value Map
*/

#include<Arduino.h>
#include<Wire.h>
#include<Servo.h>
#include<ADXL345.h>
#include<MPU6050_light.h>

float setpoint_z = {};
float setpoint_angle_xz = {};
float setpoint_angle_yz = {};

float AccX, AccY, AccZ;
float GyroX, GyroY, Gyroz;
float AngX, AngY, AngZ;

int Servo_XR_Command;
int Servo_XL_Command;
int Servo_YR_Command;
int Servo_YL_Command;
int Thrust_Command;

int thrust_gain;
int Servo_X_gain;
int Servo_Y_gain;

Servo Servo_XR;
Servo Servo_XL;
Servo Servo_YR;
Servo Servo_YL;
Servo Thruster;

ADXL345 ACC(ADXL345_STD);
MPU6050 mpu(Wire);

//Stage Machine Data Zone:
//Stage 1: Lift-off -> 
//Stage 2: Stabilisation and Hovering -> 
//Stage 3: Hozential Hovering 
//Stage 4: Stabilisation and Landing Site Lockdown
//Stage 5: Landing and Touchdown

void setup()
{
    //Communication Establishment:
    Serial.begin(9600);
    Wire.begin();
  
    //Setup the sensors (ADXL345)
    mpu.begin();
    mpu.calcGyroOffsets();

    delay(1000);

    //Servo Setup
    Servo_XR.attach(6);
    Servo_XL.attach(9);
    Servo_YR.attach(11);
    Servo_YL.attach(13);
    Thruster.attach(7);

    //System Test:
    Thruster.write(300);
    Servo_XR.write(0);
    Servo_XL.write(0);
    Servo_YR.write(0);
    Servo_YL.write(0);

    delay(10000); //Delay for ten seconds for final confirmation and countdown
}

void loop()
{
    mpu.update();

    AccZ = mpu.getAccZ;
    AngX = mpu.getAccAngleX;
    AngY = mpu.getAccAngleY;

    //Stage Machine Scope
    if(AccZ == 0 || AngX == 0 || AngY == 0) //Stage 1 (Lift-off) (All motion stops and the GPS shows the vehicle is at launch site)
    {
        Thrust_Control(AccZ, setpoint_z);
        XZ_Control(AngX);
        YZ_Control(AngY);
        Serial.print("Lift-off Stage");
    }else if() //(Stabilisation and Hovering)
    {
        //XY Stablisation
        Thrust_Control();
        Serial.print("Stabilisation and Pre-hovering");
    }else if() //(Hovering)
    {
        //XZ Stablisation
    }else if() //(Stabilisation and Landing Site Lockdown)
    {
        //Landing
    }else if() //(Landing and Touchdown)
    {
        //Landing and Touchshut
    }
}
void Thrust_Control(AccZ, setpoint_z)
{
    //Thrust Control and Stabilisation
    AccZ = mpu.getAccZ;
    Thrust_Command = (setpoint_z - AccZ)*thrust_gain; //We need to define thrust_gain!!

    //Fuzzy Control Mapping and Maps:
    if (Thrust_Command > || Thrust_Command < )
    {
        Thruster.write();
    }else if(Thrust_Command > || Thrust_Command < )
    {
        Thruster.write();
    }else if(Thrust_Command > || Thrust_Command < )
    {
        Thruster.write();
    }else if(Thrust_Command > || Thrust_Command < )
    {
        Thruster.write();
    }else if(Thrust_Command > || Thrust_Command < )
    {
        Thruster.write();
    }else if(Thrust_Command > || Thrust_Command < )
    {
        Thruster.write();
    }else if(Thrust_Command > || Thrust_Command < )
    {
        Thruster.write();
    }else if(Thrust_Command > || Thrust_Command < )
    {
        Thruster.write();
    }else if(Thrust_Command > || Thrust_Command < )
    {
        Thruster.write();
    }else if(Thrust_Command > || Thrust_Command < )
    {
        Thruster.write();
    }
}

void XZ_Control()
{
   //XY Angle Stabilisation
}

void YZ_Control()
{
    //YZ Angular Stabilisation and Control
}