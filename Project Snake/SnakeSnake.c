#include <stdint.h>
#include <pic32mx.h>
#include "SnakeHeader.h"

void SnakeStart(){
  int i;
  for(i=0; i < 8; i++){
      snake[i].x = 0;
      snake[i].y = 0;
  }

  for(i=0; i < 8; i++){
      snake[i].x = STARTX + i;
      snake[i].y = STARTY;
  }
}

void FoodStart(){
  int i;
  Food[0].x =
  Food[1].x
  Food[2].x
  Food[3].x


  }
}