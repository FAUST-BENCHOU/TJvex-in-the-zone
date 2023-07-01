#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor Motor0 = motor(PORT19, ratio18_1, false);
motor Motor1 = motor(PORT20, ratio18_1, false);
motor Motor2 = motor(PORT1, ratio18_1, false);
motor Motor3 = motor(PORT2, ratio18_1, false);
motor MotorARM = motor(PORT3, ratio18_1, false);
motor MotorHAND = motor(PORT11, ratio18_1, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}