// Adafruit DPS310 Pressure Sensor functions

void initDPS310() {
  if (! dps.begin_I2C()) {             // Can pass in I2C address here
    Serial.println("Failed to find DPS");
    while (1) yield();
  }
  Serial.println("DPS connected...");

  dps.configurePressure(DPS310_64HZ, DPS310_64SAMPLES);
  dps.configureTemperature(DPS310_64HZ, DPS310_64SAMPLES);
}

void updateDPS310() {
  sensors_event_t temp_event, pressure_event;
  
  while (!dps.temperatureAvailable() || !dps.pressureAvailable()) {
    return; // wait until there's something to read
  }
 
  dps.getEvents(&temp_event, &pressure_event);
  dpsTemp = temp_event.temperature;
  dpsPressure = pressure_event.pressure*100;
}
