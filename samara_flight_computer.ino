// Flight computer for both of the samara payloads

// Libraries
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_DPS310.h>
#include "SparkFunLSM6DS3.h"
#include <RelayXBee.h>
//#include <XBee.h>


// Payload Definitions -- COMMENT OUT AT LEAST ONE OPTION
#define SP1
//#define SP2

// Pin Definitions
#define XBEE_SERIAL Serial1
#define THERMISTOR A0

// Constants
#define ADC_MAX 8191.0                        // Maximum ADC value given to the thermistor, should be 8192 for a Teensy 4.0
#define CONST_A 0.001125308852122             // A, B, and C are constants used for a 10k resistor and 10k thermistor for the steinhart-hart equation
#define CONST_B 0.000234711863267             // NOTE: These values change when the thermistor and/or resistor change value, so if that happens, more research needs to be done on those constants
#define CONST_C 0.000000085663516                                       
#define CONST_R 10000                         // 10k Ω resistor 
#define C2K 273.15                            // Celsius to Kelvin conversion

// Timer Definitions
#define LOOPTIME 500
float timer = 0;

// Xbee Definitions
XBee xBee = XBee(&XBEE_SERIAL);               // Xbee object with serial reference
String networkID = "2806";
String destinationCmdID = "ATDL0";
// Science payload definitions
#ifdef SP1
String myCmdID = "ATMY1";
String ID = "SP1";
#endif  // SP1
#ifdef SP2
String myCmdID = "ATMY2";
String ID = "SP2";
#endif  // SP2

// Adafruit DPS310 Pressure Sensor Variables
Adafruit_DPS310 dps;
float dpsTemp;
float dpsPressure;

// IMU data struct
struct imu_data
{
float accX;
float accY;
float accZ;
float gyrX;
float gyrY;
float gyrZ;
};
typedef struct imu_data imu_data;

// LSM6DS3 variables
LSM6DS3 ds3;  // I2C address is 0x6B
imu_data ds3Data;

// Thermistor variables
float thermTemp;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  analogReadResolution(13);
  initDPS310();
  initLSM6DS3();

  String data_header = "millis,pressure,accX,accY,accZ,gyorX,gyroY,gyroZ,temp";
  Serial.println(data_header);
}

void loop() {
  
  if (millis() - timer > LOOPTIME) {

    timer = millis();
    
    updateDPS310();

    updateLSM6DS3();

    updateThermistor();
    
    Serial.println(buildDataString());

  }

}

String buildDataString(void) {
  String data_string;
//  data_string = String(millis()) + ", " + String(dpsPressure) + ", " + String(ds3_accX) + ", " + String(ds3_accY) + ", ";
//  data_string += String(ds3_accZ) + ", " + String(ds3_gyroX) + ", " + String(ds3_gyroY) + ", " + String(ds3_gyroZ) + ", " + String(thermTemp);
  
  return data_string;
}
