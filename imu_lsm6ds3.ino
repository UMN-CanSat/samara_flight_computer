// LSM6DS3 Functions

void initLSM6DS3() {
  lsm6ds3.begin();

  Serial.println("Initialized LSM6DS3...");
  
}

void updateLSM6DS3() {
  // pull accelerometer values (milliG)
  ds3_accX = lsm6ds3.readFloatAccelX()*1000;
  ds3_accY = lsm6ds3.readFloatAccelY()*1000;
  ds3_accZ = lsm6ds3.readFloatAccelZ()*1000;

  // pull gyroscope values (deg/sec)
  ds3_gyroX = lsm6ds3.readFloatGyroX();
  ds3_gyroY = lsm6ds3.readFloatGyroY();
  ds3_gyroZ = lsm6ds3.readFloatGyroZ();
  
}
