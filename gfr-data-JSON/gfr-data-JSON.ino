// SNZ-01 Smart Sole example code with basic MPU6050 IMU
//
// exposing the 8 grf points and MPU6050 IMU as a JSON Object
//
// 16 June 2023, Turin, Davide Gomba

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;


#include <Arduino_JSON.h>


// Potentiometer is connected to GPIO 34 (Analog ADC1_CH6)
const int grf8 = 39;
const int grf7 = 36;
const int grf6 = 33;
const int grf5 = 25;
const int grf4 = 26;
const int grf3 = 34;
const int grf2 = 35;
const int grf1 = 32;

// variable for storing the potentiometer value
int gfrValue8 = 0;
int gfrValue7 = 0;
int gfrValue6 = 0;
int gfrValue5 = 0;
int gfrValue4 = 0;
int gfrValue3 = 0;
int gfrValue2 = 0;
int gfrValue1 = 0;


void setup() {
  Serial.begin(115200);
  delay(1000);

  // MPU SETUP

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
    case MPU6050_RANGE_2_G:
      Serial.println("+-2G");
      break;
    case MPU6050_RANGE_4_G:
      Serial.println("+-4G");
      break;
    case MPU6050_RANGE_8_G:
      Serial.println("+-8G");
      break;
    case MPU6050_RANGE_16_G:
      Serial.println("+-16G");
      break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG:
      Serial.println("+- 250 deg/s");
      break;
    case MPU6050_RANGE_500_DEG:
      Serial.println("+- 500 deg/s");
      break;
    case MPU6050_RANGE_1000_DEG:
      Serial.println("+- 1000 deg/s");
      break;
    case MPU6050_RANGE_2000_DEG:
      Serial.println("+- 2000 deg/s");
      break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ:
      Serial.println("260 Hz");
      break;
    case MPU6050_BAND_184_HZ:
      Serial.println("184 Hz");
      break;
    case MPU6050_BAND_94_HZ:
      Serial.println("94 Hz");
      break;
    case MPU6050_BAND_44_HZ:
      Serial.println("44 Hz");
      break;
    case MPU6050_BAND_21_HZ:
      Serial.println("21 Hz");
      break;
    case MPU6050_BAND_10_HZ:
      Serial.println("10 Hz");
      break;
    case MPU6050_BAND_5_HZ:
      Serial.println("5 Hz");
      break;
  }
}

void loop() {

  JSONVar myObject;

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  myObject["accX"] = a.acceleration.x;
  myObject["accY"] = a.acceleration.y;
  myObject["accZ"] = a.acceleration.z;

  myObject["gyrX"] = g.gyro.x;
  myObject["gyrY"] = g.gyro.y;
  myObject["gyrZ"] = g.gyro.z;

  myObject["temp"] = temp.temperature;

  // Reading potentiometer value
  gfrValue8 = analogRead(grf8);
  gfrValue7 = analogRead(grf7);
  gfrValue6 = analogRead(grf6);
  gfrValue5 = analogRead(grf5);
  gfrValue4 = analogRead(grf4);
  gfrValue3 = analogRead(grf3);
  gfrValue2 = analogRead(grf2);
  gfrValue1 = analogRead(grf1);



  /*
  Serial.print(gfrValue8);
  Serial.print(",");
  Serial.print(gfrValue7);
  Serial.print(",");
  Serial.print(gfrValue6);
  Serial.print(",");
  Serial.print(gfrValue5);
  Serial.print(",");
  Serial.print(gfrValue4);
  Serial.print(",");
  Serial.print(gfrValue3);
  Serial.print(",");
  Serial.print(gfrValue2);
  Serial.print(",");
  Serial.print(gfrValue1);
  Serial.print(",");
  Serial.println();
*/


  myObject["gfrValue8"] = gfrValue8;
  myObject["gfrValue7"] = gfrValue7;
  myObject["gfrValue6"] = gfrValue6;
  myObject["gfrValue5"] = gfrValue5;
  myObject["gfrValue4"] = gfrValue4;
  myObject["gfrValue3"] = gfrValue3;
  myObject["gfrValue2"] = gfrValue2;
  myObject["gfrValue1"] = gfrValue1;


  // JSON.stringify(myVar) can be used to convert the JSONVar to a String
  String jsonString = JSON.stringify(myObject);

  Serial.println(jsonString);

  //  Serial.println();

  delay(20);
}