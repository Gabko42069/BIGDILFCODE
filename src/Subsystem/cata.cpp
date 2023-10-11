#include "main.h"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/rtos.h"
#include "pros/rtos.hpp"

bool lazyMode = false;

void setCata(double power)
{
    cata = power;
}

void controlCata()
{
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1))
    {
        pros :: Task shoot_cata(cataAysnc, TASK_PRIORITY_MIN);
    }

    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2))
    {
      pros :: Task half_down(cataBysnc, TASK_PRIORITY_MIN);
    }
  
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP))
    {
      lazyMode = !lazyMode;
    }

    if (lazyMode)
    {
      if(colorSensor.get_proximity()>= 180)
      {
        cataAysnc();
      }
    }
    
    
}

void cataAysnc()
{
  pros::delay(10);
  setCata(127);
  pros::delay(300);
  setCata(0);
  while (limitswitch.get_value() == false) {
    setCata(127);
    pros::delay(30);
  }
  setCata(0);
}

// makes it go down 
void cataBysnc() 
{
  pros::delay(10);
  setCata(127);
  pros::delay(500);
  setCata(0);
}

void opticTask()//shit
{
    if(colorSensor.get_hue() >= 219 && colorSensor.get_hue() <= 226 )
    {
     cataAysnc();
     printf("shoot");
    }
    if(colorSensor.get_hue() >= 11 && colorSensor.get_hue() <= 15 )
    {
     cataAysnc();
     printf("shoot");
    }
    if(colorSensor.get_hue() >= 83 && colorSensor.get_hue() <= 89 )
    {
     cataAysnc();
     printf("shoot");
    }
  
}
