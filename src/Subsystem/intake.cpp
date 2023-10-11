#include "main.h"
#include "pros/misc.hpp"

void setIntake(int power)
{
    intake = power; 
}
// basic one motor subsytem programing 
void controlIntake() // goes in main.h 
{
    if(controller.get_digital(DIGITAL_R1))
    {
        setIntake(-127); // 127 max
    }
    else if(controller.get_digital(DIGITAL_R2))
    {
        setIntake(127);
    }
    else 
    {
        setIntake(0);
    }
}