#include "2048.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void _W_NOT_MERGE(int map[MAP_SIZE][MAP_SIZE], int *moved);
static void _A_NOT_MERGE(int map[MAP_SIZE][MAP_SIZE], int *moved);
static void _S_NOT_MERGE(int map[MAP_SIZE][MAP_SIZE], int *moved);
static void _D_NOT_MERGE(int map[MAP_SIZE][MAP_SIZE], int *moved);

// 地图正在向上操作
int W(int map[MAP_SIZE][MAP_SIZE]) {
  int moved = false;
  // printf("W is detected!\n");
  int i, j;
  _W_NOT_MERGE(map, &moved);
  // Merge any pairs
  for (j = 0; j < MAP_SIZE; j++) {
    for (i = 1; i < MAP_SIZE; i++) {
      if (map[i][j] != 0 && map[i][j] == map[i - 1][j]) {
        map[i - 1][j] += map[i][j];
        map[i][j] = 0;
        moved = true;
      }
    }
  }
  _W_NOT_MERGE(map, &moved);
  return moved;
}

// 向上填充，但不合并相同的数字
static void _W_NOT_MERGE(int map[MAP_SIZE][MAP_SIZE], int *moved) {
  int i, j;
  for (j = 0; j < MAP_SIZE; j++) {
    for (i = 1; i < MAP_SIZE; i++) {
      if (map[i][j] != 0) {
        int row = i;
        while (row > 0 && map[row - 1][j] == 0) {
          row--;
        }
        if (row != i) {
          map[row][j] = map[i][j];
          map[i][j] = 0;
          *moved = true;
        }
      }
    }
  }
}

// 地图正在向左操作
int A(int map[MAP_SIZE][MAP_SIZE]) {
  int moved = false;
  int i, j;
  _A_NOT_MERGE(map, &moved);
  // Merge any pairs
  for (i = 0; i < MAP_SIZE; i++) {
    for (j = 1; j < MAP_SIZE; j++) {
      if (map[i][j] != 0 && map[i][j] == map[i][j - 1]) {
        map[i][j - 1] += map[i][j];
        map[i][j] = 0;
        moved = true;
      }
    }
  }
  _A_NOT_MERGE(map, &moved);
  return moved;
}

// 向左填充，但不合并相同的数字
static void _A_NOT_MERGE(int map[MAP_SIZE][MAP_SIZE], int *moved) {
  int i, j;
  for (i = 0; i < MAP_SIZE; i++) {
    for (j = 1; j < MAP_SIZE; j++) {
      if (map[i][j] != 0) {
        int col = j;
        while (col > 0 && map[i][col - 1] == 0) {
          col--;
        }
        if (col != j) {
          map[i][col] = map[i][j];
          map[i][j] = 0;
          *moved = true;
        }
      }
    }
  }
}

// 地图正在向下操作
int S(int map[MAP_SIZE][MAP_SIZE]) {
  int moved = false;
  int i, j;
  _S_NOT_MERGE(map, &moved);
  // Merge any pairs
  for (j = 0; j < MAP_SIZE; j++) {
    for (i = MAP_SIZE - 2; i >= 0; i--) {
      if (map[i][j] != 0 && map[i][j] == map[i + 1][j]) {
        map[i + 1][j] += map[i][j];
        map[i][j] = 0;
        moved = true;
      }
    }
  }
  _S_NOT_MERGE(map, &moved);
  return moved;
}

// 向下填充，但不合并相同的数字
static void _S_NOT_MERGE(int map[MAP_SIZE][MAP_SIZE], int *moved) {
  int i, j;
  for (j = 0; j < MAP_SIZE; j++) {
    for (i = MAP_SIZE - 2; i >= 0; i--) {
      if (map[i][j] != 0) {
        int row = i;
        while (row < MAP_SIZE - 1 && map[row + 1][j] == 0) {
          row++;
        }
        if (row != i) {
          map[row][j] = map[i][j];
          map[i][j] = 0;
          *moved = true;
        }
      }
    }
  }
}

// 地图正在向右操作
int D(int map[MAP_SIZE][MAP_SIZE]) {
  int moved = false;
  // printf("D is detected!\n");
  _D_NOT_MERGE(map, &moved);
  int i, j;
  // Merge any pairs
  for (i = 0; i < MAP_SIZE; i++) {
    for (j = MAP_SIZE - 2; j >= 0; j--) {
      if (map[i][j] != 0 && map[i][j] == map[i][j + 1]) {
        map[i][j + 1] += map[i][j];
        map[i][j] = 0;
        moved = true;
      }
    }
  }
  _D_NOT_MERGE(map, &moved);
  return moved;
}

