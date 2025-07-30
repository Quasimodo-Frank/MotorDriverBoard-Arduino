#include <LiquidCrystal.h>

#include "PS2X_lib.h"  //for v1.6

/******************************************************************
   set pins connected to PS2 controller:
     - 1e column: original
     - 2e colmun: Stef?
   replace pin numbers by the ones you use
 ******************************************************************/
#define EM_MOTOR_SHIELD_BOARD_VERSION 3

#if (EM_MOTOR_SHIELD_BOARD_VERSION > 2)
#define PS2_DAT     12
#define PS2_CMD     11
#define PS2_SEL     10
#define PS2_CLK     13
#else
#define PS2_DAT     A0
#define PS2_CMD     A1
#define PS2_SEL     A2
#define PS2_CLK     A4
#endif

PS2X ps2x; // create PS2 Controller Class

/******************************************************************/
// Motor Driver
int error = 0;
bool power_on = true;
int top_speed = 100;


int8_t length;
#define Do 262
#define Re 294
#define Mi 330
#define Fa 349
#define Sol 392
#define La 440
#define Si 494
#define Do_h 523
#define Re_h 587
#define Mi_h 659
#define Fa_h 698
#define Sol_h 784
#define La_h 880
#define Si_h 988
// happy birthday Music score
int scale[] = {Sol, Sol, La, Sol, Do_h, Si, Sol, Sol,
               La, Sol, Re_h, Do_h, Sol, Sol, Sol_h, Mi_h,
               Do_h, Si, La, Fa_h, Fa_h, Mi_h, Do_h, Re_h, Do_h
              };

// Beats time
float durt[] =
{
  0.5, 0.5, 1, 1, 1, 1 + 1, 0.5, 0.5,
  1, 1, 1, 1 + 1, 0.5, 0.5, 1, 1,
  1, 1, 1, 0.5, 0.5, 1, 1, 1, 1 + 1
};



#include "Emakefun_MotorDriver.h"
#include "Buzzer.h"

Emakefun_MotorDriver mMotorDriver     = Emakefun_MotorDriver();
Emakefun_DCMotor *DCMotor_Right_Rear  = mMotorDriver.getMotor(1);
Emakefun_DCMotor *DCMotor_Left_Rear   = mMotorDriver.getMotor(2);
Emakefun_DCMotor *DCMotor_Right_Front = mMotorDriver.getMotor(3);
Emakefun_DCMotor *DCMotor_Left_Front  = mMotorDriver.getMotor(4);

Emakefun_Sensor  *rgb    = mMotorDriver.getSensor(E_RGB);
Buzzer  buzzer = Buzzer(9);


#include "ultrasonic.h"

//控制电机运动
/*
  #define MOTOR_GO_FORWARD  {digitalWrite(DIRA,HIGH);analogWrite(PWMA,150);digitalWrite(DIRB,HIGH);analogWrite(PWMB,150);\
  digitalWrite(DIRC,HIGH);analogWrite(PWMC,150);digitalWrite(DIRD,HIGH);analogWrite(PWMD,150);} //车体前进
*/
//车体前进
void MotorGoForward(uint8_t speed)
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
  digitalWrite(DIRC,LOW);analogWrite(PWMC,0);digitalWrite(DIRD,LOW);analogWrite(PWMD,0);} //车体静止
*/
//车体静止
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
  digitalWrite(DIRC,LOW);analogWrite(PWMC,150);digitalWrite(DIRD,LOW);analogWrite(PWMD,150);} //车体后退
*/
//车体后退
void MotorGoBackward(uint8_t speed)
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
  #define MOTOR_GO_LEFT_1   {digitalWrite(DIRA,HIGH);analogWrite(PWMA,150);digitalWrite(DIRD,HIGH);analogWrite(PWMB,150);} //车体左前转
*/
//车体左前转
void MotorGoLeftFront(uint8_t speed)
{
  DCMotor_Right_Front->setSpeed(speed);
  DCMotor_Right_Front->run(FORWARD);

  DCMotor_Left_Rear->setSpeed(speed);
  DCMotor_Left_Rear->run(FORWARD);
}//车体左前转

