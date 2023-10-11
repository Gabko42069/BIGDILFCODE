#include "main.h"
#include "pros/misc.h"

void controlPistons()
{
    if(controller.get_digital_new_press(DIGITAL_Y))
    {
        arm.set_value(!arm.get_value());
    }
    else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B))
    {
        elevation.set_value(!elevation.get_value());
    }
    else if (controller.get_digital_new_press(DIGITAL_A)) 
    {
        rightWing.set_value(!rightWing.get_value());
        leftWing.set_value(!leftWing.get_value());
    }
    else if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X))
    {
        backWing.set_value(!backWing.get_value());
    }
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT))
    {
        rightWing.set_value(!rightWing.get_value());
    }
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT))
    {
        leftWing.set_value(!leftWing.get_value());
    }
}