#include <iostream>
#include <ncurses.h>
#include <vector>
#include <string>
#include <string.h>

int main(int argc, char **argv){
    WINDOW *window;
    int number_of_cells = argc - 1; // coordinates are inputs form user so far
    int board[LINES][COLS];
   
    for (int i = 0;i < LINES; i++){
        for(int j = 0; j < COLS; j++){
            board[i][j] = 0;
        }
    }


    initscr();
    printw("isso foi\n");
    for (int i = 0; i < LINES;i++){
        for (int j = 0; j < COLS;j++){
            printw("%d\n", board[i][j]);
        }
    }

    refresh();
    getch();
    endwin();
    return EXIT_SUCCESS;
}
