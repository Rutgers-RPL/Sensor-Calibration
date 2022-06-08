#include <Arduino.h>
#include <BMI085.h>
#include <DFRobot_BMM150.h>

Bmi085Accel accel(Wire, 0x18);

DFRobot_BMM150_I2C mag(Wire, 0x13);

// MAG or ACCEL
#define log = "MAG"
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  while (!Serial) {};

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

void loop() {
  // put your main code here, to run repeatedly:
  accel.readSensor();
  sBmm150MagData_t magData = mag.getGeomagneticData();

  if (log == "ACCEL") {
    Serial.print(accel.getAccelX_mss, 6); Serial.print(",");
    Serial.print(accel.getAccelY_mss, 6); Serial.print(",");
    Serial.println(accel.getAccelZ_mss, 6);
  } else if (log == "MAG") {
    Serial.print(magData.x, 6); Serial.print(",");
    Serial.print(masgData.y, 6); Serial.print(",");
    Serial.println(magData.z, 6);
  }
  
  // 10HZ
  delay(100);
}