#include "Emakefun_MotorDriver.h"
Emakefun_MotorDriver mMotorDriver     = Emakefun_MotorDriver();
Emakefun_DCMotor *DCMotor_Right_Rear  = mMotorDriver.getMotor(1);
Emakefun_DCMotor *DCMotor_Left_Rear   = mMotorDriver.getMotor(2);
Emakefun_DCMotor *DCMotor_Right_Front = mMotorDriver.getMotor(3);
Emakefun_DCMotor *DCMotor_Left_Front  = mMotorDriver.getMotor(4);

#define TOP_SPEED 150

//控制电机运动    宏定义
/*
  #define MOTOR_GO_FORWARD  {digitalWrite(DIRA,HIGH);analogWrite(PWMA,150);digitalWrite(DIRB,HIGH);analogWrite(PWMB,150);\
  digitalWrite(DIRC,HIGH);analogWrite(PWMC,150);digitalWrite(DIRD,HIGH);analogWrite(PWMD,150);} //车体前进
*/
void MotorGoForward(int speed)
{
  DCMotor_Right_Front->setSpeed(speed);
  DCMotor_Right_Front->run(FORWARD);

  DCMotor_Right_Rear->setSpeed(speed);
  DCMotor_Right_Rear->run(FORWARD);

  DCMotor_Left_Front->setSpeed(speed);
  DCMotor_Left_Front->run(FORWARD);

  DCMotor_Left_Rear->setSpeed(speed);
  DCMotor_Left_Rear->run(FORWARD);
} //车体前进

/*
  #define MOTOR_GO_STOP   {digitalWrite(DIRA,LOW);analogWrite(PWMA,0);digitalWrite(DIRB,LOW);analogWrite(PWMB,0);\
  digitalWrite(DIRC,LOW);analogWrite(PWMC,0);digitalWrite(DIRD,LOW);analogWrite(PWMD,0);}       //车体静止
*/
void MotorGoStop()
{
  DCMotor_Right_Front->setSpeed(0);
  DCMotor_Right_Front->run(BRAKE);

  DCMotor_Right_Rear->setSpeed(0);
  DCMotor_Right_Rear->run(BRAKE);

  DCMotor_Left_Front->setSpeed(0);
  DCMotor_Left_Front->run(BRAKE);

  DCMotor_Left_Rear->setSpeed(0);
  DCMotor_Left_Rear->run(BRAKE);
} //车体静止


/*
  #define MOTOR_GO_BACK   {digitalWrite(DIRA,LOW);analogWrite(PWMA,150);digitalWrite(DIRB,LOW);analogWrite(PWMB,150);\
  digitalWrite(DIRC,LOW);analogWrite(PWMC,150);digitalWrite(DIRD,LOW);analogWrite(PWMD,150);}   //车体后退
*/
void MotorGoBackward(int speed)
{
  DCMotor_Right_Front->setSpeed(speed);
  DCMotor_Right_Front->run(BACKWARD);

  DCMotor_Right_Rear->setSpeed(speed);
  DCMotor_Right_Rear->run(BACKWARD);

  DCMotor_Left_Front->setSpeed(speed);
  DCMotor_Left_Front->run(BACKWARD);

  DCMotor_Left_Rear->setSpeed(speed);
  DCMotor_Left_Rear->run(BACKWARD);
} //车体后退

/*
  #define MOTOR_GO_LEFT_1   {digitalWrite(DIRA,HIGH);analogWrite(PWMA,150);digitalWrite(DIRD,HIGH);analogWrite(PWMB,150);}  //车体左前转
*/
void MotorGoLeftFront(int speed)
{
  DCMotor_Right_Front->setSpeed(speed); 
  DCMotor_Right_Front->run(FORWARD);

  DCMotor_Left_Rear->setSpeed(speed);
  DCMotor_Left_Rear->run(FORWARD);
}//车体左前转

/*
#define MOTOR_GO_LEFT_2   {digitalWrite(DIRA,HIGH);analogWrite(PWMA,150);digitalWrite(DIRB,LOW);analogWrite(PWMB,150);\
    digitalWrite(DIRC,LOW);analogWrite(PWMC,150);digitalWrite(DIRD,HIGH);analogWrite(PWMD,150);}  //车体左转
*/
void MotorGoLeftDrift(int speed)
{
  DCMotor_Right_Front->setSpeed(speed);
  DCMotor_Right_Front->run(FORWARD);

  DCMotor_Right_Rear->setSpeed(speed);
  DCMotor_Right_Rear->run(BACKWARD);

  DCMotor_Left_Front->setSpeed(speed);
  DCMotor_Left_Front->run(BACKWARD);

  DCMotor_Left_Rear->setSpeed(speed);
  DCMotor_Left_Rear->run(FORWARD);
} //车体左转平移


