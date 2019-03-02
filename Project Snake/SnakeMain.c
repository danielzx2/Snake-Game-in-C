//

#include <pic32mx.h>
#include <stdint.h>
#include "SnakeHeader.h"
void *stdin, *stdout;
 /*int for later in the program*/
int gameOver = 0;

/*Booleans för deras nurvarande riktning*/
int is_left = 1;
int is_right = 0;
int is_up = 0;
int is_down = 0;

int *left = &is_left;
int *right = &is_right;
int *up = &is_up;
int *down = &is_down;

//Fetches the input from the 4 buttons in the i/o shield
int getbtns(void)
{
    int btn = 0x00;
    btn =  ((PORTD >> 4) & 0x0E) | ((PORTF >> 1) & 0x01) ;
    return btn;
}

//initialization of the 4 buttons in the i/o shield.
//Tagen från filerna i Labb 3
void labinit( void )
{
  volatile int* trise = (volatile int*) 0xbf886100;
  *trise = *trise & 0xfff1;
  TRISDSET = 0x0FE0;
  TRISFSET = 0x02;

  T2CON = 0x070; /*Sets our prescaling to 256 and selects the internal clock.*/
  TMR2 = 0; /*Resets the clock to 0.*/
  PR2 = 0x7A12; /*The value of our pre-scaling*/

  IPC(2) = 0x1f; /*Sets the priority of the Interrupt*/
  IPC(2) = IPC(2) | 0x1c000000;
  IEC(0) = 0x0900; /*Enables interrupt for Timer2 and SW2*/
  IFSCLR(0) = 0x0900; /*Sets the Interrupt flag to 0.*/

  T2CONSET = 0x08000;
  asm volatile("ei");
  return;
}

//Interrupt Service Routine (Tagen från Labb 3)
void user_isr( void )
{
  if (IFS(0) & 0x100)
  {
      advanceSnake(left, right, up, down);
  }
  
  gameOver = isgameover();
  IFS(0) = 0;
  return;
}

//Startar programmet. 
int main(void) {
/* Set up peripheral bus clock */ //PLL output dividerat med 8??
OSCCON &= ~0x180000;
OSCCON |= 0x080000;

/* Set up output pins */
AD1PCFG = 0xFFFF;   //AD1PC kontrollerar analoga port pins (sätts till digitalt) HELP
ODCE = 0x0;					//Configurerar om den specifika I/O pin ska agera normalt som digital output eller som en "open-drain" HELP
TRISECLR = 0xFF;		//OM TRIS-E rensas så kommer outpit nivån att konverteras av en analog enhet
PORTE = 0x0;				//alla pins i PORT-E sätts till output och ? alla pins (konfgurerade som analoga inputs) rensas ? HELP

/* Output pins for display signals */
PORTF = 0xFFFF;			//Sätter alla pins i PORT-F till att ta emot data
PORTG = (1 << 9);		//bit 9 ska skriva ut data
ODCF = 0x0;					//liknar ODCE
ODCG = 0x0;					//liknar ODCE
TRISFCLR = 0x70;		//bit 6-4 sätts till outputs i Port-F
TRISGCLR = 0x200;		//bit 9 sätts till output i port-g

/* Set up input pins */
TRISDSET = (1 << 8);	//bit 8 i tris-d blir en input
TRISFSET = (1 << 1);	//bit 1 i tris-f blir en input

/* Set up SPI as master */
SPI2CON = 0;					//Alla bits i spi2 = 0
SPI2BRG = 4;					//Baud rate = 4 (Ska dividera SCK)

/* Clear SPIROV*/
SPI2STATCLR &= ~0x40;	//Ny data har tagits emot men slängs bort, programmer har ej läst förra datan (liknar IFS(0) )
/* Set CKP = 1, MSTEN = 1; */
SPI2CON |= 0x60;	//D.v.s enheten blir mastern och data utbyte sker vid rising edge

/* Turn on SPI */
SPI2CONSET = 0x8000;
//Allt ovanför detta meningen är tagen från hello display i github

/* Instansierar display, interrupts, skapar ny orm och genererar första maten */
display_init();
labinit();
SnakeStart();
generateFood();

/* Kör spelet, om maten äts så skapas ny mat på slumpmässig koordinat */
while(gameOver == 0)
{
      cleanSnake();
      drawFrame();
      drawSnake();
      drawFood();
      sendData();

			/* generera ny mat, förläng orm och öka antalet poäng */
      if(eatenFood())
      {
        expandSnake();
				generateFood();
				PORTE += 1;
      }

}

display_string(1, "			GAME OVER			");
display_update();
for(;;) ;
return 0;
}
