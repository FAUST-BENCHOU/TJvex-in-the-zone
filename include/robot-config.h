using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor Motor0;
extern motor Motor1;
extern motor Motor2;
extern motor Motor3;
extern motor MotorARM;
extern motor MotorHAND;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );