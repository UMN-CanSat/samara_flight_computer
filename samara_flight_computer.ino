// Flight computer for both of the samara payloads

// Libraries
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_DPS310.h>
#include "SparkFunLSM6DS3.h"

// Pin Definitions
#define THERMISTOR A0

// Constants
#define ADC_MAX 8191.0                        // Maximum ADC value given to the thermistor, should be 8192 for a Teensy 4.0
#define CONST_A 0.001125308852122             // A, B, and C are constants used for a 10k resistor and 10k thermistor for the steinhart-hart equation
#define CONST_B 0.000234711863267             // NOTE: These values change when the thermistor and/or resistor change value, so if that happens, more research needs to be done on those constants
#define CONST_C 0.000000085663516                                       
#define CONST_R 10000                         // 10k Ω resistor 
#define C2K 273.15                            // Celisus to Kelvin conversion


// Time Definitions
#define LOOPTIME 250
float timer = 0;

// Adafruit DPS310 Pressure Sensor Variables
Adafruit_DPS310 dps;
float dpsTemp;
float dpsPressure;

// LSM6DS3 variables
LSM6DS3 lsm6ds3;  // I2C address is 0x6B
float ds3_accX;
float ds3_accY;
float ds3_accZ;
float ds3_gyroX;
float ds3_gyroY;
float ds3_gyroZ;

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

  updateDPS310();

  updateLSM6DS3();

  updateThermistor();
  
  if (millis() - timer > LOOPTIME) {
    Serial.println(buildDataString());

    timer = millis();
  }

}

String buildDataString(void) {
  String data_string;
  data_string = String(millis()) + ", " + String(dpsPressure) + ", " + String(ds3_accX) + ", " + String(ds3_accY) + ", ";
  data_string += String(ds3_accZ) + ", " + String(ds3_gyroX) + ", " + String(ds3_gyroY) + ", " + String(ds3_gyroZ) + ", " + String(thermTemp);
  
  return data_string;
}
