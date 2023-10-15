#include <fcntl.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define CELL_CHARACTER 'o'
#define SLEEP_TIME 100000

const int neighbours[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                              {0, 1},   {1, -1}, {1, 0},  {1, 1}};

int main(int argc, char **argv) {

  int LINES, COLS;
  initscr();
  curs_set(0);
  cbreak();
  noecho();
  getmaxyx(stdscr, COLS, LINES);
  mousemask(BUTTON1_PRESSED | BUTTON3_PRESSED, NULL);
  keypad(stdscr, TRUE);

  int board[LINES][COLS];

  for (int i = 0; i < LINES; i++) {
    for (int j = 0; j < COLS; j++) {
      board[i][j] = 0;
    }
  }

  MEVENT event;
  int mousech;
  while ((mousech = getch()) != 's') {
    if (mousech == KEY_MOUSE) {
      if (getmouse(&event) == OK) {

        if (event.bstate & BUTTON1_PRESSED) {
          board[event.x][event.y] = 1;
          mvaddch(event.y, event.x, CELL_CHARACTER);
        } else if (event.bstate & BUTTON3_PRESSED) {
          board[event.x][event.y] = 0;
          mvdelch(event.y, event.x);
        }
        refresh();
      }
    }
  }

  int new_board[LINES][COLS];
  for (int i = 0; i < LINES; i++) {
    for (int j = 0; j < COLS; j++) {
      new_board[i][j] = 0;
    }
  }

  int ch;
  for (;;) {

    clear();
    refresh();

    // display
    for (int i = 0; i < LINES; i++) {
      for (int j = 0; j < COLS; j++) {
        if (board[i][j]) {
          mvaddch(j, i, CELL_CHARACTER);
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

    if ((ch = getch()) == 'q') {
      break;
    }

    usleep(SLEEP_TIME);
  }

  endwin();
  return EXIT_SUCCESS;
}
