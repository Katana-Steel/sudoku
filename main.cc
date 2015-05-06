#include <ncurses.h>
#include <iostream>

int board(void);

int main() {
 if(!initscr()) {
  std::cout << "error 1" << std::endl;
  return 0;
 }
 start_color();
 if(!has_colors()) {
  endwin();
  std::cout << "error 2" << std::endl;
  return 0;
 }
 noecho();
 nonl();
 nodelay(stdscr,FALSE);
 clear();
 board();
 echo();
 endwin();
 return 0;
}
