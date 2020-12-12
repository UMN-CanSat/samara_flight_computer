// Thermistor functions

void updateThermistor() {
  int analog_thermistor = analogRead(THERMISTOR);

  thermTemp = thermAnalogCalc(analog_thermistor);
}

// Thermistor analog calculations
float thermAnalogCalc(int analog) {
  float t = log((float(ADC_MAX/analog) - 1)*CONST_R);
  t = CONST_A + CONST_B*t + CONST_C*t*t*t;        // A + B*t + C*(t^3)
  t = 1/t - C2K;

  return t;                                       // returns temperature in Celsius
}
