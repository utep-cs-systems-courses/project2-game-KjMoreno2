#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"


int oddPress1 = 0;
int oddPress2 = 0;
int oddPress3 = 0;
int oddPress4 = 0;

void __interrupt_vec(WDT_VECTOR) WDT () {
  static int count = 0;
  int dimState = 0;

  count++;


  if ((count % 63) == 0 && oddPress1 == 1){
    led_update();
    playSong();
    count = 0;
   
  }
  else if((count % 125) == 0 && oddPress2 == 1){
    led_update();
    playSong2();
    count = 0;
  }
  else if ((count % 125) == 0 && oddPress3 == 1){
    led_update();
    playSong3();
    count = 0;
  }
  else if ((count % 32) == 0 && oddPress4 == 1){
    buzzer_set_period(0);  
    dim_sequence();
    count = 0;
  }
}
