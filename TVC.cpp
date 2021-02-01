/*
This is program aims to control the thrust vector control (TVC) vehicle
using Arduino library and C programming Language
Author: Mark Chen (陳皓圓) and 許哲維
//Version: 0.1 (0 means that this is a initial script for the control system, testing and verification are required)
//System Control Concept: PID control with PID autotune libraray
*/

//Library
#include<Wire.h>
#include<Servo.h>
#include<PID_v1.h>
#include<BMP280_DEV.h> // Include the BMP280_DEV.h library
#include<Adafruit_Sensor.h> 
#include<Adafruit_ADXL345_U.h>

//Declare global variables
//Sensors - ADXL345
double AccX, AccY, AccZ; //for launching
double GyroX, GyroY, Gyroz;
double AngX, AngY, AngZ; //For stabilisation

//Height Sensor:
double cur_height;

//Setpoints
double setpoint_height_ascend = 38.0;
double setpoint_height_descent = 100;
double setpoint_AngX = 0;
double setpoint_AngY = 0;
double setpoint_AngZ = 0;

//Control Variables
double thrust;
double Servo_XR_Command;
double Servo_XL_Command;
double Servo_YR_Command;
double Servo_YL_Command;
double Thrust_Command;

//PID Controller
PID thrust_control_ascend_PID(&cur_height, &thrust, &setpoint_height_ascend, 0.5,0.5,0.5, DIRECT);
PID thrust_control_descend_PID(&cur_height, &thrust, &setpoint_height_descent, 1,1,1, DIRECT);
PID stabilisation_ZX_1(&AngX, &Servo_XR_Command, &setpoint_AngX, 1,1,1, DIRECT);
PID stabilisation_ZX_2(&AngX, &Servo_XL_Command, &setpoint_AngX, 1,1,1, DIRECT);
PID stabilisation_ZY_1(&AngY, &Servo_YR_Command, &setpoint_AngY, 1,1,1, DIRECT);
PID stabilisation_ZY_2(&AngY, &Servo_YL_Command, &setpoint_AngY, 1,1,1, DIRECT);

Servo Servo_XR;
Servo Servo_XL;
Servo Servo_YR;
Servo Servo_YL;
Servo Thruster;

//Sensor Declaration:
float temperature, pressure, altitude;            // Create the temperature, pressure and altitude variables
BMP280_DEV bmp280;  
  
Adafruit_ADXL345_Unified ADXL345_sensor = Adafruit_ADXL345_Unified(12345);

void thrust_control_ascend(double); //cur_height
void thrust_control_descend(double); //cure_height
void stabilisation(double, double, double); //AngX, AngY, AngZ

void setup()
{
    //Communication Establishment:
    Serial.begin(115200);
    Wire.begin();
  
    //Setup the sensors (ADXL345)
    bmp280.begin(BMP280_I2C_ALT_ADDR);              // Default initialisation with alternative I2C address (0x76), place the BMP280 into SLEEP_MODE 
    bmp280.setTimeStandby(TIME_STANDBY_2000MS);     // Set the standby time to 2 seconds
    bmp280.startNormalConversion(); 
    delay(1000);

    //Servo Setup
    Servo_XR.attach(6);
    Servo_XL.attach(9);
    Servo_YR.attach(11);
    Servo_YL.attach(13);
    Thruster.attach(7);

    //System Test:
    thrust = 300;
    thrust = map(thrust, 0, 1023, 0, 180);
    Thruster.write(thrust);
    Servo_XR.write(0);
    Servo_XL.write(0);
    Servo_YR.write(0);
    Servo_YL.write(0);

    thrust_control_ascend_PID.SetMode(AUTOMATIC);
    thrust_control_descend_PID.SetMode(AUTOMATIC);
    stabilisation_ZX_1.SetMode(AUTOMATIC);
    stabilisation_ZX_2.SetMode(AUTOMATIC);
    stabilisation_ZY_1.SetMode(AUTOMATIC);
    stabilisation_ZY_2.SetMode(AUTOMATIC);


    delay(10000); //Delay for ten seconds for final confirmation and countdown
}

void loop()
{
    sensors_event_t event; 
    ADXL345_sensor.getEvent(&event);
  
    AccZ = event.acceleration.z;
    AccY = event.acceleration.y;
    AccX = event.acceleration.x;

    bmp280.getMeasurements(temperature, pressure, altitude);

    cur_height = altitude;

    thrust_control_ascend_PID.Compute();
    thrust_control_descend_PID.Compute();
    stabilisation_ZX_1.Compute();
    stabilisation_ZX_2.Compute();
    stabilisation_ZY_1.Compute();
    stabilisation_ZY_2.Compute();

    thrust_control_ascend(cur_height);
}

void thrust_control_ascend(double input_height)
{
    thrust_control_ascend_PID.Compute();
    thrust = thrust*4.01;
    Serial.print(cur_height);
    Serial.print("\n");
    
    Serial.print(thrust);
    Serial.print("\n");
    delay(500);
    thrust = map(thrust, 0, 1023, 0, 180);
    Thruster.write(thrust);
}

void thrust_control_descent(double input_height)
{
    thrust = map(thrust, 0, 1023, 0, 180);
    Thruster.write(thrust);
}