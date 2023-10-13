#include <iostream>
#include <ncurses.h>
#include <vector>
#include <string>
#include <string.h>

int main(int argc, char **argv){
    WINDOW *window;
    int number_of_cells = argc - 1; // coordinates are inputs form user so far
    std::vector<std::pair<int, int>> cells_coord; 
    for (int i = 1; i < argc; i++){
        std::string c1 = strtok(argv[i], ",");
        std::string c2 = strtok(NULL, ",");
        cells_coord.push_back({std::stoi(c1), std::stoi(c2)});
    }
    initscr();

    for (auto e: cells_coord)
    {
        printw("%d,%d\n", e.first, e.second);
    }
    refresh();
    getch();
    endwin();
    return EXIT_SUCCESS;
}
