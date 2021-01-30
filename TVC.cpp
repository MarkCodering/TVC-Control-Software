/*
This is program aims to control the thrust vector control (TVC) vehicle
using Arduino library and C programming Language
Author: Mark Chen (陳皓圓) and 許哲維
//Version: 0.1 (0 means that this is a initial script for the control system, testing and verification are required)
//System Control Concept: PID control with PID autotune libraray
*/

//Library
#include<PID_v1.h>
#include<Wire.h>
#include<Servo.h>
#include<Adafruit_Sensor.h> 
#include<Adafruit_ADXL345_U.h>

//Declare global variables
//Sensors - ADXL345
float AccX, AccY, AccZ; //for launching
float GyroX, GyroY, Gyroz;
float AngX, AngY, AngZ; //For stabilisation

//Height Sensor:
float cur_height;

//Control Variables
float setpoint_height_ascend;
int thrust;

int Servo_XR_Command;
int Servo_XL_Command;
int Servo_YR_Command;
int Servo_YL_Command;
int Thrust_Command;

//PID Controller
PID thrust_control_ascend(&cur_height, &thrust, &setpoint_height_ascend, 1,1,1, DIRECT);
PID stabilisation_ZX_1();
PID stabilisation_ZX_2();
PID stabilisation_ZY_1();
PID stabilisation_ZY_2();

Servo Servo_XR;
Servo Servo_XL;
Servo Servo_YR;
Servo Servo_YL;
Servo Thruster;

Adafruit_ADXL345_Unified ADXL345 = Adafruit_ADXL345_Unified();

void thrust_control_accend(float); //cur_height
void thrust_control_descend(float); //cure_height
void stabilisation(float, float, float); //AngX, AngY, AngZ

void setup()
{
    //Communication Establishment:
    Serial.begin(9600);
    Wire.begin();
  
    //Setup the sensors (ADXL345)
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
    sensors_event_t event; 
    accel.getEvent(&event);

    AccZ = event.acceleration.z();
    AccX = event.acceleration.y();
    AccY = event.acceleration.z();

    Thruster_Control(AccZ);
}

void thrust_control_accend(float input_height)
{

}