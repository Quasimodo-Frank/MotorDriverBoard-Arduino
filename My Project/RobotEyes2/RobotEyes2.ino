#include "Servo.h"

// the io pins forthe servos on the driver board
#define TOP_RIGHT_EYELID_SERVO_PIN      2
#define BOTTOM_RIGHT_EYELID_SERVO_PIN   3
#define TOP_LEFT_EYELID_SERVO_PIN       4
#define BOTTOM_LEFT_EYELID_SERVO_PIN    7
#define HORIZONTAL_EYEBALL_SERVO_PIN    5
#define VERTICAL_EYEBALL_SERVO_PIN      6

// the range of each servo freedom after a fe tries 
#define MIN_HORIZONTAL_ANGLE            45
#define MAX_HORIZONTAL_ANGLE            135
#define MIN_VERTICAL_ANGLE              65
#define MAX_VERTICAL_ANGLE              115

#define MIN_TOP_EYELID_ANGLE            60
#define MAX_TOP_EYELID_ANGLE            120
#define MIN_BOTTOM_EYELID_ANGLE         60
#define MAX_BOTTOM_EYELID_ANGLE         120

// the servos on the board
Servo top_right_eyelid_servo; 
Servo bottom_right_eyelid_servo; 
Servo top_left_eyelid_servo; 
Servo bottom_left_eyelid_servo; 
Servo horizontal_eyeball_servo; 
Servo vertical_eyeball_servo;

#include "PS2X_lib.h"

// ps2 controller pins
#define PS2_DAT     12
#define PS2_CMD     11
#define PS2_SEL     10
#define PS2_CLK     13

/******************************************************************
 * select modes of PS2 controller:
 *   - pressures = analog reading of push-butttons 
 *   - rumble    = motor rumbling
 * uncomment 1 of the lines for each mode selection
 ******************************************************************/
#define ps2x_pressures   false
#define ps2x_rumble      false

PS2X ps2x;
int ps2x_error      = 0;
byte ps2x_type      = 0;
byte ps2x_vibrate   = 0;

// Reset func 
void (* resetFunc) (void) = 0;

#include "RGBLed.h"
RGBLed rgbled_A3(A1, 2);

#define BUZZER_PIN 9 
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
               Do_h, Si, La, Fa_h, Fa_h, Mi_h, Do_h, Re_h, Do_h }; 

// Beats time
float durt[]=
{
    0.5, 0.5, 1, 1, 1, 1+1, 0.5, 0.5,
    1, 1, 1, 1+1, 0.5, 0.5, 1, 1,
    1, 1, 1, 0.5, 0.5, 1, 1, 1, 1+1
};

int buzz_length;


// the demo_mode
byte demo_mode       = 0;


void setup()   
{  

    // set up the serial port
    Serial.begin(9600);  //Set the baud rate
    delay(500);

    rgbled_A3.setColor(1,255,255,255);
    rgbled_A3.setColor(2,255,255,255);
    rgbled_A3.show();

    pinMode(BUZZER_PIN, OUTPUT);
    // get scale length
    buzz_length = sizeof(scale) / sizeof(scale[0]);  
    
    // attach the top right eye lid servo
    top_right_eyelid_servo.attach(TOP_RIGHT_EYELID_SERVO_PIN);
    delay(50);
    // attach the bottom right eyelid servo
    bottom_right_eyelid_servo.attach(BOTTOM_RIGHT_EYELID_SERVO_PIN);
    delay(50);

    // attach the top left eyelid servo
    top_left_eyelid_servo.attach(TOP_LEFT_EYELID_SERVO_PIN);
    delay(50);

    // attch the bottom left eyelid servo
    bottom_left_eyelid_servo.attach(BOTTOM_LEFT_EYELID_SERVO_PIN);
    delay(50);

    // attach the horizontal eyeball servo
    horizontal_eyeball_servo.attach(HORIZONTAL_EYEBALL_SERVO_PIN);
    delay(50);
    
    // attach the vertical eyeball servo
    vertical_eyeball_servo.attach(VERTICAL_EYEBALL_SERVO_PIN);
    delay(50);


    top_right_eyelid_servo.write(90);
    delay(10);
    top_left_eyelid_servo.write(90);
    delay(10);
    bottom_right_eyelid_servo.write(90);
    delay(10);
    bottom_left_eyelid_servo.write(90);
    delay(10);
    horizontal_eyeball_servo.write(90);
    delay(10);
    vertical_eyeball_servo.write(90);

    delay(100);

    //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
    ps2x_error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, ps2x_pressures, ps2x_rumble);
  
    
    if(ps2x_error == 0){
        Serial.print("Found Controller, configured successful ");
        Serial.print("pressures = ");
        if (ps2x_pressures)
            Serial.println("true ");
        else
            Serial.println("false");
        Serial.print("rumble = ");
        if (ps2x_rumble)
            Serial.println("true)");
        else
            Serial.println("false");
        Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
        Serial.println("holding L1 or R1 will print out the analog stick values.");
        Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
    }  
    else if(ps2x_error == 1)
        Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
    else if(ps2x_error == 2)
        Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

    else if(ps2x_error == 3)
        Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  
    ps2x_type = ps2x.readType(); 
    switch(ps2x_type) {
    case 0:
        Serial.println("Unknown Controller type found ");
        break;
    case 1:
        Serial.println("DualShock Controller found ");
        break;
    case 2:
        Serial.println("GuitarHero Controller found ");
        break;
    case 3:
        Serial.println("Wireless Sony DualShock Controller found ");
        break;
   }


    demo_mode=0;

}


