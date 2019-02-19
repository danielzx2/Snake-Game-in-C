/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;
volatile int* TRISE = (volatile int*) 0xbf886100;
volatile int* PORTE = (volatile int*) 0xbf886110;
char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  *TRISE = *TRISE & 0xff00; //uppgift C
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  TRISD = 0xf01f;   // upgift E
  *PORTE = 0x0000;  //uppgift D
  delay( 1000 );
  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  tick( &mytime );

  *PORTE = *PORTE + 1; //uppgift D
  display_image(96, icon);
}
