#include "main.h"
#include "pros/adi.hpp"

//Motors

extern pros :: Motor leftFront; 
extern pros :: Motor leftMiddle; 
extern pros :: Motor leftBack;
extern pros :: Motor rightFront;
extern pros :: Motor rightMiddle;
extern pros :: Motor rightBack;

extern pros :: Motor intake;
extern pros :: Motor cata;
extern pros :: Imu inertial;
extern pros :: Controller controller;

extern pros :: ADIPort leftWing;
extern pros :: ADIPort rightWing;
extern pros :: ADIPort backWing;
extern pros :: ADIPort arm;
extern pros :: ADIPort elevation; // piston 
extern pros :: ADIPort limitswitch; // limit switch
extern pros :: Optical colorSensor;


#define leftFrontPort 13
#define leftMiddlePort 12
#define leftBackPort 11
#define rightFrontPort 15
#define rightMiddlePort 16
#define rightBackPort 17 

#define intakePort 18 
#define cataPort 21 
#define inertialPort 14
#define opticPort 20

#define limitswitchPort 'D'
#define leftWingPort 'G'
#define rightWingPort 'B'
#define backWingPort 'H'
#define armPort 'A'
#define elevationPort 'E'