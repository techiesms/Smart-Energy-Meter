/**
   This code is to print the values of

   - Current
   - Voltage
   &
   - Power

   on Serial Monitor
*/

#include <ZMPT101B.h> //https://github.com/Abdurraziq/ZMPT101B-arduino/tree/master

#define SENSITIVITY 553.0f // Voltage calibaration value
#define Voltage_Pin 34
#define Current_Pin 35

// ZMPT101B sensor output connected to analog pin A0
// and the voltage source frequency is 50 Hz.
ZMPT101B voltageSensor(Voltage_Pin, 50.0);

void setup() {
  Serial.begin(115200);
  analogSetPinAttenuation(Current_Pin, ADC_0db);
  // Change the sensitivity value based on value you got from the calibrate
  // example.
  voltageSensor.setSensitivity(SENSITIVITY);
}

void loop() {
  // read the voltage and then print via Serial.

  int a = 0;
  for (int j = 0; j < 1024; j++) {
    a += analogRead(35);
  }

  //Serial.println(a/1024);
  a = (a / 1024) - 1614;
  if (a < 2)
  {
    a = 0;
  }
  float voltage = voltageSensor.getRmsVoltage();
  Serial.print("Voltage : ");
  Serial.print(voltage);
  float AMPv = ((float(a) / 4095.0) * 43.0);

  Serial.print("V  Current : ");
  Serial.print(AMPv, 3 );
  Serial.print("I  Power : ");
  Serial.print(voltage * AMPv );
  Serial.println("W");
  delay(500);
}
