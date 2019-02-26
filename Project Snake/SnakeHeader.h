//This header file is used for the snake game, designed for the uno 32 chipkit and basic i/o shield
//Made by Abyel Tesfay and Daniel Nyeko Moini

#include <stdlib.h>
#include <stdint.h>

#define SnakeBody 100
#define STARTY 15
#define STARTX 45
int is_left = 0;
int is_right = 1;
int is_up = 2;
int is_down = 3;

uint8_t snakeMap[512];

int is_validPoint(int x, int y);
void generatePixel(int x, int y);
void cleanSnake(void);

typedef struct {
    int x;
    int y;
    int ON;
} pixel;

//The max body for snake
pixel snake[50];
pixel food[4];
