#include "cat.hpp"
#include "PID.hpp"
#include "intake.hpp"
#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "util.hpp"


pros::ADIDigitalIn catLim ('C');
//pros::ADIAnalogIn catPot ('B');
pros::Motor cat (1, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);



bool cat_btn = false;
bool load = false;
bool ready_to_fire = false;
bool pressed_once = false;
int wait_after_fire = 0;
int cat_time = 0;
//bool expan_btn = false;
//bool going_down = false;
//bool lim_pressed = false;

e_cat state = winding;
void set_state(e_cat _state){
 state = _state;
}
e_cat get_state() {
 return state;
}

void cat_control() {

 if (get_state() == winding) {
  //if catapult isn't pressing the lim, wind the catapult back
  cat.move(127);
  if (catLim.get_value() == 1) {
  //once the catapult hits the limit switch, the cat is primed and needs to stop
   set_state(primed);
   }
  }

 if (get_state() == primed) {
 //cat is primed so stop motor
  cat.move(0);
  }
    
 if (get_state() == fire) {
 //fire the catapult
  cat.move(127);
  if (wait_after_fire <= 400) {
   wait_after_fire += util::DELAY_TIME;
  } else {
  //sets state after delay
   wait_after_fire = 0;
   set_state(winding);
   }
  }
    
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && cat_btn == false) {
   if (get_state() == primed) { 
   //if cat is primed, cat can be fired
    set_state(fire);
    cat_btn = true;
    }
   } else if (!master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
      cat_btn = false;

}


void fire_cat_auton() {
 if (load) {
  ready_to_fire = true;
  cat.move(127);
  pros::delay(400);
  pressed_once = false;
 }
}


void catTask() {
 while(1) {      
  if (pros::competition::is_autonomous()) {
   if (catLim.get_value() == 0 && pressed_once == false) {
    printf("pressed");
    load = false;
    ready_to_fire = false;
    cat.move(100);
   }
   else {
    if (ready_to_fire == false) {
    pressed_once = true;
    load = true;
    cat.move(0);
    }
   }    
  }      
  pros::delay(util::DELAY_TIME);
 }
} pros::Task cat_task(catTask);


