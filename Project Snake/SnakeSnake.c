#include <stdint.h>
#include <pic32mx.h>
#include "SnakeHeader.h"



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

      //gameOver = 0;
  }
}

void drawFrame()
{
  int i;
  for(i = 0; i < 128; i++)
  {
    generatePixel(i, 0);
    generatePixel(i, 1);

    generatePixel(i, 30);
    generatePixel(i, 31);
  }

  for(i = 0; i < 32; i++)
  {
    generatePixel(0, i);
    generatePixel(1, i);

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
