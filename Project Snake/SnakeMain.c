#include <pic32mx.h>
#include <stdint.h>
#include "SnakeHeader.h"
void *stdin, *stdout;
 /*int for later in the program*/
int gameOver = 0;

uint8_t  wall[] = {
0, 0, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252,
252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252,
252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252,
252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 0, 0,

0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0,

0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0,

0, 0, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 0, 0,
};

//Fetches the input from the 4 buttons in the i/o shield
int getbtns(void)
{
    int btn = 0x00;
    btn =  ((PORTD >> 4) & 0x0E) | ((PORTF >> 1) & 0x01) ;
    return btn;
}

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
SPI2CON |= 0x60;	//D.v.s eneheten blir mastern och data utbyte sker vid rising edge

/* Turn on SPI */
SPI2CONSET = 0x8000;

display_init();
//display_update();
SnakeStart();
generateFood();
drawFrame();
drawSnake();
drawFood();
sendData();


while(1)
{
    while(gameOver == 0)
    {
        if()
				{
					clearFood(); /*Tar bort maten*/
					expandSnake();/*Gör att ormen växer. Kolla SnakeSnake för fulla funktionen*/
				}

    }

}



while(1)
 {

   cleanSnake();
   drawSnake();
   drawFrame();
   sendData();


 }

for(;;) ;
return 0;
}
