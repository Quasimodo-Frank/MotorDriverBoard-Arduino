#include "Emakefun_MotorDriver.h"

Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver();
Emakefun_Sensor *rgb = NULL;



void setup()
{
    Serial.begin(9600);
    delay(1000);

    //rgb = mMotorDriver.getSensor(E_RGB);
    delay(1000);
}

void loop()
{

while(1){
  Serial.println("hello world");
  delay (1000);
}
  #if 0
  rgb->SetRgbColor(E_RGB_ALL,RGB_WHITE);
  delay(1000);
  rgb->SetRgbColor(E_RGB_ALL,RGB_BLUE);
  delay(1000);
  rgb->SetRgbColor(E_RGB_ALL,RGB_RED);
  delay(1000);
  rgb->SetRgbColor(E_RGB_ALL,RGB_YELLOW);
  delay(1000);
  #endif
}
