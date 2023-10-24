#include "EZ-Template/util.hpp"
#include "autons.hpp"
#include "main.h"



const int DRIVE_SPEED = 110;  // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                              // If this is 127 and the robot tries to heading correct, it's only correcting by
                              // making one side slower.  When this is 87%, it's correcting by making one side
                              // faster and one side slower, giving better heading correction.
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;

int catashots = 0;
///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, .45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 3.9, 0.003, 36, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void one_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void two_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches

  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();
}

///
// Turn Example
///
void turn_example() {
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  /*
  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
  */
}

///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(6);
  chassis.set_max_speed(40);  // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_until(-6);
  chassis.set_max_speed(40);  // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();
}

///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive

  chassis.set_swing_pid(ez::LEFT_SWING, 45, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(12);

  chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
  chassis.wait_drive();
}

///
// Auto that tests everything
///
void combining_movements() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.set_drive_pid(-12, 127);
    chassis.wait_drive();

    // If failsafed...
    if (chassis.interfered) {
      chassis.reset_drive_sensor();
      chassis.set_drive_pid(-2, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees!
// If interfered, robot will drive forward and then attempt to drive backwards.
void interfered_example() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
}


void MEGALAZY()
{
  arm.set_value(!arm.get_value());
  chassis.set_turn_pid(-30, 80);
  chassis.wait_drive();
  chassis.set_drive_pid(-28 * 2, 127);
  chassis.wait_drive();
  // chassis.set_swing_pid(e_swing type, double target, int speed)
  chassis.set_drive_pid(13 * 2, 127);
  chassis.wait_drive();
  chassis.set_turn_pid(79, 80);
  chassis.wait_drive();
  chassis.set_drive_pid(7, 127);
  chassis.wait_drive();
  while (true) {
    if (colorSensor.get_proximity() >= 180) {
      cataAysnc();
      catashots++;
    }
    pros ::delay(200);
    if (catashots >= 44) {
      break;
    }
  }
}

// . . .
// Make your own autonomous functions here!
// . . .
// MULTIPLY BY 2


void bigDoolAutonR() {
  cataBysnc();
  arm.set_value(!arm.get_value());
  chassis.set_swing_pid(ez::RIGHT_SWING, -10, SWING_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(90, 127);
  setIntake(-127);
  chassis.wait_drive();
  pros::delay(300);

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  setIntake(0);

  chassis.set_drive_pid(20, 127);
  setIntake(127);
  chassis.wait_drive();
  pros ::delay(300);
  chassis.set_drive_pid(-18, 127);
  chassis.wait_drive();
  setIntake(0);
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-30, 127);
  chassis.wait_drive();
  setIntake(-127);
  chassis.set_drive_pid(36, 127);
  chassis.wait_drive();
  chassis.set_turn_pid(-63, SWING_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(20, 127);
  chassis.wait_drive();
  pros ::delay(200);
  setIntake(0);
  chassis.set_turn_pid(90, 127);
  chassis.wait_drive();
  chassis.set_drive_pid(36, 127);
  setIntake(127);
  chassis.wait_drive();
  chassis.set_drive_pid(-20, 127);
  chassis.wait_drive();
  setIntake(0);
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-41, 127);
  chassis.wait_drive();
  chassis.set_swing_pid(RIGHT_SWING, -136, SWING_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(76, 127);
  chassis.wait_drive();
  arm.set_value(!arm.get_value());
}

void DOOL3R() // 2nd arm triball 
{
  arm.set_value(!arm.get_value()); 
  chassis.set_drive_pid(10,80);
  chassis.wait_drive();
  chassis.set_drive_pid(70, 127);
  chassis.wait_drive();
  chassis.set_turn_pid(90, 127); //
  chassis.wait_drive();
  setIntake(127);
  cataBysnc();
  chassis.set_drive_pid(-41,127); // first backup
  chassis.wait_drive();
  chassis.set_turn_pid(-45,80);// turn to 3rd tribal 
  chassis.wait_drive();
  setIntake(-127);
  chassis.set_drive_pid(14,127);
  chassis.wait_drive();
  rightWing.set_value(!rightWing.get_value());
  chassis.set_drive_pid(-10,127);
  chassis.wait_drive();
  rightWing.set_value(!rightWing.get_value());
  chassis.set_turn_pid(-90, 127);
  chassis.wait_drive();
  chassis.set_turn_pid(85,127);
  //rightWing.set_value(!rightWing.get_value());
  chassis.wait_drive();
 // rightWing.set_value(!rightWing.get_value());
  setIntake(127);
  pros :: delay(1000);
  chassis.set_turn_pid(225,127);
  chassis.wait_drive();
  setIntake(-127);
  chassis.set_drive_pid(12,100);
  chassis.wait_drive();
  chassis.set_drive_pid(-12,100);
  chassis.wait_drive();
  chassis.set_turn_pid(87,127);
  chassis.wait_drive();
  setIntake(127);
  chassis.set_drive_pid(-10,127);
  chassis.wait_drive();
  setIntake(0);
  chassis.set_turn_pid(-90,127);
  chassis.wait_drive();
  ledouble();
  chassis.set_drive_pid(-100,127);
  chassis.wait_until(-50);
  ledouble();
  chassis.set_swing_pid(RIGHT_SWING, -135, SWING_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(60, 127);
  chassis.wait_drive();
  arm.set_value(!arm.get_value());
}
void dool2R()
{
  arm.set_value(!arm.get_value()); 
  //chassis.set_swing_pid(ez::RIGHT_SWING, -10, SWING_SPEED);
  //chassis.wait_drive();
  chassis.set_drive_pid(10,80);
  chassis.wait_drive();
  chassis.set_drive_pid(70, 127);
  chassis.wait_drive();
  chassis.set_turn_pid(90, 127); //
  chassis.wait_drive();
  setIntake(127);
  cataBysnc();
  chassis.set_drive_pid(-52,127);
  chassis.wait_drive();
  rightWing.set_value(!rightWing.get_value());
  chassis.set_swing_pid(ez::RIGHT_SWING, 45, SWING_SPEED);
  setIntake(-127);
  chassis.wait_drive();
  rightWing.set_value(!rightWing.get_value());
  chassis.set_drive_pid(20,127);//
  chassis.wait_drive();
  chassis.set_swing_pid(ez::RIGHT_SWING, 90, SWING_SPEED);
  chassis.wait_drive();
  setIntake(0);
  chassis.set_drive_pid(20,127); //
  setIntake(127);
  chassis.wait_drive();
  pros :: delay(400);
  chassis.set_turn_pid(-65,80); //
  chassis.wait_drive();
  setIntake(-127);
  chassis.set_drive_pid(28,127);
  chassis.wait_drive();
  chassis.set_drive_pid(-26,127);
  chassis.wait_drive();
  chassis.set_turn_pid(90,127);
  chassis.wait_drive();
  setIntake(127);
  chassis.set_drive_pid(-24,127);
  chassis.wait_drive();
  chassis.set_turn_pid(-90,127);
  chassis.wait_drive();
  ledouble();
  chassis.set_drive_pid(-100,127);
  chassis.wait_until(-40);
  pros :: delay(200); 
  chassis.set_swing_pid(ez::RIGHT_SWING, -142,80);
  chassis.wait_drive();
  ledouble();
  setIntake(-127);
  chassis.set_drive_pid(100,127);
  arm.set_value(!arm.get_value());
  chassis.wait_until(60);
}

void bitchassAutonL() {
  arm.set_value(!arm.get_value());
  chassis.set_swing_pid(ez::LEFT_SWING, 10, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(88, 127);
  setIntake(-127);
  chassis.wait_drive();
  pros::delay(700);

  chassis.set_turn_pid(-50, TURN_SPEED);
  chassis.wait_drive();
  setIntake(0);
  pros :: Task shoot_cata(cataAysnc, TASK_PRIORITY_MIN);
  pros ::delay(100);
  chassis.set_swing_pid(ez::RIGHT_SWING, 50, SWING_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(31, 127);
  setIntake(-127);
  chassis.wait_drive();
  pros::delay(500);
  chassis.set_drive_pid(-12, 127);
  chassis.wait_drive();
  chassis.set_turn_pid(222, 90);
  chassis.wait_drive();
  chassis.set_drive_pid(22, 127);
  pros :: Task shoot_cat(cataAysnc, TASK_PRIORITY_MIN);
  pros ::delay(100);

  chassis.set_drive_pid(100, 127);
  chassis.wait_drive();
  setIntake(0);
  // chassis.set_turn_pid(-75, TURN_SPEED);
  // chassis.wait_drive();

  // chassis.set_turn_pid(-137, TURN_SPEED);
  //  chassis.wait_drive();
  // chassis.set_drive_pid(100, 127, true);
  //  chassis.wait_drive();
  arm.set_value(!arm.get_value());
  pros ::delay(800);
  chassis.set_drive_pid(-50, 127);
  chassis.wait_until(-36);
  setIntake(-127);
  arm.set_value(!arm.get_value());
  pros ::delay(600);
  chassis.set_drive_pid(22, 127);
  chassis.wait_drive();
  chassis.set_drive_pid(-20, 127);
  chassis.wait_drive();
  pros ::delay(400);
  setIntake(0);
  pros :: Task shoot_ca(cataAysnc, TASK_PRIORITY_MIN);
  pros ::delay(200);
  chassis.set_turn_pid(100, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(80, 127, false);
  chassis.wait_drive();
}

void endgameL() {
  arm.set_value(!arm.get_value()); 
  chassis.set_drive_pid(10,80);
  chassis.wait_drive();
  chassis.set_drive_pid(70, 127);
  chassis.wait_drive();
  chassis.set_turn_pid(-90, 127); //
  chassis.wait_drive();
  setIntake(127);
  chassis.set_drive_pid(-8,127);
  chassis.wait_drive();
  chassis.set_turn_pid(20,127);
  chassis.wait_drive();
  setIntake(-127);
  chassis.set_drive_pid(10,127);
  chassis.wait_drive();
  chassis.set_drive_pid(-10,127);
  chassis.wait_drive();
  chassis.set_turn_pid(-90,127);
  chassis.wait_drive();
  cataAysnc();
  setIntake(0);
  rightWing.set_value(!rightWing.get_value());
  chassis.set_drive_pid(-65,127);
  chassis.wait_until(-45);
  chassis.set_drive_pid(10,127);
  chassis.wait_drive();
  setIntake(127);
  chassis.set_drive_pid(47,127);
  chassis.wait_drive();
  rightWing.set_value(!rightWing.get_value());
  chassis.set_drive_pid(-10,127);
  chassis.wait_drive();
  chassis.set_swing_pid(RIGHT_SWING,65,80);
  chassis.wait_drive();
  setIntake(0);
  chassis.set_drive_pid(-64,127);
  chassis.wait_drive();
  chassis.set_turn_pid(-35,127);
  chassis.wait_drive();
  leftWing.set_value(!leftWing.get_value());
  chassis.set_drive_pid(-24,100);
  chassis.wait_drive();
  chassis.set_swing_pid(LEFT_SWING,-90,127);
  chassis.wait_drive();
  leftWing.set_value(!leftWing.get_value());
  chassis.set_turn_pid(-75,100);
  chassis.wait_drive();
  chassis.set_drive_pid(-76,127);
  chassis.wait_drive();
}

void pluh ()
{
  chassis.set_turn_pid(-30, 80);
  chassis.wait_drive();
  chassis.set_drive_pid(-28 * 2, 127);
  chassis.wait_drive();
  // chassis.set_swing_pid(e_swing type, double target, int speed)
  chassis.set_drive_pid(13 * 2, 127);
  chassis.wait_drive();
  chassis.set_turn_pid(79, 80);
  chassis.wait_drive();
  chassis.set_drive_pid(7, 127);
  chassis.wait_drive();
  while (true) {
    if (colorSensor.get_proximity() >= 70) {
      cataAysnc();
      catashots++;
    }
    pros ::delay(100);
    if (catashots >= 44) {
      break;
    }
  }
}

void autonSkills() {
  arm.set_value(!arm.get_value());
  chassis.set_turn_pid(-30, 80);
  chassis.wait_drive();
  chassis.set_drive_pid(-28 * 2, 127);
  chassis.wait_drive();
  // chassis.set_swing_pid(e_swing type, double target, int speed)
  chassis.set_drive_pid(13 * 2, 127);
  chassis.wait_drive();
  chassis.set_turn_pid(79, 80);
  chassis.wait_drive();
  chassis.set_drive_pid(7, 127);
  chassis.wait_drive();
  while (true) {
    if (colorSensor.get_proximity() >= 70) {
      cataAysnc();
      catashots++;
    }
    pros ::delay(100);
    if (catashots >= 44) {
      break;
    }
  }

  pros ::delay(500);
  chassis.set_swing_pid(ez::RIGHT_SWING, 120, 80);
  chassis.wait_drive();
  chassis.set_drive_pid(-56, 127);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::LEFT_SWING, 90, 127);
  chassis.wait_drive();
  chassis.set_drive_pid(-130, 127);
  chassis.wait_drive();
  // chassis.set_turn_pid(90,127);
  // chassis.wait_drive();
  // chassis.set_drive_pid(-80,127);
  // chassis.wait_drive();
  rightWing.set_value(!rightWing.get_value());
  chassis.set_swing_pid(LEFT_SWING, 65, 127);
  chassis.wait_drive();
  chassis.set_drive_pid(-30,127);
  chassis.wait_drive();
  chassis.set_turn_pid(0, 127); // change from left swing
  chassis.wait_drive();
  chassis.set_drive_pid(-100,127);
  chassis.wait_until(-25);
  chassis.set_drive_pid(40,127);
  chassis.wait_drive();
  chassis.set_drive_pid(-100,127);
  chassis.wait_until(-32);
  chassis.set_swing_pid(RIGHT_SWING, 40, 127);
  chassis.wait_drive();
  chassis.set_drive_pid(35,127);
  chassis.wait_drive();
  leftWing.set_value(!leftWing.get_value());
  chassis.set_drive_pid(-100,127);
  chassis.wait_until(-40);
}