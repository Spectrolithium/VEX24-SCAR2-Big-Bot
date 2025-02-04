#include "main.h"

/////
// For installation, upgrading, documentations and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

#define CATA_BOT true
// Chassis constructor
#if CATA_BOT //to be done

  //chassis motors
    // #define RIGHT_MOTOR_1_PORT 10
    // #define RIGHT_MOTOR_2_PORT 7 //reverse
    // #define RIGHT_MOTOR_3_PORT 8
    // #define RIGHT_MOTOR_4_PORT 9 //reverse

    // #define LEFT_MOTOR_1_PORT 1 //reverse
    // #define LEFT_MOTOR_2_PORT 2 
    // #define LEFT_MOTOR_3_PORT 3 //reverse
    // #define LEFT_MOTOR_4_PORT 4

  // //sensors
    // // #define INERTIAL_PORT 19 //why do we not have imu here yet
    
    // #define ROTATION_PORT 5
    
    // #define CATA_RADAR_PORT 16
ez::Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is used as the sensor
  {-1, 2, -3, 4}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is used as the sensor
  ,{10, -7, 8, -9}

  // IMU Port
  ,15

  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
  ,3.25

  // Cartridge RPM
  ,600

  // External Gear Ratio (MUST BE DECIMAL) This is WHEEL GEAR / MOTOR GEAR
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 84/36 which is 2.333
  // eg. if your drive is 60:36 where the 36t is powered, your RATIO would be 60/36 which is 0.6
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 36/60 which is 0.6
  ,1.6667
);
#else
ez::Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is used as the sensor
  {-11, 12, -13, 14}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is used as the sensor
  ,{15, -16, 17, -18}

  // IMU Port
  ,1

  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
  ,3.25

  // Cartridge RPM
  ,600

  // External Gear Ratio (MUST BE DECIMAL) This is WHEEL GEAR / MOTOR GEAR
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 84/36 which is 2.333
  // eg. if your drive is 60:36 where the 36t is powered, your RATIO would be 60/36 which is 0.6
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 36/60 which is 0.6
  ,1.6667
);
#endif


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D
  ez::ez_template_print();
  
  pros::delay(500); // Stop the user from doing anything while legacy ports configure

  // Configure your chassis controls
  chassis.opcontrol_curve_buttons_toggle(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.opcontrol_drive_activebrake_set(0); // Sets the active brake kP. We recommend 0.1.
  chassis.opcontrol_curve_default_set(0, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  default_constants(); // Set the drive to your own constants from autons.cpp!

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.opcontrol_curve_buttons_left_set (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  // chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.autons_add({
    Auton("Example Drive\n\nDrive forward and come back.", drive_example),
    Auton("Example Turn\n\nTurn 3 times.", turn_example),
    Auton("Drive and Turn\n\nDrive forward, turn, come back. ", drive_and_turn),
    Auton("Drive and Turn\n\nSlow down during drive.", wait_until_change_speed),
    Auton("Swing Example\n\nSwing in an 'S' curve", swing_example),
    Auton("Combine all 3 movements", combining_movements),
    Auton("Interference\n\nAfter driving forward, robot performs differently if interfered or not.", interfered_example),
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
  master.rumble(".");
}



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}



/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}



/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.pid_targets_reset(); // Resets PID targets to 0
  chassis.drive_imu_reset(); // Reset gyro position to 0
  chassis.drive_sensor_reset(); // Reset drive sensors to 0
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency

  ez::as::auton_selector.selected_auton_call(); // Calls selected auton from autonomous selector
}



/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  // This is preference to what you like to drive on
  chassis.drive_brake_set(MOTOR_BRAKE_COAST);

#if CATA_BOT
  //update this

    // //cata and intake
    // #define INTAKE_RIGHT_PORT 20
    // #define INTAKE_LEFT_PORT 11 //reverse

    // #define CATA_RIGHT_PORT 19
    // #define CATA_LEFT_PORT 12

    // //climb - not used for cata
    // // #define CLIMB_MOTOR_PORT 20

    // //wings
    // #define FRONT_WINGS_PORT 'G' //or H?
    // #define BACK_WINGS_PORT 'F' // or E?

  pros::Motor intake_right_motor(20);
  pros::Motor intake_left_motor(11, true); 
  pros::Motor_Group intake = pros::Motor_Group({intake_right_motor, intake_left_motor});

  pros::Motor cata_right_motor(19);
  pros::Motor cata_left_motor(12, true);
  pros::Motor_Group cata = pros::Motor_Group({cata_right_motor, cata_left_motor});

  pros::ADIDigitalOut frontWings('G');
  pros::ADIDigitalOut backWings('F');

  bool frontWingsDeployed = false;
  bool backWingsDeployed = false;
#else
  pros::Motor climb_motor1(19);
  pros::Motor climb_motor2(20, true);
  pros::Motor_Group climb = pros::Motor_Group({climb_motor1, climb_motor2});

  pros::ADIDigitalOut climbPiston('A');
  pros::ADIDigitalOut frontWings('B');
  bool frontWingsDeployed = false;

#endif

  
  while (true) {
    
    // PID Tuner
    // After you find values that you're happy with, you'll have to set them in auton.cpp
    if (!pros::competition::is_connected()) { 
      // Enable / Disable PID Tuner
      //  When enabled: 
      //  * use A and Y to increment / decrement the constants
      //  * use the arrow keys to navigate the constants
      if (master.get_digital_new_press(DIGITAL_X)) 
        chassis.pid_tuner_toggle();
        
      // Trigger the selected autonomous routine
      if (master.get_digital_new_press(DIGITAL_B)) 
        autonomous();

      chassis.pid_tuner_iterate(); // Allow PID Tuner to iterate
    } 

    // chassis.opcontrol_tank(); // Tank control
    chassis.opcontrol_arcade_standard(ez::SPLIT); // Standard split arcade
    // chassis.opcontrol_arcade_standard(ez::SINGLE); // Standard single arcade
    // chassis.opcontrol_arcade_flipped(ez::SPLIT); // Flipped split arcade
    // chassis.opcontrol_arcade_flipped(ez::SINGLE); // Flipped single arcade

    #if CATA_BOT //cata bot controls
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
			frontWingsDeployed = !frontWingsDeployed;
			frontWings.set_value(frontWingsDeployed);
		}
		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
			backWingsDeployed = !backWingsDeployed;
			backWings.set_value(backWingsDeployed);
		}

    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)){
      intake = 80;
    }
    else if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)){
      intake = -80;
    }
    else{
      intake = 0;
    }

    //cata code goes here 
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)){
      cata = 127;
    }
    else{
      cata = 0;
    }

    #else //u bot controls

    //climb rotate
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)){
      climb = 40;
    }
    else if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)){
      climb = -40;
    }
    else{
      climb = 0;
    }

    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)){
      climbPiston.setValue(true);
    }
    else if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)){
      climbPiston.setValue(false);
    }
    //wings
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
			frontWingsDeployed = !frontWingsDeployed;
			frontWings.set_value(frontWingsDeployed);
		}

    #endif

    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
