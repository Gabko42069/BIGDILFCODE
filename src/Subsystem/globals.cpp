#include "main.h"
#include "pros/adi.h"
#include "pros/motors.h"
#include "lemlib/api.hpp"

pros ::Motor leftFront(leftFrontPort, pros ::E_MOTOR_GEARSET_06,true);
pros ::Motor leftMiddle(leftMiddlePort, pros ::E_MOTOR_GEARSET_06,true);
pros ::Motor leftBack(leftBackPort, pros ::E_MOTOR_GEARSET_06,true);

pros ::Motor rightFront(rightFrontPort, pros ::E_MOTOR_GEARSET_06);
pros ::Motor rightMiddle(rightMiddlePort, pros ::E_MOTOR_GEARSET_06);
pros ::Motor rightBack(rightBackPort, pros ::E_MOTOR_GEARSET_06);

pros ::Motor intake(intakePort, pros ::E_MOTOR_GEARSET_06);
pros ::Motor cata(cataPort, pros ::E_MOTOR_GEARSET_06, true);
pros ::Controller controller(pros ::E_CONTROLLER_MASTER);

pros ::ADIPort limitswitch(limitswitchPort, pros::E_ADI_DIGITAL_IN); // limit switch 
pros ::ADIPort leftWing(leftWingPort, pros::E_ADI_DIGITAL_OUT);
pros ::ADIPort rightWing(rightWingPort, pros::E_ADI_DIGITAL_OUT); // piston 
pros ::ADIPort backWing(backWingPort, pros::E_ADI_DIGITAL_OUT);
pros ::ADIPort arm(armPort, pros::E_ADI_DIGITAL_OUT);
pros ::ADIPort elevation(elevationPort, pros::E_ADI_DIGITAL_OUT);
pros ::Optical colorSensor(opticPort);
pros::Imu inertial(inertialPort);

pros::MotorGroup left_side_motors({leftFront,leftMiddle,leftBack});
pros::MotorGroup right_side_motors({rightFront,rightMiddle, rightBack});

lemlib::Drivetrain_t drivetrain = {
    &left_side_motors,
    &right_side_motors,
    12,
    4,
    300
    //80
    };

lemlib::OdomSensors_t sensors = {
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    &inertial};
lemlib::ChassisController_t lateralController = {
    .45,
    5,
    3,
    100,
    7,
    500,
    5};
lemlib::ChassisController_t angularController = {
    3.9,
    36,
    3,
    100,
    7,
    500,
    5};