void blink_both_eyes ()
{
    top_right_eyelid_servo.write(MIN_TOP_EYELID_ANGLE);
    delay(10);
    top_left_eyelid_servo.write(MAX_TOP_EYELID_ANGLE);
    delay(10);
    bottom_right_eyelid_servo.write(MAX_BOTTOM_EYELID_ANGLE);
    delay(10);
    bottom_left_eyelid_servo.write(MIN_BOTTOM_EYELID_ANGLE);
    delay(10);

    delay (400);

    top_right_eyelid_servo.write(90);
    delay(10);
    top_left_eyelid_servo.write(90);
    delay(10);
    bottom_right_eyelid_servo.write(90);
    delay(10);
    bottom_left_eyelid_servo.write(90);
    delay(10);

    delay (500);

}


void look_up_both_eyes ()
{
    top_right_eyelid_servo.write(MAX_TOP_EYELID_ANGLE);
    delay(10);
    top_left_eyelid_servo.write(MIN_TOP_EYELID_ANGLE);
    delay(10);
    bottom_right_eyelid_servo.write(MAX_BOTTOM_EYELID_ANGLE);
    delay(10);
    bottom_left_eyelid_servo.write(MIN_BOTTOM_EYELID_ANGLE);
    delay(10);
    horizontal_eyeball_servo.write(90);
    delay(10);
    vertical_eyeball_servo.write(MAX_VERTICAL_ANGLE);
    delay(10);

    delay (1500);

    top_right_eyelid_servo.write(90);
    delay(10);
    top_left_eyelid_servo.write(90);
    delay(10);
    bottom_right_eyelid_servo.write(90);
    delay(10);
    bottom_left_eyelid_servo.write(90);
    delay(10);
    horizontal_eyeball_servo.write(90);
    delay(10);
    vertical_eyeball_servo.write(90);
    delay(10);

    delay (500);

}

void look_left_both_eyes ()
{
    top_right_eyelid_servo.write(90);
    delay(10);
    top_left_eyelid_servo.write(90);
    delay(10);
    bottom_right_eyelid_servo.write(90);
    delay(10);
    bottom_left_eyelid_servo.write(90);
    delay(10);
    horizontal_eyeball_servo.write(MAX_HORIZONTAL_ANGLE);
    delay(10);
    vertical_eyeball_servo.write(90);
    delay(10);

    delay (1500);

    top_right_eyelid_servo.write(90);
    delay(10);
    top_left_eyelid_servo.write(90);
    delay(10);
    bottom_right_eyelid_servo.write(90);
    delay(10);
    bottom_left_eyelid_servo.write(90);
    delay(10);
    horizontal_eyeball_servo.write(90);
    delay(10);
    vertical_eyeball_servo.write(90);
    delay(10);

    delay (500);
}


