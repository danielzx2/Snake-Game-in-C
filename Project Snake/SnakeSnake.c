//Denna fill hanterar ormen i spelet och instansieringen av mat

#include <stdint.h>
#include <pic32mx.h>
#include "SnakeHeader.h"
void *stdin, *stdout;

/* slumpvalt värde för funktionen rand(), tail räknar ormens totala segment */
// För att generera slumpmässiga koordinater används
int randi = 734;
int tail = 9;

/* Skapar en ny orm */
void SnakeStart(){
  int i;

  for(i=0; i < (tail + 1); i++){
      snake[i].x = STARTX - i;
      snake[i].y = STARTY;
      snake[i].ON = 1;
  }
}

/* Får ormen att börja gå, parametrarna beskriver ormens färdriktning
   och används för att bestämma den riktning ormen kommer färda. */
void advanceSnake(int* is_left, int* is_right, int* is_up, int* is_down)
{
  randi++;
  int x;
  int y;
  int adv;

	for(adv = tail; adv > 0; adv--)
		snake[adv] = snake[adv-1];

	for(adv = SNAKE_LENGTH; adv > tail; adv--)
		snake[adv].ON = 0;

  /* Ormen roterar motsols */
	if(getbtns() == 8)
	{
    if(*is_left)
		{
			*is_left = 0;
			*is_up = 1;
		}

    else if(*is_up)
    {
      *is_up = 0;
      *is_right = 1;
    }

    else if(*is_right)
    {
      *is_right = 0;
      *is_down = 1;
    }

    else if(*is_down)
    {
      *is_down = 0;
      *is_left = 1;
    }
	}

  /* Ormen roterar medsols */
	if(getbtns() == 4)
	{
		if(*is_left)
		{
			*is_down = 1;
			*is_left = 0;
		}

    else if (*is_down)
    {
      *is_down = 0;
      *is_right = 1;
    }

    else if(*is_right)
    {
      *is_right = 0;
      *is_up = 1;
    }

    else if(*is_up)
    {
      *is_up = 0;
      *is_left = 1;
    }
	}

  /* Beroende på ormens tidigare rutt så fortsätter den sin riktning */
	if(*is_left)
		snake[0].x = snake[0].x + 1;
	else if(*is_right)
		snake[0].x = snake[0].x - 1;
	else if(*is_up)
		snake[0].y = snake[0].y - 1;
	else if(*is_down)
		snake[0].y = snake[0].y + 1;
}

/* Ritar ut maten i displayen med hjälp av generatepixel */
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
    randi++;
	}
}

/* Skapar maten i form av 2x2 pixel */
//nya slumpmässiga koordinater genereras tills de passar
void generateFood(){
  int x,y;

  do{
  x = (rand() + randi) % 126;
  y = (rand() + randi) % 30;
  }while( !(is_validPoint(x,y)) && x > 8 && y > 8);

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
      randi++;
	  }
	  drawFood();
}

/* Ritar ut spelplanen i displayen */
void drawFrame(){
  int i;
  for(i = 0; i < 128; i++){
    generatePixel(i, 1);
    generatePixel(i, 2);
    generatePixel(i, 30);
    generatePixel(i, 31);
  }

  for(i = 0; i < 32; i++){
    generatePixel(1, i);
		generatePixel(2, i);
    generatePixel(126, i);
    generatePixel(127, i);
    generatePixel(128, i);

  }
}

/* ritar ut ormen i spelet */
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

/* Får ormen att växa OM ormen äter mat*/
void expandSnake(void)
{
  int newbody = tail + 1;
  snake[newbody].x = snake[tail].x - 1;
  snake[newbody].y = snake[tail].y;
	snake[newbody].ON = 1;
  drawSnake();
  tail++;
}

/* Undersöker om ormen äver en del av maten */
int eatenFood(void)
{
  if(snake[0].x == food[0].x && snake[0].y == food[0].y)
    return 1;

	if (snake[0].x == food[1].x && snake[0].y == food[1].y)
		return 1;

	if (snake[0].x == food[2].x && snake[0].y == food[2].y)
	  return 1;

	if (snake[0].x == food[3].x && snake[0].y == food[3].y)
	  return 1;

	 else
	  return 0;

    randi++;
}

/* Undersöker om ormen kolliderar med väggen eller med sig själv*/
int isgameover(void)
{
    int i;
		if(snake[0].x == 2 || snake[0].x == 126 || snake[0].y == 2 || snake[0].y == 30)
			return 1;

		for(i = 3; i <= tail; i++)
      if(snake[0].x == snake[i].x && snake[0].y == snake[i].y)
        return 1;

    return 0;
}