/*
  #define MOTOR_GO_LEFT_2   {digitalWrite(DIRA,HIGH);analogWrite(PWMA,150);digitalWrite(DIRB,LOW);analogWrite(PWMB,150);\
    digitalWrite(DIRC,LOW);analogWrite(PWMC,150);digitalWrite(DIRD,HIGH);analogWrite(PWMD,150);} //车体左转
*/
//车体左转
void MotorGoLeftDrift(uint8_t speed)
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
  #define MOTOR_GO_LEFT_3   {digitalWrite(DIRB,LOW);analogWrite(PWMB,150);digitalWrite(DIRC,LOW);analogWrite(PWMB,150);} //车体左后转
*/
//车体左转
void MotorGoLeftBack(uint8_t speed)
{
  DCMotor_Left_Front->setSpeed(speed);
  DCMotor_Left_Front->run(BACKWARD);

  DCMotor_Right_Rear->setSpeed(speed);
  DCMotor_Right_Rear->run(BACKWARD);
}//车体左后转

/*
  #define MOTOR_GO_RIGHT_1  {digitalWrite(DIRB,HIGH);analogWrite(PWMB,150);digitalWrite(DIRC,HIGH);analogWrite(PWMC,150);} //车体右前转
*/
//车体右前转
void MotorGoRightFront(uint8_t speed)
{
  DCMotor_Left_Front->setSpeed(speed);
  DCMotor_Left_Front->run(FORWARD);

  DCMotor_Right_Rear->setSpeed(speed);
  DCMotor_Right_Rear->run(FORWARD);
}//车体右前转

/*
  #define MOTOR_GO_RIGHT_2  {digitalWrite(DIRA,LOW);analogWrite(PWMA,150);digitalWrite(DIRB,HIGH);analogWrite(PWMB,150);\
    digitalWrite(DIRC,HIGH);analogWrite(PWMC,150);digitalWrite(DIRD,LOW);analogWrite(PWMD,150);} //车体右转
*/
//车体右转
void MotorGoRightDrift(uint8_t speed)
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
  #define MOTOR_GO_RIGHT_3  {digitalWrite(DIRA,LOW);analogWrite(PWMB,150);digitalWrite(DIRD,LOW);analogWrite(PWMC,150);} //车体右后转
*/
//车体右后转
void MotorGoRightBack(uint8_t speed)
{
  DCMotor_Right_Front->setSpeed(speed);
  DCMotor_Right_Front->run(BACKWARD);

  DCMotor_Left_Rear->setSpeed(speed);
  DCMotor_Left_Rear->run(BACKWARD);
}//车体右后转


//车体原地右转
void MotorRotateRight(uint8_t speed)
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
void MotorRotateLeft(uint8_t speed)
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


// Reset func
void (* resetFunc) (void) = 0;

void autonomousDrive()
{
  float distance = getDistance();
  static float speed = top_speed/2;
  static int invalid_count = 0;

  if (distance >= 100){
    speed = top_speed;
    MotorGoForward(speed);
  }
  else if ((distance < 100) && (distance >= 30)){
    if (speed>= top_speed/2)
        MotorGoForward(speed);
    else
       speed = top_speed/2;
       
    speed -= 2;
    
  }
  else if ((distance < 30) && (distance >= 0)){
    MotorRotateLeft(top_speed);
  }
  else{
    if (invalid_count < 5){
        invalid_count++;
        if (speed>= top_speed/2)
        MotorGoForward(speed);
    }
    else{
        invalid_count = 0;
        MotorGoBackward(top_speed);
    }
  }

  Serial.print("speed is :");
  Serial.print(speed);
  Serial.println();
  
  delay(150);
}

