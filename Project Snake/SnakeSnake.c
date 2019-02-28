#include <stdint.h>
#include <pic32mx.h>
#include "SnakeHeader.h"
void *stdin, *stdout;

int randi = 47389623;
int tail = 7;
srand(randi);

/*Boolean values to determine directions*/
int is_left = 1;
int is_right = 0;
int is_up = 0;
int is_down = 0;

int randomNumberGeneratorX(void)
{
	int randomnumber = rand() % 127;
  randi++;
	return randomnumber;
}

int randomNumberGeneratorY(void){
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

void generateFood(){
	int x = randomNumberGeneratorX();
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

void drawFood(){
	int x;
	int y;
	int k;
	for(k = 0; x < FOOD_VECTOR_SIZE; x++){
		x = food[k].x;
		y = food[k].y;

		generatePixel(x, y);
	}
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
  int x;
  int y;

  snake[newbody].x = snake[tail].x - 1;
  snake[newbody].y = snake[tail].y;
  drawSnake();

  tail++;
}

void go_up(void)
{
  int x;
  int y;
  int u;
  int turnPoint = snake[0].x;
  for(u = 0; u < SNAKE_LENGTH; u++)
  {
    while (snake[u].x != turnPoint)
    {
      if(is_left)
      {
        snake[u].x = snake[u].x + 1;
      }

      if(is_right)
      {
        snake[u].x = snake[u].x - 1;
      }
    }
    x = snake[u].x;
    y = snake[u].y - 1;

    generatePixel(x, y);
  }
}

void go_down(void)
{
  int x;
  int y;
  int d;
  int turnPoint = snake[0].x;
  for(d = 0; d < SNAKE_LENGTH; d++)
  {
    while(snake[d].x != turnPoint)
    {
      if(is_left)
      {
        snake[d].x = snake[d].x + 1;
      }

      if(is_right)
      {
        snake[d].x = snake[d].x - 1;
      }
    }

    x = snake[d].x;
    y = snake[d].y + 1;

    generatePixel(x, y);
  }
}

void go_left(void)
{
  int x;
  int y;
  int l;
  int turnPoint = snake[0].y;
  for(l = 0; l < SNAKE_LENGTH; l++)
  {
    while(snake[l].y != turnPoint)
    {
      if(is_up)
      {
        snake[l].y = snake[l].y - 1;
      }

      if(is_down)
      {
        snake[l].y = snake[l].y + 1;
      }
    }
    x = snake[l].x - 1;
    y = snake[l].y;

    generatePixel(x, y);
  }
}

void go_right(void)
{
  int r;
  int x;
  int y;
  int turnPoint = snake[0].y;
  for(r = 0; r < SNAKE_LENGTH; r++)
  {
    while(snake[r].y != turnPoint)
    {
      if(is_up)
      {
        snake[r].y = snake[r].y - 1;
      }

      if(is_down)
      {
        snake[r].y = snake[r].y + 1;
      }
    }

    x = snake[r].x + 1;
    y = snake[r].y;

    generatePixel(x, y);
  }
}

int eatenFood(void)
{
  if(snake[0].x == food[1].x | snake[0].x == food[2].x | snake[0].x == food[3].x | snake[0].x == food[4].x | snake[0].y == food[1].y | snake[0].x == food[2].y | snake[0].x == food[3].y | snake[0].x == food[4].y)
  {
    return 1;
  }
}

int isgameover(int *over){
	int i;
	for(i = 0; i < 32; i++){
		if(snake[i].x == 2 || snake[i].x == 126){
			*over = 1;
		 	return 1;
		}
	}
	for(i = 0; i < 128; i++){
		if(snake[i].y == 2 || snake[i].y == 30){
			*over = 1;
			return 1;
		}

		return 0;
	}
}
