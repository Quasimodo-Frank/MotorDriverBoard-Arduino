#include "Emakefun_MotorDriver.h"
Emakefun_MotorDriver mMotorDriver = Emakefun_MotorDriver();
Emakefun_DCMotor *DCMotor_1 = mMotorDriver.getMotor(1);
Emakefun_DCMotor *DCMotor_2 = mMotorDriver.getMotor(2);
Emakefun_DCMotor *DCMotor_3 = mMotorDriver.getMotor(3);
Emakefun_DCMotor *DCMotor_4 = mMotorDriver.getMotor(4);

void setup()
{
    Serial.begin(9600);
    mMotorDriver.begin(50);
}

void loop()
{
  DCMotor_1->setSpeed(0);
  DCMotor_1->run(3);
  DCMotor_2->setSpeed(0);
  DCMotor_2->run(3);
  DCMotor_3->setSpeed(0);
  DCMotor_3->run(3);
  DCMotor_4->setSpeed(0);
  DCMotor_4->run(3);  
  delay(4000);
}
