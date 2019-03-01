#include <stdint.h>
#include <pic32mx.h>
#include "SnakeHeader.h"
void *stdin, *stdout;

int randi = 234234;
int tail = 9;

/*Booleans för deras kommande riktningar*/

srand(int(randi));

/*Boolean values to determine directions*/

int randomNumberGeneratorX(void)
{
	int randomnumber = rand() % 126;
  randi++;
	return randomnumber;
}

int randomNumberGeneratorY(void){
	int randomnumber = rand() % 30;
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

  for(i=0; i < 10; i++){
      snake[i].x = STARTX - i;
      snake[i].y = STARTY;
      snake[i].ON = 1;
  }
}

void advanceSnake(int* is_left, int* is_right, int* is_up, int* is_down)
{
  int x;
  int y;
  int adv;

	for(adv = tail; adv > 0; adv--)
	{
		snake[adv] = snake[adv-1];
	}

	for(adv = SNAKE_LENGTH; adv > tail; adv--)
	{
		snake[adv].ON = 0;
	}



	if(getbtns() == 8)
	{
		PORTE += 1;

		if(*is_left)
		{
			snake[0].y = snake[0].y - 1;
			*is_up = 1;
			*is_left = 0;
		}

		if(*is_right)
		{
			snake[0].y = snake[0].y + 1;
			*is_down = 1;
			*is_right = 0;
		}

		if(*is_up)
		{
			snake[0].x = snake[0].x - 1;
			*is_left = 1;
			*is_up = 0;
		}

		if(*is_down)
		{
			snake[0].x = snake[0].x + 1;
			*is_left = 1;
			*is_down =	0;
		}
	}

	else if(getbtns() == 4)
	{
		if(*is_left)
		{
			snake[0].y = snake[0].y + 1;
			*is_down = 1;
			*is_left = 0;
		}

		if(*is_right)
		{
				snake[0].y = snake[0].y - 1;
				*is_up = 1;
				*is_right = 0;
		}

		if(*is_up)
		{
			snake[0].x = snake[0].x + 1;
			*is_left = 1;
			*is_up = 0;
		}

		if(*is_down)
		{
			snake[0].x = snake[0].x - 1;
			*is_right = 1;
			*is_down = 0;
		}
	}

	if(*is_left)
		snake[0].x = snake[0].x + 1;
	if(*is_right)
		snake[0].x = snake[0].x - 1;
	if(*is_up)
		snake[0].y = snake[0].y - 1;
	if(*is_down)
		snake[0].y = snake[0].y + 1;

}

void drawFood()
{
	int x;
	int y;
	int k;
	for(k = 0; k < FOOD_VECTOR_SIZE; k++)
	{
		x = food[k].x;
		y = food[k].y;

		generatePixel(x, y);
	}
}

void generateFood(){
	int x = 60;
	int y = 15;
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
	drawFood();
}

void drawFrame(){
  int i;
  for(i = 0; i < 128; i++){
    generatePixel(i, 2);
    generatePixel(i, 1);

    generatePixel(i, 30);
    generatePixel(i, 31);
  }

  for(i = 0; i < 32; i++){
    generatePixel(1, i);
		generatePixel(2, i);

    generatePixel(126, i);
    generatePixel(127, i);
  }
}


void drawSnake(void)
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

void expandSnake(void)
{
  int newbody = tail + 1;
  snake[newbody].x = snake[tail].x - 1;
  snake[newbody].y = snake[tail].y;
	snake[newbody].ON = 1;
  drawSnake();

  tail++;
}

/*
while (snake[u].x != turnPoint)
{
	if(*is_left)
	{
		snake[u].x = snake[u].x + 1;
	}

	if(*is_right)
	{
		snake[u].x = snake[u].x - 1;
	}
}

x = snake[u].x;
y = snake[u].y - 1;
*/


void go_up()
{
	int u;
  for(u = SNAKE_LENGTH; u > 0; u--)
  {
    snake[u] = snake[u-1];
  }
	snake[0].y = snake[1].y - 1;
	snake[0].x = snake[1].x;
}

void go_down()
{
	int u;
	for(u = SNAKE_LENGTH; u > 0; u--)
  {
    snake[u].x = snake[u-1].x;
		snake[u].y = snake[u-1].y;
  }
	snake[0].y = snake[1].y + 1;
	snake[0].x = snake[1].x;
}


void go_left(int *is_up, int *is_down)
{
	int u;
	for(u = SNAKE_LENGTH; u > 0; u--)
  {
    snake[u].x = snake[u-1].x;
		snake[u].y = snake[u-1].y;
  }
	snake[0].y = snake[1].y;
	snake[0].x = snake[1].x + 1;
}

void go_right(int *is_up, int *is_down)
{
	int u;
	for(u = SNAKE_LENGTH; u > 0; u--)
  {
    snake[u].x = snake[u-1].x;
		snake[u].y = snake[u-1].y;
  }
	snake[0].y = snake[1].y;
	snake[0].x = snake[1].x - 1;
}


int eatenFood(void)
{
  if(snake[0].x == food[0].x && snake[0].y == food[0].y)
  {
    return 1;
  }

	if (snake[0].x == food[1].x && snake[0].y == food[1].y)
	 {
		return 1;
	 }

	 if (snake[0].x == food[2].x && snake[0].y == food[2].y)
	 {
	 	return 1;
	 }

	 if (snake[0].x == food[3].x && snake[0].y == food[3].y)
	  {
	 	return 1;
	  }

		else
		{
			return 0;
		}
}


int isgameover(void)
{
		if(snake[0].x == 2 || snake[0].x == 125){
			return 1;
		}

		if(snake[0].y == 2 || snake[0].y == 29){
			return 1;
		}

		else
		{
			return 0;
		}
}
