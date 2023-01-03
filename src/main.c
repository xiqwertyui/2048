#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "2048.h"

int map[MAP_SIZE][MAP_SIZE];
char command;
int moved = false;
int printPretty = false;
int clearEnable = true;

#define printMap(map) printMap(map, printPretty, clearEnable)  // 设置默认参数

void usage(void) {
  printf("======<How to start>======\n");
  printf("./main -> start 2048 game\n");
  printf("======<command line parameter>======\n");
  printf("-1, log -> log every step when gamming\n");
  printf("-p, pretty -> make the output pretty\n");
  printf("--help, help -> usage\n");
}

int main(int argc, char **argv) {
  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "log") == 0) {
      clearEnable = false;
    }
    if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "pretty") == 0) {
      printPretty = true;
    }
    if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "help") == 0) {
      usage();
      exit(0);
    }
  }
  printf("<Game start>==================================\n");
  for (initMap(map); true;) {
    printMap(map);
    printf("Input accepting (w|a|s|d): ");
    if (scanf(" %c", &command) == EOF) {
      printf("EXIT!\n");
      exit(0);
      break;
    }
    switch (command) {
      case UP:
        moved = W(map);
        break;
      case DOWN:
        moved = S(map);
        break;
      case RIGHT:
        moved = D(map);
        break;
      case LEFT:
        moved = A(map);
        break;
      default:
        printf("Invalid Input!\n");
        break;
    }
    printf("Result:\n");
    printMap(map);
    if (gameStat(map) != CONTINUE) {
      switch (gameStat(map)) {
        case WIN:
          printf("YOU WIN!!\n");
          break;
        case LOSE:
          printf("YOU LOSE!!\n");
          break;
        default:
          printf("ERROR!!\n");
          break;
      }
      printf("\nPress any key to exit\n");
      getchar();
      exit(0);
    }
    printf("<Next turn>==================================\n");
    if (moved) {  // 如果地图发生变化，随机加入一个2或者4
      randomAdd(map);
    }
  }
  
}