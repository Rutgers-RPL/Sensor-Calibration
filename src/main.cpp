#include <Arduino.h>
#include <BMI085.h>
#include <DFRobot_BMM150.h>

Bmi085Accel accel(Wire, 0x18);

DFRobot_BMM150_I2C mag(&Wire, I2C_ADDRESS_4);
#define _g_ 9.806

// MAG or ACCEL

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  //while (!Serial) {};

  while (mag.begin()) {
    Serial.printf("BMM150 Init Failed, Trying again\n");
    delay(500);
  } //Serial.printf("BMM150 Init Success!\n");
  mag.setOperationMode(BMM150_POWERMODE_NORMAL);
  mag.setPresetMode(BMM150_PRESETMODE_HIGHACCURACY);
  mag.setRate(BMM150_DATA_RATE_10HZ);
  mag.setMeasurementXYZ();


  while (accel.begin() < 0) {
    Serial.printf("BMI085 Init Failed, Trying again\n");
    delay(500);
  } //Serial.printf("BMI085 Init Success!");

}
/*
void loop()
{
  sBmm150MagData_t magData = mag.getGeomagneticData();
  Serial.print("mag x = "); Serial.print(magData.x); Serial.println(" uT");
  Serial.print("mag y = "); Serial.print(magData.y); Serial.println(" uT");
  Serial.print("mag z = "); Serial.print(magData.z); Serial.println(" uT");
  float compassDegree = mag.getCompassDegree();
  Serial.print("the angle between the pointing direction and north (counterclockwise) is:");
  Serial.println(compassDegree);
  Serial.println("--------------------------------");
  delay(100);
}
*/

void loop() {
  // put your main code here, to run repeatedly:
  accel.readSensor();
  sBmm150MagData_t magData = mag.getGeomagneticData();

  if (true) {
    Serial.printf("%f,%f,%f\n", accel.getAccelX_mss()/_g_,accel.getAccelY_mss()/_g_,accel.getAccelZ_mss()/_g_);
  } else {
    //Serial.print(magData.x); Serial.print(",");
    //Serial.print(magData.y); Serial.print(",");
    //Serial.println(magData.z);
  }
  
  // 100HZ
  delay(10);
}