/*
#define MOTOR_GO_LEFT_3   {digitalWrite(DIRB,LOW);analogWrite(PWMB,150);digitalWrite(DIRC,LOW);analogWrite(PWMB,150);}  //车体左后转
*/
void MotorGoLeftBack(int speed)
{
  DCMotor_Left_Front->setSpeed(speed);
  DCMotor_Left_Front->run(BACKWARD);

  DCMotor_Right_Rear->setSpeed(speed);
  DCMotor_Right_Rear->run(BACKWARD);
}//车体左后转

/*
#define MOTOR_GO_RIGHT_1  {digitalWrite(DIRB,HIGH);analogWrite(PWMB,150);digitalWrite(DIRC,HIGH);analogWrite(PWMC,150);}  //车体右前转
*/
void MotorGoRightFront(int speed)
{
  DCMotor_Left_Front->setSpeed(speed); 
  DCMotor_Left_Front->run(FORWARD);

  DCMotor_Right_Rear->setSpeed(speed);
  DCMotor_Right_Rear->run(FORWARD);
}//车体右前转

/*
#define MOTOR_GO_RIGHT_2  {digitalWrite(DIRA,LOW);analogWrite(PWMA,150);digitalWrite(DIRB,HIGH);analogWrite(PWMB,150);\
    digitalWrite(DIRC,HIGH);analogWrite(PWMC,150);digitalWrite(DIRD,LOW);analogWrite(PWMD,150);}  //车体右转
*/  
void MotorGoRightDrift(int speed)
{
  DCMotor_Right_Front->setSpeed(speed);
  DCMotor_Right_Front->run(BACKWARD);

  DCMotor_Right_Rear->setSpeed(speed);
  DCMotor_Right_Rear->run(FORWARD);

  DCMotor_Left_Front->setSpeed(speed);
  DCMotor_Left_Front->run(FORWARD);

  DCMotor_Left_Rear->setSpeed(speed);
  DCMotor_Left_Rear->run(BACKWARD);
} //车体右转平移

/*
#define MOTOR_GO_RIGHT_3  {digitalWrite(DIRA,LOW);analogWrite(PWMB,150);digitalWrite(DIRD,LOW);analogWrite(PWMC,150);}  //车体右后转
*/
void MotorGoRightBack(int speed)
{
  DCMotor_Right_Front->setSpeed(speed);
  DCMotor_Right_Front->run(BACKWARD);

  DCMotor_Left_Rear->setSpeed(speed);
  DCMotor_Left_Rear->run(BACKWARD);
}//车体右后转


//车体原地右转
void MotorRotateRight(int speed)
{
  DCMotor_Right_Front->setSpeed(speed);
  DCMotor_Right_Front->run(BACKWARD);

  DCMotor_Right_Rear->setSpeed(speed);
  DCMotor_Right_Rear->run(BACKWARD);

  DCMotor_Left_Front->setSpeed(speed);
  DCMotor_Left_Front->run(FORWARD);

  DCMotor_Left_Rear->setSpeed(speed);
  DCMotor_Left_Rear->run(FORWARD);
}//车体原地右转

//车体原地左转
void MotorRotateLeft(int speed)
{
  DCMotor_Right_Front->setSpeed(speed);
  DCMotor_Right_Front->run(FORWARD);

  DCMotor_Right_Rear->setSpeed(speed);
  DCMotor_Right_Rear->run(FORWARD);

  DCMotor_Left_Front->setSpeed(speed);
  DCMotor_Left_Front->run(BACKWARD);

  DCMotor_Left_Rear->setSpeed(speed);
  DCMotor_Left_Rear->run(BACKWARD);
}//车体原地左转


void setup()
{
  Serial.begin(9600);
  mMotorDriver.begin(50);
}

void loop()
{
 MotorGoForward(60);
  delay(2000);
  MotorGoStop();
  delay(2000);

  MotorGoBackward(60);
  delay(2000);
  MotorGoStop();
  delay(2000);

  MotorGoLeftFront(60);
  delay(2000);
  MotorGoStop();
  delay(2000);

  MotorGoLeftDrift(60);
  delay(2000);
  MotorGoStop();
  delay(2000);

  MotorGoLeftBack(60);
  delay(2000);
  MotorGoStop();
  delay(2000);

  MotorGoRightFront(60);
  delay(2000);
  MotorGoStop();
  delay(2000);

  MotorGoRightDrift(60);
  delay(2000);
  MotorGoStop();
  delay(2000);

  MotorGoRightBack(60);
  delay(2000);
  MotorGoStop();
  delay(2000);

  MotorRotateRight(60);
  delay(2000);
  MotorGoStop();
  delay(2000);

  MotorRotateLeft(60);
  delay(2000);
  MotorGoStop();
  delay(2000);

}
