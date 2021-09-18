#include <Wire.h>

#define IMU_ADDRESS 0x68
#define FULL_SCALE_RANGE 16*9.81 // full scale range for acceleration

// remark: true_value = (value-offset) * full_scale_range / int16_max

int32_t x_accel_offset = 0, y_accel_offset = 0, z_accel_offset = 0;
int32_t x_gyro_offset = 0, y_gyro_offset = 0, z_gyro_offset = 0; 

int16_t x_accel, y_accel, z_accel;
int16_t x_gyro, y_gyro, z_gyro;
int16_t temp;

long pitch = 0L;
long roll = 0L;
long accelX, accelY, accelZ; // true values

//we don't need gyro values in this task
//however, i put them in to have a code preset for IMU interfacing and sensor-reading

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    setImuRegister(0x6B, 0x00);
    setImuRegister(0x1C, 0x18); // this way: full_scale_range is 16 * 9.81
    setImuRegister(0x1B, 0x18); // unneeded, gyroscope register setting
    calibrateImu(5000);   
}

void loop() {
  readImuAll();
  accelX = (x_accel - x_accel_offset)* FULL_SCALE_RANGE / 32767; 
  accelY = (y_accel - y_accel_offset)* FULL_SCALE_RANGE / 32767;
  accelZ = (z_accel - z_accel_offset)* FULL_SCALE_RANGE / 32767; 
   
  pitch = 180 * atan2(accelX, sqrt(accelY*accelY + accelZ*accelZ))/PI;
  roll = 180 * atan2(accelY, sqrt(accelX*accelX + accelZ*accelZ))/PI;
  
  if(pitch > 60 || roll > 60)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);            
  }

}
// interfacing 
void setImuRegister(uint8_t reg, uint8_t val)
{
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}
//unneeded
/* 
uint8_t readImu1Byte(uint8_t reg)
{
  uint8_t data = 0;
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(IMU_ADDRESS, 1);
  while(Wire.available() <1);
  data = Wire.read();
  return data;
}
*/ 
uint16_t readImu2Bytes(uint8_t reg)
{
  uint16_t data = 0;
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(IMU_ADDRESS, 2);
  while(Wire.available() < 2);
  data = Wire.read() << 8 | Wire.read();
  return data;
}

void calibrateImu(uint32_t n_iterations)
{
  for(uint32_t i = 0; i < n_iterations; i++)
  {
    x_accel_offset += readImu2Bytes(0x3B);
    y_accel_offset += readImu2Bytes(0x3D);
    z_accel_offset += readImu2Bytes(0x3F);

    x_gyro_offset += readImu2Bytes(0x43);
    y_gyro_offset += readImu2Bytes(0x45);
    z_gyro_offset += readImu2Bytes(0x47);
  } 
  x_accel_offset /= n_iterations;
  y_accel_offset /= n_iterations;
  z_accel_offset /= n_iterations;

  x_gyro_offset /= n_iterations;
  y_gyro_offset /= n_iterations;
  z_gyro_offset /= n_iterations;
}

void readImuAll()
{
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(IMU_ADDRESS, 14);
  while(Wire.available() < 14);
  x_accel = Wire.read() << 8 | Wire.read();
  y_accel = Wire.read() << 8 | Wire.read();
  z_accel = Wire.read() << 8 | Wire.read();
  x_gyro = Wire.read() << 8 | Wire.read();
  y_gyro = Wire.read() << 8 | Wire.read();
  z_gyro = Wire.read() << 8 | Wire.read();
  temp = Wire.read() << 8 | Wire.read();
}
