#include <stdint.h>
#include <pic32mx.h>
#include "SnakeHeader.h"
#include <stdlib.h>

#define SNAKEMAP_SIZE 512

void delay(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

////slå ihop till en enda
uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 0x01));
	return SPI2BUF;
}

void sendData(void) {
	int i;
	for(i = 0; i < SNAKEMAP_SIZE; i++) {
		spi_send_recv(snakeMap[i]);
	}
}

int randomNumberGeneratorX(void)
{
	int n;
	int random;
	int randomnumber = (random ^ n) % 127;
	return randomnumber;
}

int randomNumberGeneratorY(void)
{
	int m;
	int random;
	int randomnumber = (random ^ m) % 31;
	return randomnumber;
}

void generateFood()
{	int x = randomNumberGeneratorX();
	int y = randomNumberGeneratorY();

	food[0].x = x;
	food[0].y = y;
	food[1].x = x + 1;
	food[1].y = y;
	food[2].x = x;
	food[2].y = y + 1;
	food[3].x = x + 1;
	food[3].y = y + 1;

	int i;
	for(i = 0; i < 4; i++)
	{
		food[i].ON = 1;
	}
}

int is_validPoint(int x, int y)/*Checks if the appointed coordinate is an actual point on the display.*/
{
	if (x < 128 && y < 32 && !(x < 0) && !(y < 0) ) {
		return 1;
	}

	else
		return 0;
}

///förklara helt  visa förståelse
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

void cleanSnake(void)
{
	int x;
	for(x = 0; x < SNAKEMAP_SIZE; x++)
	{
		snakeMap[x] = 0;
	}
}

void display_init() {
	DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK;
	delay(10);
	DISPLAY_VDD_PORT &= ~DISPLAY_VDD_MASK;
	delay(1000000);

	spi_send_recv(0xAE);
	DISPLAY_RESET_PORT &= ~DISPLAY_RESET_MASK;
	delay(10);
	DISPLAY_RESET_PORT |= DISPLAY_RESET_MASK;
	delay(10);

	spi_send_recv(0x8D);
	spi_send_recv(0x14);

	spi_send_recv(0xD9);
	spi_send_recv(0xF1);

	DISPLAY_VBATT_PORT &= ~DISPLAY_VBATT_MASK;
	delay(10000000);

	spi_send_recv(0xA1);
	spi_send_recv(0xC8);

	spi_send_recv(0xDA);
	spi_send_recv(0x20);

	spi_send_recv(0x20);
	spi_send_recv(0x0);

	spi_send_recv(0xAF);

	TRISDSET = 0x0FE0;
  TRISFSET = 0x02;

	PORTFSET = 0x10;
}
