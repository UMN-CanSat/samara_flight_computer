// LSM6DS3 Functions

void initLSM6DS3() {
  ds3.begin();

  Serial.println("Initialized LSM6DS3...");
  
}

void updateLSM6DS3() {
  // pull accelerometer values (milliG)
  ds3Data.accX = ds3.readFloatAccelX()*1000;
  ds3Data.accY = ds3.readFloatAccelY()*1000;
  ds3Data.accZ = ds3.readFloatAccelZ()*1000;

  // pull gyroscope values (deg/sec)
  ds3Data.gyrX = ds3.readFloatGyroX();
  ds3Data.gyrY = ds3.readFloatGyroY();
  ds3Data.gyrZ = ds3.readFloatGyroZ();
  
}
