//Receiver program
#include <SPI.h>
#include "nRF24L01.h"

#define EM_MOTOR_SHIELD_BOARD_VERSION 3

#if (EM_MOTOR_SHIELD_BOARD_VERSION > 2)
    #define NRF24L01_CE 10
    #define NRF24L01_CSN 8
#else
    #define NRF24L01_CE 10
    #define NRF24L01_CSN 9
#endif

Nrf24l Mirf = Nrf24l(NRF24L01_CE, NRF24L01_CSN);
String SmartCarName = "MotorDrive";
int value;
int nChannel = 0;
void setup()
{
 #if 0
    Serial.begin(9600);
    Mirf.spi = &MirfHardwareSpi;
    Mirf.init();
    Mirf.setRADDR((byte *)"MotorDrive"); //Set your own address (receiver address) 
    Mirf.payload = sizeof(value);
    Mirf.channel = 90;             //Set the used channel
    Mirf.config();
    Serial.println("Listening...");  //Start listening to received data
#endif
}

void setup_channel(int nChannel)
{
    Serial.begin(9600);
    Mirf.spi = &MirfHardwareSpi;
    Mirf.init();
    Mirf.setRADDR((byte *)"MotorDrive"); //Set your own address (receiver address) 
    Mirf.payload = sizeof(value);
    Mirf.channel = nChannel;             //Set the used channel
    Mirf.config();
    Serial.print("Set Channel ");
    Serial.print(nChannel, DEC);
    Serial.println();
    Serial.println("Listening...");  //Start listening to received data
}


void loop()
{
  
  setup_channel(nChannel);
  nChannel ++;

  unsigned long time = millis();
  while ( (millis()- time) < 1000)
  {
    if (Mirf.dataReady()) { //When the program is received, the received data is output from the serial port
      Mirf.getData((byte *) &value);
      Serial.print("Got data: ");
      Serial.println(value);
      exit(0);
    }
  }
  if (nChannel == 127)
  {
    Serial.println("end searching..");
    delay(500);
    exit(0);
  }
}