// 向右填充，但不合并相同的数字
static void _D_NOT_MERGE(int map[MAP_SIZE][MAP_SIZE], int *moved) {
  int i, j;
  for (i = 0; i < MAP_SIZE; i++) {
    for (j = MAP_SIZE - 2; j >= 0; j--) {
      if (map[i][j] != 0) {
        int col = j;
        while (col < MAP_SIZE - 1 && map[i][col + 1] == 0) {
          col++;
        }
        if (col != j) {
          map[i][col] = map[i][j];
          map[i][j] = 0;
          *moved = true;
        }
      }
    }
  }
}

// // 随机在图上的空的位置上加入2或者4，加入4的概率由RANDOM_ADD_4_CHANCE决定
void randomAdd(int map[MAP_SIZE][MAP_SIZE]) {
  // int i, j;
  int r, c;
  int n = 2;
  time_t t;

  // if map is full, return immediatly
  if (isFullMap(map)) {
    return;
  }

  // Seed the random number generator
  srand((unsigned)time(&t));

  // Choose a random location (r, c) that is empty
  do {
    r = rand() % MAP_SIZE;
    c = rand() % MAP_SIZE;
  } while (map[r][c] != 0);

  // There is a RANDOM_ADD_4_CHANCE (now is 10% chance) chance that we will add
  // a 4 instead of a 2
  if (rand() % (int)(1 / RANDOM_ADD_4_CHANCE) == 0) {
    n = 4;
  }

  map[r][c] = n;
}

// 清空屏幕
void clear(bool clearEnable) {
  if (clearEnable) {
    system("cls");
  }
}

// 若地图上无空位返回true
bool isFullMap(int map[MAP_SIZE][MAP_SIZE]) {
  int isFull = true;
  for (int i = 0; i < MAP_SIZE; i++) {
    for (int j = 0; j < MAP_SIZE; j++) {
      if (map[i][j] == 0) {
        isFull = false;
      };
    }
  }
  return isFull;
}

// 初始化图
void initMap(int map[MAP_SIZE][MAP_SIZE]) {
  for (int i = 0; i < MAP_SIZE; i++) {
    for (int j = 0; j < MAP_SIZE; j++) {
      map[i][j] = 0;
    }
  }
  // 初始化的时候占用两个位置
  randomAdd(map);
  randomAdd(map);
}

// 打印图
void printMap(int map[MAP_SIZE][MAP_SIZE], bool printPrettyEnable,
              bool clearEnable) {
  clear(clearEnable);
  for (int i = 0; i < MAP_SIZE; i++) {
    for (int j = 0; j < MAP_SIZE; j++) {
      if (printPrettyEnable) {
        switch (map[i][j]) {
          case 0:
            printf("%*s ", MAX_DIGIT, "(x)");
            break;
          case 2:
            printf("%*s ", MAX_DIGIT, "<2>");
            break;
          case 4:
            printf("%*s ", MAX_DIGIT, ">4<");
            break;
          case 8:
            printf("%*s ", MAX_DIGIT, "!8!");
            break;
          case 16:
            printf("%*s ", MAX_DIGIT, "|16|");
            break;
          case 32:
            printf("%*s ", MAX_DIGIT, "{32}");
            break;
          case 64:
            printf("%*s ", MAX_DIGIT, "[64]");
            break;
          case 128:
            printf("%*s ", MAX_DIGIT, "#128#");
            break;
          case 256:
            printf("%*s ", MAX_DIGIT, "^256^");
            break;
          case 512:
            printf("%*s ", MAX_DIGIT, "&512&");
            break;
          case 1024:
            printf("%*s ", MAX_DIGIT, ">>>1024<<<");
            break;
          case 2048:
            printf("%*s ", MAX_DIGIT, "!!!2048!!!");
            break;
          default:
            printf("%*s ", MAX_DIGIT, "?");
            break;
        }

      } else {
        switch (map[i][j]) {
          case 0:
            printf("%*s ", MAX_DIGIT, "(x)");
            break;
          default:
            printf("%*d ", MAX_DIGIT, map[i][j]);
            break;
        }
      }
    }
    printf("\n");
  }
  printf("\n");
}

// 查看游戏的状态，若获胜返回WIN，若失败返回LOSE，若继续返回CONTINUE
int gameStat(int map[MAP_SIZE][MAP_SIZE]) {
  for (int i = 0; i < MAP_SIZE; i++) {
    for (int j = 0; j < MAP_SIZE; j++) {
      if (map[i][j] == 2048) {
        return WIN;
      }
    }
  }
  if (isFullMap(map)) {
    for (int i = 0; i < MAP_SIZE; i++) {
      for (int j = 0; j < MAP_SIZE; j++) {
        if (i + 1 < MAP_SIZE && map[i][j] == map[i + 1][j]) return CONTINUE;
        if (i - 1 > 0 && map[i][j] == map[i - 1][j]) return CONTINUE;
        if (j + 1 < MAP_SIZE && map[i][j] == map[i][j + 1]) return CONTINUE;
        if (j - 1 > 0 && map[i][j] == map[i][j - 1]) return CONTINUE;
      }
    }
    return LOSE;
  }
  return CONTINUE;
}