/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\张                                                */
/*    Created:      Tue Jun 06 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Motor0               motor         19              
// Motor1               motor         20              
// Motor2               motor         1               
// Motor3               motor         2               
// MotorARM             motor         3               
// MotorHAND            motor         11              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "Vector2D.h"
#include "const.h"
 
using namespace vex;

typedef vec<float> vecf;
motor* motor_move[4];
motor* motor_arm,*motor_hand;
const int FORWARD=0;
const int REVERSE=1;
int direction[4]={FORWARD,REVERSE,FORWARD,REVERSE};

vecf now_direction(1,0);
double now_handangle=0;
double now_armangle=0;


//key stand for the button:
const int BUTTON_L1 = 10001;
const int BUTTON_L2 = 10002;
const int BUTTON_R1 = 10003;
const int BUTTON_R2 = 10004;
const int BUTTON_U = 10005;
const int BUTTON_D = 10006;
const int BUTTON_L = 10007;
const int BUTTON_R = 10008;
const int BUTTON_X = 10009;
const int BUTTON_Y = 10010;
const int BUTTON_A = 10011;
const int BUTTON_B = 10012;                
//return ture if the button is pressed
//return false if the botton isn't pressed or doesn't exist
bool checkbutton(int key_name)
{
  switch(key_name)
  {
    case BUTTON_L1: 
    return Controller1.ButtonL1.pressing();
    case BUTTON_L2:
    return Controller1.ButtonL2.pressing();
    case BUTTON_R1:
    return Controller1.ButtonR1.pressing();
    case BUTTON_R2:
    return Controller1.ButtonR2.pressing();
    case BUTTON_U:
    return Controller1.ButtonUp.pressing();
    case BUTTON_D:
    return Controller1.ButtonDown.pressing();
    case BUTTON_L:
    return Controller1.ButtonLeft.pressing();
    case BUTTON_R:
    return Controller1.ButtonRight.pressing();
    case BUTTON_X:
    return Controller1.ButtonX.pressing();
    case BUTTON_Y:
    return Controller1.ButtonY.pressing();
    case BUTTON_A:
    return Controller1.ButtonA.pressing();
    case BUTTON_B:
    return Controller1.ButtonB.pressing();
    default:
    return 0;
  }
}

//name of joystick
const int JOYSTICK_LEFT=20001;
const int JOYSTICK_RIGHT=20002;
vecf checkrocker(int joystick)
{
  float x, y;
  switch (joystick)
  {
    case JOYSTICK_LEFT:
    {
      x = Controller1.Axis2.position();
      y = Controller1.Axis1.position();
      vecf v(x,y);
      return v;
    }
    case JOYSTICK_RIGHT:
    {
      x = Controller1.Axis4.position();
      y = Controller1.Axis3.position();
      vecf v(x,y);
      return v;
    }
    default:
    vecf v(0,0);
    return v;
  }
}



/*
//motorname 电机指针
//direction 正反转
//speed 每一个时间间隔转动的角度
//timeInterval 时间间隔（ms）
*/
float timeInterval=4;
void run(motor* motorname, int direction, float speed)
{
    if (direction == FORWARD) {
        motorname->spin(directionType::fwd, speed, velocityUnits::pct);
    } else if (direction == REVERSE) {
        motorname->spin(directionType::rev, speed, velocityUnits::pct);
    }
}


void move_forward(float speed){
  for(int i=0;i<4;i++){
    run(motor_move[i],direction[i],speed);
  }
}
void move_back(float speed){
  for(int i=0;i<4;i++){
    run(motor_move[i],direction[i]^1,speed);
  }
}
void turn_left(float speed){
  for(int i=0;i<4;i++){
    //i%2==1，右侧电机，反转
    run(motor_move[i],direction[i]^(i%2?0:1),speed);
  }
}
void turn_right(float speed){
  for(int i=0;i<4;i++){
    //i%2==1，右侧电机，正转
    run(motor_move[i],direction[i]^(i%2?1:0),speed);
  }
}

void _stop(){
  for(int i=0;i<4;i++){
    //i%2==1，右侧电机，正转
    //motor_move[i]->setStopping(vex::brakeType::brake);
    motor_move[i]->stop(vex::brakeType::hold);
  }
}

const int UP=0;
const int OPEN=0;
const int DOWN=1;
const int CLOSE=1;
void up_arm(float speed){
  /*now_armangle+=pre_armangle;
  if(now_armangle>lim_armangle){
    now_armangle=lim_armangle;
    motor_arm->stop(vex::brakeType::hold);
  }else{
    
  }*/
  run(motor_arm,UP,speed);
}
void down_arm(float speed){
  /*now_armangle-=pre_armangle;
  if(now_armangle<0){
    now_armangle=0;
    motor_arm->stop(vex::brakeType::hold);
  }else{
    
  }*/
  run(motor_arm,UP^1,speed);
}
void hold_arm(){
  motor_arm->stop(vex::brakeType::hold);
}

void open_hand(float speed){
  /*now_handangle-=pre_handangle;
  if(now_handangle<0){
    now_handangle=0;
    motor_hand->stop(vex::brakeType::hold);
  }else{
    
  }*/
  run(motor_hand,OPEN,speed);
}
void close_hand(float speed){
  /*now_handangle+=pre_handangle;
  if(now_handangle>pai2){
    now_handangle=pai2;
    motor_hand->stop(vex::brakeType::hold);
  }else{
    
  }*/
  run(motor_hand,OPEN^1,speed);
}
void hold_hand(){
  motor_hand->stop(vex::brakeType::hold);
}

void move_arm(int move,double fixed=1)
{
  int T=300*fixed;
  while(T--){
    if(move==UP)up_arm(half_speed);
    else down_arm(half_speed);
    wait(timeInterval, msec);
  }
  hold_arm();
}

