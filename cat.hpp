#pragma once
#include "main.h"
#include "pros/adi.hpp"
#include "pros/motors.hpp"

extern pros::Motor cat;
extern pros::ADIDigitalIn catLim;
//extern pros::ADIAnalogIn catPot;

void on_cat(bool on);
void load_cat();
void fire_cat();
void fire_cat_auton();
void cat_control();

enum e_cat { winding = 0,
             primed = 1,
             fire = 2
};

e_cat get_state();
void set_state(e_cat _state);
/*
class Cat {
    public:
    
    Cat(int cat_motor_port);
    pros::Motor cat;
     
      * \brief enumeration for the catapult states
      
     enum e_cat { winding = 0,
                  primed = 1,
                  fire = 2 };
    
     
}; */