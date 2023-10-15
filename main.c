#include <fcntl.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char **argv) {
  int board[LINES][COLS];
  printf("%d\n", COLS);
  for (int i = 0; i < LINES; i++) {
    for (int j = 0; j < COLS; j++) {
      board[i][j] = 0;
    }
  }

  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL) {
    perror("Error while opening input file\n");
    exit(EXIT_FAILURE);
  }

  char line_buffer[BUFFER_SIZE];
  while (fgets(line_buffer, sizeof(line_buffer), fp) != NULL) {
    int c0 = atoi(strtok(line_buffer, ","));
    int c1 = atoi(strtok(NULL, ","));
    board[c0][c1] = 1;
  }
  fclose(fp);

  for (int i = 0; i < LINES; i++) {
    for (int j = 0; j < COLS; j++) {
      printf("%d\n", board[i][j]);
    }
  }
  printf("ooooi\n");
  exit(0);

  initscr();

  refresh();
  getch();
  endwin();
  return EXIT_SUCCESS;
}