void move_both_eye_balls (int lx, int ly, int rx, int ry)
{
#if 0
    top_right_eyelid_servo.write(90);
    delay(10);
    top_left_eyelid_servo.write(90);
    delay(10);
    bottom_right_eyelid_servo.write(90);
    delay(10);
    bottom_left_eyelid_servo.write(90);
    delay(10);
#endif
    int horizontal_angle = lx* (MAX_HORIZONTAL_ANGLE-MIN_HORIZONTAL_ANGLE)/256  + MIN_HORIZONTAL_ANGLE;
    //Serial.println("horizontal angle: ");
    //Serial.print (horizontal_angle, DEC);
    //Serial.println("");

    int vertical_angle = 180-(ly*(MAX_VERTICAL_ANGLE-MIN_VERTICAL_ANGLE)/256 + MIN_VERTICAL_ANGLE);
    //Serial.println("horizontal angle: ");
    //Serial.print (vertical_angle, DEC);
    //Serial.println("");

    horizontal_eyeball_servo.write(horizontal_angle);
    delay(10);

    vertical_eyeball_servo.write(vertical_angle);
    delay(10);

}



void move_both_eye_lids (int lx, int ly, int rx, int ry)
{
#if 0
    top_right_eyelid_servo.write(90);
    delay(10);
    top_left_eyelid_servo.write(90);
    delay(10);
    bottom_right_eyelid_servo.write(90);
    delay(10);
    bottom_left_eyelid_servo.write(90);
    delay(10);
#endif

    int vertical_angle = 180-(ry*(MAX_TOP_EYELID_ANGLE-MIN_TOP_EYELID_ANGLE)/256 + MIN_TOP_EYELID_ANGLE);
    //Serial.println("horizontal angle: ");
    //Serial.print (vertical_angle, DEC);
    //Serial.println("");

    top_right_eyelid_servo.write(vertical_angle);
    delay(10);
    top_left_eyelid_servo.write(180-vertical_angle);
    delay(10);
    bottom_right_eyelid_servo.write(180-vertical_angle);
    delay(10);
    bottom_left_eyelid_servo.write(vertical_angle);
    delay(10);


}



void look_right_both_eyes ()
{
    top_right_eyelid_servo.write(90);
    delay(10);
    top_left_eyelid_servo.write(90);
    delay(10);
    bottom_right_eyelid_servo.write(90);
    delay(10);
    bottom_left_eyelid_servo.write(90);
    delay(10);
    horizontal_eyeball_servo.write(MIN_HORIZONTAL_ANGLE);
    delay(10);
    vertical_eyeball_servo.write(90);
    delay(10);

    delay (1500);

    top_right_eyelid_servo.write(90);
    delay(10);
    top_left_eyelid_servo.write(90);
    delay(10);
    bottom_right_eyelid_servo.write(90);
    delay(10);
    bottom_left_eyelid_servo.write(90);
    delay(10);
    horizontal_eyeball_servo.write(90);
    delay(10);
    vertical_eyeball_servo.write(90);
    delay(10);

    delay (500);

}

void look_down_both_eyes ()
{
    top_right_eyelid_servo.write(MIN_TOP_EYELID_ANGLE);
    delay(10);
    top_left_eyelid_servo.write(MAX_TOP_EYELID_ANGLE);
    delay(10);
    bottom_right_eyelid_servo.write(MIN_BOTTOM_EYELID_ANGLE);
    delay(10);
    bottom_left_eyelid_servo.write(MAX_BOTTOM_EYELID_ANGLE);
    delay(10);
    horizontal_eyeball_servo.write(90);
    delay(10);
    vertical_eyeball_servo.write(MIN_VERTICAL_ANGLE);
    delay(10);

    delay (1500);

    top_right_eyelid_servo.write(90);
    delay(10);
    top_left_eyelid_servo.write(90);
    delay(10);
    bottom_right_eyelid_servo.write(90);
    delay(10);
    bottom_left_eyelid_servo.write(90);
    delay(10);
    horizontal_eyeball_servo.write(90);
    delay(10);
    vertical_eyeball_servo.write(90);
    delay(10);

    delay (500);

}

