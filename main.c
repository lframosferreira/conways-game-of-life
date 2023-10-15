#include <fcntl.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

const int neighbours[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                              {0, 1},   {1, -1}, {1, 0},  {1, 1}};

int main(int argc, char **argv) {

  int LINES, COLS;
  initscr();
  curs_set(0);
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  getmaxyx(stdscr, COLS, LINES);
  mousemask(ALL_MOUSE_EVENTS, NULL);

  MEVENT event;
  char mousech;
  while ((mousech = getch()) != 's') {
    if (mousech == KEY_MOUSE) {
      if (getmouse(&event) == OK) {
        if (event.bstate & BUTTON1_PRESSED) {
          printw("Left mouse button pressed at (%d, %d)", event.x,
                   event.y);
          refresh();
        }
      }
    }
  }

  int board[LINES][COLS];

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

  int new_board[LINES][COLS];
  for (int i = 0; i < LINES; i++) {
    for (int j = 0; j < COLS; j++) {
      new_board[i][j] = 0;
    }
  }

  char ch;
  for (;;) {

    clear();
    refresh();

    // display
    for (int i = 0; i < LINES; i++) {
      for (int j = 0; j < COLS; j++) {
        if (board[i][j]) {
          mvaddch(j, i, 'o');
        }
      }
    }

    // check neighbourhood status for each cell and store in the new board
    int count;
    for (int i = 0; i < LINES; i++) {
      for (int j = 0; j < COLS; j++) {
        count = 0;
        for (int k = 0; k < 8; k++) {
          int neighbour_coord_x = i + neighbours[k][0];
          int neighbour_coord_y = j + neighbours[k][1];
          count += board[neighbour_coord_x][neighbour_coord_y];
        }
        if (board[i][j]) {
          if (count < 2 || count > 3) {
            new_board[i][j] = 0;
          } else {
            new_board[i][j] = 1;
          }

        } else {
          if (count == 3) {
            new_board[i][j] = 1;
          }
        }
      }
    }

    // pass info from new board to current board and sets new board all back to
    // 0

    for (int i = 0; i < LINES; i++) {
      for (int j = 0; j < COLS; j++) {
        board[i][j] = new_board[i][j];
        new_board[i][j] = 0;
      }
    }

    if ((ch = getch()) == 'q') { // tenho q apertas 'q' duas vzs, tem algo zuado
      break;
    }

    usleep(100000);
  }

  endwin();
  return EXIT_SUCCESS;
}
