#include "main.h"
#include "pros/adi.h"
#include "pros/motors.h"

pros ::Motor leftFront(leftFrontPort, pros ::E_MOTOR_GEARSET_06,true);
pros ::Motor leftMiddle(leftMiddlePort, pros ::E_MOTOR_GEARSET_06,true);
pros ::Motor leftBack(leftBackPort, pros ::E_MOTOR_GEARSET_06,true);

pros ::Motor rightFront(rightFrontPort, pros ::E_MOTOR_GEARSET_06);
pros ::Motor rightMiddle(rightMiddlePort, pros ::E_MOTOR_GEARSET_06);
pros ::Motor rightBack(rightBackPort, pros ::E_MOTOR_GEARSET_06);

pros ::Motor intake(intakePort, pros ::E_MOTOR_GEARSET_06);
pros ::Motor cata(cataPort, pros ::E_MOTOR_GEARSET_06, true);
pros ::Controller controller(pros ::E_CONTROLLER_MASTER);

pros ::ADIPort limitswitch(limitswitchPort, ADI_DIGITAL_IN); // limit switch 
pros ::ADIPort leftWing(leftWingPort, ADI_DIGITAL_OUT);
pros ::ADIPort rightWing(rightWingPort, ADI_DIGITAL_OUT); // piston 
pros ::ADIPort backWing(backWingPort, ADI_DIGITAL_OUT);
pros ::ADIPort arm(armPort, ADI_DIGITAL_OUT);
pros ::ADIPort elevation(elevationPort, ADI_DIGITAL_OUT);
pros ::Optical colorSensor(opticPort);