void close_both_eyes ()
{
    top_right_eyelid_servo.write(MIN_TOP_EYELID_ANGLE);
    delay(10);
    top_left_eyelid_servo.write(MAX_TOP_EYELID_ANGLE);
    delay(10);
    bottom_right_eyelid_servo.write(MAX_BOTTOM_EYELID_ANGLE);
    delay(10);
    bottom_left_eyelid_servo.write(MIN_BOTTOM_EYELID_ANGLE);
    delay(10);

    delay (1500);

    top_right_eyelid_servo.write(90);
    delay(10);
    top_left_eyelid_servo.write(90);
    delay(10);
    bottom_right_eyelid_servo.write(90);
    delay(10);
    bottom_left_eyelid_servo.write(90);
    delay(10);

    delay (500);

}

void wide_open_both_eyes ()
{
    top_right_eyelid_servo.write(MAX_TOP_EYELID_ANGLE);
    delay(10);
    top_left_eyelid_servo.write(MIN_TOP_EYELID_ANGLE);
    delay(10);
    bottom_right_eyelid_servo.write(MIN_BOTTOM_EYELID_ANGLE);
    delay(10);
    bottom_left_eyelid_servo.write(MAX_BOTTOM_EYELID_ANGLE);
    delay(10);

    delay (1500);

    top_right_eyelid_servo.write(90);
    delay(10);
    top_left_eyelid_servo.write(90);
    delay(10);
    bottom_right_eyelid_servo.write(90);
    delay(10);
    bottom_left_eyelid_servo.write(90);
    delay(10);

    delay (500);

}

void blink_right_eye ()
{
    top_right_eyelid_servo.write(MIN_TOP_EYELID_ANGLE);
    delay(10);
    bottom_right_eyelid_servo.write(MAX_BOTTOM_EYELID_ANGLE);
    delay(10);

    delay (500);

    top_right_eyelid_servo.write(90);
    delay(10);
    top_left_eyelid_servo.write(90);
    delay(10);
    bottom_right_eyelid_servo.write(90);
    delay(10);
    bottom_left_eyelid_servo.write(90);
    delay(10);

    delay (500);

}

void blink_left_eye ()
{
    top_left_eyelid_servo.write(MAX_TOP_EYELID_ANGLE);
    delay(10);
    bottom_left_eyelid_servo.write(MIN_BOTTOM_EYELID_ANGLE);
    delay(10);

    delay (500);

    top_right_eyelid_servo.write(90);
    delay(10);
    top_left_eyelid_servo.write(90);
    delay(10);
    bottom_right_eyelid_servo.write(90);
    delay(10);
    bottom_left_eyelid_servo.write(90);
    delay(10);

    delay (500);

}

