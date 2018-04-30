#include <MirfHardwareSpiDriver.h>
#include <MirfSpiDriver.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <SPI.h>
#include <Wire.h>

//0 = stop, 1 = left, 2 = right, 3 = forward, 4 = backwards
long command;
long last_command;
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

void setup() {
  // put your setup code here, to run once:
  Mirf.spi = &MirfHardwareSpi;  
  Mirf.init(); 
  Mirf.setTADDR((byte *)"serv1");
  Mirf.payload = sizeof(long);
  Mirf.config(); 
  dataS(2);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(115200);
}

void loop() {
Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  Serial.print("AcX = "); Serial.print(AcX/2048);
  Serial.print(" | AcY = "); Serial.println(AcY/2048);
  //Serial.print(" | AcZ = "); Serial.print(AcZ/2048);
  AcX=AcX/2048;
  //dataS(4);
  
  
  if (abs(AcX)>=15){
    dataS(4);
    }
  else if (abs(AcX)>=10){
    dataS(3);
    }
    

delay(100);
  }

void dataS(long cmd){
    command=cmd;
    delay(100);
    Mirf.send((byte *)&command);
    while(Mirf.isSending()){
    }
  }





  
void dataSend(){
  
  for(int i=1;i<=5;i++){
    command =i;
    delay(500);
    Mirf.send((byte *)&command);
    
    while(Mirf.isSending()){
    }
    
  }
  Serial.println("data packet sent");
  delay(1000);

  
  }
