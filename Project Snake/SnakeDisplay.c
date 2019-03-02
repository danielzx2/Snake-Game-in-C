//Denna fil hanterar displayen i basic i/o shield

#include <stdint.h>
#include <pic32mx.h>
#include "SnakeHeader.h"
void *stdin, *stdout;

//Följande defineringar är tagna från "hello display" i github
#define DISPLAY_VDD_PORT PORTF
#define DISPLAY_VDD_MASK 0x40
#define DISPLAY_VBATT_PORT PORTF
#define DISPLAY_VBATT_MASK 0x20
#define DISPLAY_COMMAND_DATA_PORT PORTF
#define DISPLAY_COMMAND_DATA_MASK 0x10
#define DISPLAY_RESET_PORT PORTG
#define DISPLAY_RESET_MASK 0x200

//egna defineringar
#define FOOD_VECTOR_SIZE 4
#define SNAKEMAP_SIZE 512

void delay(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

//skickar data till display via SPI protokoll
uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 0x01));
	return SPI2BUF;
}

//skickar hela vektorn "snakemap", som är en 8-bit int vektorn
//där varje element styr 8 pixlar

//inspirerat av https://github.com/GioTro/Snake-for-uno32-devBoard/tree/master/Project
void sendData(void) {
	int i;
	for(i = 0; i < SNAKEMAP_SIZE; i++) {
		spi_send_recv(snakeMap[i]);
	}
}

//skriver ut textsträng i display
void display_string(int line, char *s) {
	int i;
	if(line < 0 || line >= 4)
		return;
	if(!s)
		return;

	for(i = 0; i < 16; i++)
		if(*s) {
			textbuffer[line][i] = *s;
			s++;
		} else
			textbuffer[line][i] = ' ';
}

//uppdaterar displayen
void display_update() {
	int i, j, k;
	int c;
	for(i = 0; i < 4; i++) {
		DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK;
		spi_send_recv(0x22);
		spi_send_recv(i);

		spi_send_recv(0x0);
		spi_send_recv(0x10);

		DISPLAY_COMMAND_DATA_PORT |= DISPLAY_COMMAND_DATA_MASK;

		for(j = 0; j < 16; j++) {
			c = textbuffer[i][j];
			if(c & 0x80)
				continue;

			for(k = 0; k < 8; k++)
				spi_send_recv(font[c*8 + k]);
		}
	}
}

//Checks if the appointed coordinate is an actual point on the display. https://github.com/GioTro/Snake-for-uno32-devBoard/tree/master/Project
int is_validPoint(int x, int y)
{
	if (x < 128 && y < 32 && x > 0 && y > 0) {
		return 1;
	}
}

//Draws a pixel in a specific coordinate on the screen. Function found at https://github.com/GioTro/Snake-for-uno32-devBoard/tree/master/Project
void generatePixel(int x, int y)
{
	if(is_validPoint(x, y) == 1)
	{
		int range = y % 8; /*Determines which pixel of within the 8 bits are used.*/
		int row = y / 8;	/*Which out of the 4 rows will the point generate on.*/
		int des = row*128+x; /*The determined index of the pixel.*/
		snakeMap[des] = snakeMap[des] | (0x01 << range); /*we shift the value of "range" by 1  so that bits 1-7 can be used properly*/
	}
}

//Removes the snake from the screen
void cleanSnake(void){
	int x;
	for(x = 0; x < SNAKEMAP_SIZE; x++)
	{
		snakeMap[x] = 0;
	}
}

//Initializes the display. This 
void display_init() {
	DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK; //stänger av portf pin 4?
	delay(10);
	DISPLAY_VDD_PORT &= ~DISPLAY_VDD_MASK; //sätter på ström till logik
	delay(1000000);

	spi_send_recv(0xAE); //set display ON
	DISPLAY_RESET_PORT &= ~DISPLAY_RESET_MASK; //stänger av SPI
	delay(10);
	DISPLAY_RESET_PORT |= DISPLAY_RESET_MASK;  //Sätter på SPI
	delay(10);

	spi_send_recv(0x8D); 	//Charge pump settings
	spi_send_recv(0x14);	//Enable charge pump (ökar strömmen från låg till hög?)

	spi_send_recv(0xD9);	//Set the duration of pre-charge period
	spi_send_recv(0xF1); 	//??

	DISPLAY_VBATT_PORT &= ~DISPLAY_VBATT_MASK; //sätter på ström till display
	delay(10000000);

	spi_send_recv(0xA1);  	 //Set segment remap??
	spi_send_recv(0xC8); 	 //Set output COM scan direction??

	spi_send_recv(0xDA);	 //com pins hardware config (styr displayen somewhat)
	spi_send_recv(0x20);	 //page addressing mode

	spi_send_recv(0x20);     //??
	spi_send_recv(0x0);

	spi_send_recv(0xAF); 	 //display ON
	delay(100);

  DISPLAY_COMMAND_DATA_PORT |= DISPLAY_COMMAND_DATA_MASK;
}