void loop()   
{  

  if(ps2x_error == 1){ //skip loop if no controller found
      resetFunc();
  }

  ps2x.read_gamepad(false, ps2x_vibrate); //read controller and set large motor to spin at 'vibrate' speed
  
  if(ps2x.Button(PSB_START))         //will be TRUE as long as button is pressed
  {
      //Serial.println("Start is being held");
      if (demo_mode == 1)
      {
          demo_mode=0;
      }
      else
      {
          demo_mode=1;
      }
  }

    if (demo_mode == 1)
      {
          rgbled_A3.setColor(1,255, 0,0);
          rgbled_A3.setColor(2,255, 0,0);
          rgbled_A3.show();

      }
      else
      {
          rgbled_A3.setColor(1,0,0,255);
          rgbled_A3.setColor(2,0,0,255);
          rgbled_A3.show();
      }


  //blink_both_eyes ();
  //delay(1500);


  if(ps2x.Button(PSB_SELECT)){
    Serial.println("Select is being held");      
    blink_both_eyes();
  }

  if(ps2x.Button(PSB_PAD_UP)) {      //will be TRUE as long as button is pressed
    Serial.print("PSB_PAD_UP ");
    look_up_both_eyes();
  }

  if(ps2x.Button(PSB_PAD_RIGHT)){
    Serial.print("PSB_PAD_RIGHT ");
    look_left_both_eyes();
  }

  if(ps2x.Button(PSB_PAD_LEFT)){
    Serial.print("PSB_PAD_LEFT ");
    look_right_both_eyes();
  }

  if(ps2x.Button(PSB_PAD_DOWN)){
    Serial.print("PSB_PAD_DOWN ");
    look_down_both_eyes();
  }   

  if(ps2x.Button(PSB_L1)){
    Serial.print("PSB_L1 ");
    wide_open_both_eyes();
  }   

  if(ps2x.Button(PSB_R1)){
    Serial.print("PSB_R1 ");
    close_both_eyes();
  }   

  if(ps2x.Button(PSB_L2)){
    Serial.print("PSB_L2 ");
    blink_left_eye();
  }   

  if(ps2x.Button(PSB_R2)){
    Serial.print("PSB_R2 ");
    blink_right_eye();
  }   

  if(ps2x.Button(PSB_CIRCLE)) {
    Serial.println("Circle just pressed");
    for(int x = 0; x < buzz_length; x++) {
      // Serial.println(scale[x]);
      tone(BUZZER_PIN, scale[x]);
      
      rgbled_A3.setColor(1, scale[x] - 425, scale[x] - 500, scale[x] - 95);
      rgbled_A3.setColor(2, scale[x] - 425, scale[x] - 500, scale[x] - 95);
      rgbled_A3.show();
      
      // 1= 3/4F so one Beats is  187*4 = 748ms
      delay(374 * durt[x]);
      noTone(BUZZER_PIN);
    }
    delay(3000);
  } 

  ps2x_vibrate = ps2x.Analog(PSAB_CROSS);  //this will set the large motor vibrate speed based on how hard you press the blue (X) button
  if (ps2x.NewButtonState()) {        //will be TRUE if any button changes state (on to off, or off to on)
    if(ps2x.Button(PSB_L3))
      Serial.println("L3 pressed");
    if(ps2x.Button(PSB_R3))
      Serial.println("R3 pressed");
    if(ps2x.Button(PSB_L2))
      Serial.println("L2 pressed");
    if(ps2x.Button(PSB_R2))
      Serial.println("R2 pressed");
    if(ps2x.Button(PSB_TRIANGLE))
      Serial.println("Triangle pressed");        
  }

  if(ps2x.ButtonPressed(PSB_CIRCLE))               //will be TRUE if button was JUST pressed
    Serial.println("Circle just pressed");
  if(ps2x.NewButtonState(PSB_CROSS))               //will be TRUE if button was JUST pressed OR released
    Serial.println("X just changed");
  if(ps2x.ButtonReleased(PSB_SQUARE))              //will be TRUE if button was JUST released
    Serial.println("Square just released");     

  if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) { //print stick values if either is TRUE
    Serial.print("Stick Values:");
    Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
    Serial.print(",");
    Serial.print(ps2x.Analog(PSS_LX), DEC); 
    Serial.print(",");
    Serial.print(ps2x.Analog(PSS_RY), DEC); 
    Serial.print(",");
    Serial.println(ps2x.Analog(PSS_RX), DEC); 
  }     
  

  move_both_eye_balls(ps2x.Analog(PSS_LX), ps2x.Analog(PSS_LY), ps2x.Analog(PSS_RX), ps2x.Analog(PSS_RY));
  move_both_eye_lids(ps2x.Analog(PSS_LX), ps2x.Analog(PSS_LY), ps2x.Analog(PSS_RX), ps2x.Analog(PSS_RY));




    //bottom_right_eyelid_servo.write(45);

  while (demo_mode)
  //while (ps2x.ButtonPressed(PSB_START))
  {

      blink_both_eyes ();
      delay(1500);

      blink_right_eye();
      delay (1500);

      //blink_both_eyes ();
      //delay(1500);

      blink_left_eye();
      delay (1500);

      //blink_both_eyes ();
      //delay(1500);

      wide_open_both_eyes();
      delay (1500);

      //blink_both_eyes ();
      //delay(1500);

      close_both_eyes();
      delay (1500);

      //blink_both_eyes ();
      //delay(1500);

      look_up_both_eyes();
      delay (1500);

      //blink_both_eyes ();
      //delay(1500);

      look_down_both_eyes();
      delay (1500);

      //blink_both_eyes ();
      //delay(1500);

      look_left_both_eyes();
      delay (1500);
      
      //blink_both_eyes ();
      //delay(1500);

      look_right_both_eyes();
      delay (1500);

      demo_mode = 0;
  }

}  
