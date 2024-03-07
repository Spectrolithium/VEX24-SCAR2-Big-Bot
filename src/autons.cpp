#include "main.h"

/////
// For installation, upgrading, documentations and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 110;  
const int TURN_SPEED = 70;
const int SWING_SPEED = 90;

///
// Constants
///
void default_constants() {
  chassis.pid_heading_constants_set(3, 0, 20);
  chassis.pid_drive_constants_set(10, 0, 100);
  chassis.pid_turn_constants_set(3, 0, 20);
  chassis.pid_swing_constants_set(5, 0, 30);

  chassis.pid_turn_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  chassis.pid_swing_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  chassis.pid_drive_exit_condition_set(300_ms, 1_in, 500_ms, 3_in, 750_ms, 750_ms);

  chassis.slew_drive_constants_set(7_in, 80);
}

///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches

   ez::Piston backWings('H');

  // bool frontWingsDeployed = false;
  bool backWingsDeployed = false;

  backWingsDeployed = !backWingsDeployed;
	backWings.set(backWingsDeployed);
  chassis.pid_wait();
  pros::delay(1000);

  //take triball out and wait to retract wings

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  backWingsDeployed = !backWingsDeployed;
	backWings.set(backWingsDeployed);
  chassis.pid_wait();

  // get into position to push triball in

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(18_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  //push triball in and come backwards

  chassis.pid_drive_set(20_in, 127, true);
  chassis.pid_wait();

  chassis.pid_drive_set(-6_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //try to push triball in again

  chassis.pid_drive_set(12_in, 127, true);
  chassis.pid_wait();

  chassis.pid_drive_set(-4_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //turn to face middle bar and run into it

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-70_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //rotate so intake faces bar and push into it

  chassis.pid_drive_set(10_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-8_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Turn Example
// this is actually our SKILLS AUTON
///
void turn_example() {
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at

  pros::Motor intake(10);

  pros::Motor scoop(1);
  int scoop_speed = 127;
  int scoop_interval = -900;
  int scoop_target_position = scoop_interval;

  int scoop_delay = 1000;
  int wings_delay = 900;

  ez::Piston backWings('H');

  //deploy wings

  bool backWingsDeployed = false;

  backWingsDeployed = !backWingsDeployed;
	backWings.set(backWingsDeployed);
  chassis.pid_wait();
  pros::delay(wings_delay);

  //scoop five triballs out

  scoop.move_absolute(scoop_target_position, scoop_speed);
  scoop_target_position = scoop_target_position + scoop_interval;
  pros::delay(scoop_delay);

  scoop.move_absolute(scoop_target_position, scoop_speed);
  scoop_target_position = scoop_target_position + scoop_interval;
  pros::delay(scoop_delay);

  scoop.move_absolute(scoop_target_position, scoop_speed);
  scoop_target_position = scoop_target_position + scoop_interval;
  pros::delay(scoop_delay);

  scoop.move_absolute(scoop_target_position, scoop_speed);
  scoop_target_position = scoop_target_position + scoop_interval;
  pros::delay(scoop_delay);

  scoop.move_absolute(scoop_target_position, scoop_speed);
  scoop_target_position = scoop_target_position + scoop_interval;
  pros::delay(scoop_delay);
  
  //retract wings to prepare for push

  backWingsDeployed = !backWingsDeployed;
	backWings.set(backWingsDeployed);
  chassis.pid_wait();
  pros::delay(wings_delay);

  //turn and push the triballs every five scoops

  chassis.pid_drive_set(-6_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-96_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //return to starting position

  chassis.pid_drive_set(96_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED); //remember that degrees is absolute, i.e. 0 deg is starting position
  chassis.pid_wait();

  chassis.pid_drive_set(6_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //deploy wings for scoop

  backWingsDeployed = !backWingsDeployed;
	backWings.set(backWingsDeployed);
  chassis.pid_wait();
  pros::delay(wings_delay);

  //scoop five triballs out

  scoop.move_absolute(scoop_target_position, scoop_speed);
  scoop_target_position = scoop_target_position + scoop_interval;
  pros::delay(scoop_delay);

  scoop.move_absolute(scoop_target_position, scoop_speed);
  scoop_target_position = scoop_target_position + scoop_interval;
  pros::delay(scoop_delay);

  scoop.move_absolute(scoop_target_position, scoop_speed);
  scoop_target_position = scoop_target_position + scoop_interval;
  pros::delay(scoop_delay);

  scoop.move_absolute(scoop_target_position, scoop_speed);
  scoop_target_position = scoop_target_position + scoop_interval;
  pros::delay(scoop_delay);

  scoop.move_absolute(scoop_target_position, scoop_speed);
  scoop_target_position = scoop_target_position + scoop_interval;
  pros::delay(scoop_delay);


}

///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // pid_wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 30
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(6_in);
  chassis.pid_speed_max_set(30);  // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 30 speed
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 30
  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(-6_in);
  chassis.pid_speed_max_set(30);  // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 30 speed
  chassis.pid_wait();
}

///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();
}

///
// Auto that tests everything
///
void combining_movements() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees.
// If interfered, robot will drive forward and then attempt to drive backwards.
void interfered_example() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}

// . . .
// Make your own autonomous functions here!
// . . .