void move_hand(int move,double fixed=1)
{
  int T=100*fixed;
  while(T--){
    if(move==OPEN)open_hand(half_speed);
    else close_hand(half_speed);
    wait(timeInterval, msec);
  }
  hold_hand();
}

//2pai
//将车转向angle度（弧度制
void turn_angle(double angle,double fixed=1,double speed=full_speed){
  int work_time;
  work_time=fabs(angle)/pre_angle*fixed*(full_speed/speed);
  while(work_time--){
    if(angle>=0)
      turn_left(speed);
    else 
      turn_right(speed);
    wait(timeInterval, msec);
  }
  _stop();
}

// m
// 将车向前开meter米
void run_length(double meter,double fixed=1,double speed=full_speed){
  int work_time;
  work_time=fabs(meter)/pre_meter*fixed*(full_speed/speed);
  while(work_time--){
    if(meter>=0)
      move_forward(speed);
    else 
       move_back(speed);
    wait(timeInterval, msec);
  }
  _stop();
}


//将车从p1移动到p2
void movep2p(vecf p1,vecf p2,double fixed1 = 1,double fixed2 = 1){
  float p2p_angle=0;
  vecf target_direction=p2-p1;
  p2p_angle=(now_direction&target_direction)/(now_direction.length()*target_direction.length());
  p2p_angle=acos(p2p_angle);

  if((now_direction|target_direction)<0){//now在p1的右侧
    p2p_angle=-p2p_angle;
  }
  turn_angle(p2p_angle, fixed1);
  run_length(target_direction.length(), fixed2);
  _stop();
}

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  
  motor_move[0]=&Motor0;
  motor_move[1]=&Motor1;
  motor_move[2]=&Motor2;
  motor_move[3]=&Motor3;
  motor_arm=&MotorARM;
  motor_hand=&MotorHAND;
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  //__
    move_arm(DOWN,0.1);
    move_hand(CLOSE,1);
    move_arm(UP,0.5);
    //turn_angle(pai2,0.69);

    movep2p(vecf(1*UNIT,7*UNIT),vecf(2.27*UNIT,8.26*UNIT),0.72,1.13);

    move_arm(DOWN,0.5);
    move_hand(OPEN,1);
    move_arm(DOWN,0.1);
//
    run_length(0.2,1,50);
    move_hand(CLOSE,1);
    move_arm(UP,1);

    turn_angle(-pai2/2,0.93,50);
    move_arm(DOWN,0.5);
    move_hand(OPEN,1);

    move_arm(DOWN,0.5);
//2
    //run_length(-0.05,1,50);
    turn_angle(-pai2/2,0.40);

    run_length(0.35,1,50);
    move_hand(CLOSE,1);
    move_arm(UP,1.2);

    turn_angle(pai2/2,1,30);
    //run_length(0.2,0.6,30);
    move_arm(DOWN,0.5);
    move_hand(OPEN,1);
//5
    run_length(-0.2,1,30);
    move_arm(DOWN,0.6);
    turn_angle(-pai2,0.4,50);
    run_length(0.6,1.1,50);

    move_hand(CLOSE,1);
    move_arm(UP,0.6);
    turn_angle(pai2/2,1.15,50);//
    run_length(-0.05,0.9,30);//
    move_arm(DOWN,0.5);
    move_hand(OPEN,1);
    move_arm(DOWN,0.5);

    run_length(0.3,1.2,50);//
    move_hand(CLOSE,1);
    move_arm(UP,0.8);

    turn_angle(-pai2/2,0.85,30);//
    run_length(0.1,0.7,30);//
    move_arm(DOWN,0.5);
    move_hand(OPEN,1);


    
    
    _stop();
    
//__
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  double move_speed,turn_speed;
  while(1){
    if(checkbutton(BUTTON_L1)||checkbutton(BUTTON_R1)||checkbutton(BUTTON_L2)||checkbutton(BUTTON_R2)){
      // if(checkbutton(BUTTON_L1))      {run(motor_move[0],direction[0],full_speed);   run(motor_move[2],direction[2],full_speed);}
      // else if(checkbutton(BUTTON_L2)) {run(motor_move[0],direction[0]^1,full_speed); run(motor_move[2],direction[2]^1,full_speed);}
      // else                            {run(motor_move[0],direction[0],0);            run(motor_move[2],direction[2],0);}
      // if(checkbutton(BUTTON_R1))      {run(motor_move[1],direction[1],full_speed);   run(motor_move[3],direction[3],full_speed);}
      // else if(checkbutton(BUTTON_R2)) {run(motor_move[1],direction[1]^1,full_speed); run(motor_move[3],direction[3]^1,full_speed);}
      // else                            {run(motor_move[1],direction[1],0);            run(motor_move[3],direction[3],0);}
      move_speed=half_speed;
      turn_speed=quat_speed;

    }else{
      move_speed=full_speed;
      turn_speed=half_speed;
    }

    {

      if     (checkbutton(BUTTON_U))  move_forward (move_speed);
      else if(checkbutton(BUTTON_D))  move_back    (move_speed);
      else if(checkbutton(BUTTON_L))  turn_left    (turn_speed);
      else if(checkbutton(BUTTON_R))  turn_right   (turn_speed);
      else   _stop();
    }

    if     (checkbutton(BUTTON_X))  up_arm(half_speed);
    else if(checkbutton(BUTTON_B))  down_arm(half_speed);
    else                            hold_arm();
    if     (checkbutton(BUTTON_A))  open_hand(half_speed);
    else if(checkbutton(BUTTON_Y))  close_hand(half_speed);
    else                            hold_hand();
    wait(timeInterval, msec);
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}