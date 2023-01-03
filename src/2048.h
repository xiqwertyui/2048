

#ifndef GAME2048_H
#define GAME2048_H

#include <stdbool.h>

#define MAX_DIGIT 4  // 2048 is 4 digit, you'd better set here greater than 4
#define PRETTY_MAX_DIGIT 6

#define UP 'w'
#define LEFT 'a'
#define DOWN 's'
#define RIGHT 'd'

#define WIN 0
#define LOSE 1
#define CONTINUE 2

#define MAP_SIZE 4
#define RANDOM_ADD_4_CHANCE 0.1

void clear(bool clearEnable);
void initMap(int map[MAP_SIZE][MAP_SIZE]);
void printMap(int map[MAP_SIZE][MAP_SIZE], bool printPrettyEnable,
              bool clearEnable);
void randomAdd(int map[MAP_SIZE][MAP_SIZE]);

// 朝4个方位移动的操作函数
int W(int map[MAP_SIZE][MAP_SIZE]);
int A(int map[MAP_SIZE][MAP_SIZE]);
int S(int map[MAP_SIZE][MAP_SIZE]);
int D(int map[MAP_SIZE][MAP_SIZE]);

bool isFullMap(int map[MAP_SIZE][MAP_SIZE]);

int gameStat(int map[MAP_SIZE][MAP_SIZE]);

#endif
