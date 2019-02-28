#include <stdint.h>
#include <pic32mx.h>
#include "SnakeHeader.h"
void *stdin, *stdout;

int randi = 47389623;

int randomNumberGeneratorX(void)
{
  srand(randi);
	int randomnumber = rand() % 127;
	return randomnumber;
}

int randomNumberGeneratorY(void)
{
	srand(randi);
	int randomnumber = randi % 31;
	return randomnumber;
}

void SnakeStart(){
  int i;
  for(i=0; i < 8; i++){
      snake[i].x = 0;
      snake[i].y = 0;
      snake[i].ON = 0;
  }

  for(i=0; i < 8; i++){
      snake[i].x = STARTX + i;
      snake[i].y = STARTY;
      snake[i].ON = 1;
  }
}

void generateFood()
{	int x = randomNumberGeneratorX();
	int y = randomNumberGeneratorY();
	int i;

	food[0].x = x;
	food[0].y = y;
	food[1].x = x + 1;
	food[1].y = y;
	food[2].x = x;
	food[2].y = y + 1;
	food[3].x = x + 1;
	food[3].y = y + 1;

	for(i = 0; i < 4; i++)
	{
		food[i].ON = 1;
	}
}

void drawFood()
{
	int x;
	int y;
	int k;
	for(k = 0; x < FOOD_VECTOR_SIZE; x++)
	{
		x = food[k].x;
		y = food[k].y;

		generatePixel(x, y);
	}
}

void drawFrame()
{
  int i;
  for(i = 0; i < 31; i++)
  {

    //generatePixel(0, i);
    //generatePixel(127, i);
  }

  for(i = 0; i < 127; i++)
  {
    generatePixel(i, 7);
    //generatePixel(i, 31);

  }
}

void drawSnake()
{
  int x;
  int y;
  int i;
  for(i = 0; i < SNAKEMAP_LENGTH; i++)
  {
    if(snake[i].ON == 1)
    {
      x = snake[i].x;
      y = snake[i].y;
      generatePixel(x, y);
    }
  }
 }