void setup() {

  Serial.begin(9600);

  // set up motor controller
  mMotorDriver.begin(50);

  delay(500);  //added delay to give wireless ps2 module some time to startup, before configuring it

  //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, false, false);
  if (error == 0)
    Serial.println("Found Controller, configured successful ");
  else
    Serial.println("Error Setting Up Controller.");

  rgb = mMotorDriver.getSensor(E_RGB);
  rgb->SetRgbColor(E_RGB_ALL, RGB_RED);
  
  length = sizeof(scale) / sizeof(scale[0]);

  setupUltrasonic();
}

void loop() {
  /* You must Read Gamepad to get new values and set vibration values
     ps2x.read_gamepad(small motor on/off, larger motor strenght from 0-255)
     if you don't enable the rumble, use ps2x.read_gamepad(); with no values
     You should call this at least once a second
  */
  if (error == 1) { //skip loop if no controller found
    resetFunc();
  }

  ps2x.read_gamepad(); //read controller and set large motor to spin at 'vibrate' speed
  MotorGoStop();

  // use the start button to control the motor as a power button
  if (ps2x.ButtonReleased(PSB_START)) {       //will be TRUE as long as button is pressed
    if (power_on == true) {
      power_on = false;
      Serial.println("Power Motor Off");
      rgb->SetRgbColor(E_RGB_RIGHT, RGB_BLACK);
    }
    else {
      power_on = true;
      Serial.println("Power Motor On");
      rgb->SetRgbColor(E_RGB_RIGHT, RGB_RED);
    }
  }

  // if power off, then turn off the Motor, and do nothing else
  if (power_on == false)
  {
    //MotorGoStop();
    //delay(50);

    autonomousDrive();
    return;
  }

  // otherwise (power_on), then check the buttons
  //if (ps2x.Button(PSB_SELECT))
  //  Serial.println("Select is being held");

  if (ps2x.Button(PSB_PAD_UP) &&
      !ps2x.Button(PSB_PAD_DOWN) &&
      !ps2x.Button(PSB_PAD_LEFT) &&
      !ps2x.Button(PSB_PAD_RIGHT))
  {
    Serial.println(" MOTOR GO FORWARD");
    MotorGoForward(top_speed);
  }

  if (!ps2x.Button(PSB_PAD_UP) &&
      ps2x.Button(PSB_PAD_DOWN) &&
      !ps2x.Button(PSB_PAD_LEFT) &&
      !ps2x.Button(PSB_PAD_RIGHT))
  {
    Serial.println(" MOTOR GO BACKWARD");
    MotorGoBackward(top_speed);
  }

  if (!ps2x.Button(PSB_PAD_UP) &&
      !ps2x.Button(PSB_PAD_DOWN) &&
      ps2x.Button(PSB_PAD_LEFT) &&
      !ps2x.Button(PSB_PAD_RIGHT))
  {
    Serial.println(" MOTOR GO LEFT DRIFT");
    MotorGoLeftDrift(top_speed);
  }

  if (!ps2x.Button(PSB_PAD_UP) &&
      !ps2x.Button(PSB_PAD_DOWN) &&
      !ps2x.Button(PSB_PAD_LEFT) &&
      ps2x.Button(PSB_PAD_RIGHT))
  {
    Serial.println(" MOTOR GO RIGHT DRIFT");
    MotorGoRightDrift(top_speed);
  }

  if (ps2x.Button(PSB_PAD_UP) &&
      !ps2x.Button(PSB_PAD_DOWN) &&
      ps2x.Button(PSB_PAD_LEFT) &&
      !ps2x.Button(PSB_PAD_RIGHT))
  {
    Serial.println(" MOTOR GO LEFT FRONT");
    MotorGoLeftFront(top_speed);
  }

  if (!ps2x.Button(PSB_PAD_UP) &&
      ps2x.Button(PSB_PAD_DOWN) &&
      ps2x.Button(PSB_PAD_LEFT) &&
      !ps2x.Button(PSB_PAD_RIGHT))
  {
    Serial.println(" MOTOR GO LEFT BACK");
    MotorGoLeftBack(top_speed);
  }

  if (ps2x.Button(PSB_PAD_UP) &&
      !ps2x.Button(PSB_PAD_DOWN) &&
      !ps2x.Button(PSB_PAD_LEFT) &&
      ps2x.Button(PSB_PAD_RIGHT))
  {
    Serial.println(" MOTOR GO RIGHT FRONT");
    MotorGoRightFront(top_speed);
  }

  if (!ps2x.Button(PSB_PAD_UP) &&
      ps2x.Button(PSB_PAD_DOWN) &&
      !ps2x.Button(PSB_PAD_LEFT) &&
      ps2x.Button(PSB_PAD_RIGHT))
  {
    Serial.println(" MOTOR GO RIGHT BACK");
    MotorGoRightBack(top_speed);
  }


  if (ps2x.Button(PSB_L3))
  {
    Serial.println("MOTOR ROTATE LEFT");
    MotorRotateLeft(top_speed);
  }

  if (ps2x.Button(PSB_R3))
  {
    Serial.println("MOTOR ROTATE RIGHT");
    MotorRotateRight(top_speed);
  }

  // The below buttons can be used for special fucntions

  /*
    if (ps2x.ButtonPressed(PSB_CIRCLE))              //will be TRUE if button was JUST pressed
      Serial.println("Circle just pressed");
    if (ps2x.NewButtonState(PSB_CROSS))              //will be TRUE if button was JUST pressed OR released
      Serial.println("X just changed");
    if (ps2x.ButtonReleased(PSB_SQUARE))             //will be TRUE if button was JUST released
      Serial.println("Square just released");
  */

  // play happy birthday
  if (ps2x.Button(PSB_SELECT))
  {
    for (int x = 0; x < length; x++) {
      //Serial.println(scale[x]);
      buzzer.tone(scale[x], durt[x]* 500);

      // 1= 3/4F so one Beats is  187*4 = 748ms
      //delay(748 * durt[x]);
      buzzer.noTone(9);
    }
    //delay(3000);
  }

  //Use the PSS_LY and PSS_RY to control the usual movement
  int8_t leftSpeed  = ((128 - ps2x.Analog(PSS_LY)) * top_speed) >> 7;
  int8_t rightSpeed = ((128 - ps2x.Analog(PSS_RY)) * top_speed) >> 7 ;

  if (leftSpeed > 0)
  {
    DCMotor_Left_Front->setSpeed(leftSpeed);
    DCMotor_Left_Front->run(FORWARD);

    DCMotor_Left_Rear->setSpeed(leftSpeed);
    DCMotor_Left_Rear->run(FORWARD);
  }
  else if (leftSpeed < 0)
  {
    DCMotor_Left_Front->setSpeed(-leftSpeed);
    DCMotor_Left_Front->run(BACKWARD);

    DCMotor_Left_Rear->setSpeed(-leftSpeed);
    DCMotor_Left_Rear->run(BACKWARD);
  }

  if (rightSpeed > 0)
  {
    DCMotor_Right_Front->setSpeed(rightSpeed);
    DCMotor_Right_Front->run(FORWARD);

    DCMotor_Right_Rear->setSpeed(rightSpeed);
    DCMotor_Right_Rear->run(FORWARD);
  }
  else if (rightSpeed < 0)
  {
    DCMotor_Right_Front->setSpeed(-rightSpeed);
    DCMotor_Right_Front->run(BACKWARD);

    DCMotor_Right_Rear->setSpeed(-rightSpeed);
    DCMotor_Right_Rear->run(BACKWARD);
  }


#if 0
  if (ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) { //print stick values if either is TRUE
    Serial.print("Stick Values:");
    Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX
    Serial.print(",");
    Serial.print(ps2x.Analog(PSS_LX), DEC);
    Serial.print(",");
    Serial.print(ps2x.Analog(PSS_RY), DEC);
    Serial.print(",");
    Serial.println(ps2x.Analog(PSS_RX), DEC);
  }
#endif

  delay(150);
}
