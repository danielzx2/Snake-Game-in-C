//This header file is used for the snake game, designed for the uno 32 chipkit and basic i/o shield
//Made by Abyel Tesfay and Daniel Nyeko Moini

#include <stdlib.h>
#include <stdint.h>

#define SnakeBody 100
#define STARTY 15
#define STARTX 45
#define SNAKEMAP_LENGTH 512
#define DISPLAY_VDD PORTFbits.RF6
#define DISPLAY_VBATT PORTFbits.RF5
#define DISPLAY_COMMAND_DATA PORTFbits.RF4
#define DISPLAY_RESET PORTGbits.RG9

#define DISPLAY_VDD_PORT PORTF
#define DISPLAY_VDD_MASK 0x40
#define DISPLAY_VBATT_PORT PORTF
#define DISPLAY_VBATT_MASK 0x20
#define DISPLAY_COMMAND_DATA_PORT PORTF
#define DISPLAY_COMMAND_DATA_MASK 0x10
#define DISPLAY_RESET_PORT PORTG
#define DISPLAY_RESET_MASK 0x200

#define SNAKEMAP_SIZE 512
#define FOOD_VECTOR_SIZE 4
#define SNAKEMAP_SIZE 512

uint8_t snakeMap[512];

int is_validPoint(int x, int y);
int randomNumberGenerator(void);
void generatePixel(int x, int y);
void cleanSnake(void);
void go_left(int s, int l);
void go_right(int s, int r);
void go_up(int pos);
void go_down(int pos);
void delay(int cyc);
void generateFood();
void drawFood();
uint8_t spi_send_recv(uint8_t data);
void sendData();
void go_left(int s, int l);
void go_right(int s, int r);
void go_up(int pos);
void go_down(int pos);


typedef struct {
    int x;
    int y;
    int ON;
} pixel;

//The max body for snake
pixel snake[100];
pixel food[4];
