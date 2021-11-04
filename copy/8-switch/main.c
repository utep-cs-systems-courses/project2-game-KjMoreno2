#include <msp430.h>
#include "libTimer.h"

#define LED_RED BIT0               // P1.0
#define LED_GREEN BIT6             // P1.6
#define LEDS (BIT0 | BIT6)


#define SW1 BIT0                /* switch1 is p1.3 */
#define SWITCHES SW1		/* only 1 switch on this board */

void main(void) 
{  
  configureClocks();

  P1DIR |= LEDS;                // sets p1dir.0 and p1dir.6 to true(output)
  P1OUT &= ~LEDS;		/* leds initially off */
  
  P1REN |= SWITCHES;		/* enables resistors for switches */
  P1IE |= SWITCHES;		/* enable interrupts from switches */
  P1OUT |= SWITCHES;		/* pull-ups for switches */
  P1DIR &= ~SWITCHES;		/* set switches' bits for input */

  or_sr(0x18);  // CPU off, GIE on
} 

void
switch_interrupt_handler()
{
  char p2_in_read = P2IN;	//0000 1000	/* switch is in P2 */

/* update switch interrupt sense to detect changes from current buttons */
  P2IES |= (p2_in_read & SWITCHES);	/* if switch up,check for transition to down */
  P2IES &= (p2_in_read | ~SWITCHES);	/* if switch down, sense up */
  // button_state = (p1val & SW1) ? 0: 1;
  // button_state (p1val & SW2) ? button_state: 2; 
/* up=red, down=green */
  if (p1_in_read & SW1) { // p2_in_read and 0000 1000
    P1OUT |= LED_RED;
    P1OUT &= ~LED_GREEN;
  } else {
    P1OUT |= LED_GREEN;
    P1OUT &= ~LED_RED;
  }
}


/* Switch on P2 (S2) */
void
__interrupt_vec(PORT1_VECTOR) Port_1(){
  if (P2IFG & SWITCHES) {	 /* did a button cause this interrupt? p1ifg is port 1 interrupt */
    P2IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}
