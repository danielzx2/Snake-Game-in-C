#include <stdint.h>
#include <pic32mx.h>
#include "SnakeHeader.h"
void *stdin, *stdout;

int randi = 47389623;
int tail = 7;
srand(randi);

int randomNumberGeneratorX(void)
{
	int randomnumber = rand() % 127;
  randi++;
	return randomnumber;
}

int randomNumberGeneratorY(void)
{
	int randomnumber = rand() % 31;
  randi++;
	return randomnumber;
}

void SnakeStart(){
  int i;
  for(i=0; i < SNAKE_LENGTH; i++){
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
  for(i = 0; i < 128; i++)
  {
    generatePixel(i, 2);
    generatePixel(i, 1);

    generatePixel(i, 30);
    generatePixel(i, 31);
  }

  for(i = 0; i < 32; i++)
  {
    generatePixel(1, i);
		generatePixel(2, i);

    generatePixel(126, i);
    generatePixel(127, i);
  }
}


void drawSnake()
{
  int x;
  int y;
  int i;
  for(i = 0; i < SNAKE_LENGTH; i++)
  {
    if(snake[i].ON == 1)
    {
      x = snake[i].x;
      y = snake[i].y;
      generatePixel(x, y);
    }
  }
 }

void expandSnake()
{
  int newbody = tail + 1;
  int x;
  int y;

  snake[newbody].x = snake[tail].x - 1;
  snake[newbody].y = snake[tail].y;
  drawSnake();

  tail++;
}

int eatenFood()
{
  if(snake[0].x == food[1].x | snake[0].x == food[2].x | snake[0].x == food[3].x | snake[0].x == food[4].x | snake[0].y == food[1].y | snake[0].x == food[2].y | snake[0].x == food[3].y | snake[0].x == food[4].y)
  {
    return 1;
  }
}
