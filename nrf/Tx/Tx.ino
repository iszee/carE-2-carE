#include <MirfHardwareSpiDriver.h>
#include <MirfSpiDriver.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <SPI.h>
#include <Wire.h>

//0 = stop, 1 = left, 2 = right, 3 = forward, 4 = backwards
long command;
long last_command;


void setup() {
  // put your setup code here, to run once:
  Mirf.spi = &MirfHardwareSpi;  
  Mirf.init(); 
  Mirf.setTADDR((byte *)"serv1");
  Mirf.payload = sizeof(long);
  Mirf.config(); 
  dataS(2);
  Serial.begin(115200);
}

void loop() {



  }

void dataS(long cmd){
    command=cmd;
    delay(500);
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
