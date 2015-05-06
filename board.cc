#include <ncurses.h>
#include "sudoku.h"

void doku_grid(WINDOW *win);
void draw_board(WINDOW *win,sudoku *b);
void draw_blocked(WINDOW *win,sudoku *b,int v);

int board(void) {
 keypad(stdscr, TRUE);
 sudoku *B = new sudoku();
 int cc;
 init_pair(1,COLOR_YELLOW,COLOR_BLUE);
 WINDOW *b = derwin(stdscr,13,13,0,0);
 wattron(b, COLOR_PAIR(1));
 wbkgd(b,' '|b->_attrs);
 wclear(b);
 box(b,0,0);
 doku_grid(b);
 int cy=0,cx=0,v=0;
 int y=1,x=1;
 wmove(b,y,x);
 wrefresh(b);
 while(cc != 'q') {
  v = 0;
  switch(cc) {
  case 1:
   cc = 'q';
   continue;
  case 'd':
   cc = KEY_DC;
   B->clear();
   continue;
  case KEY_UP:
   if(cy!=0) cy--;
   y = ((cy/3)*4) + (cy%3) + 1;
   break;
  case KEY_DOWN:
   if(cy!=8) cy++;
   y = ((cy/3)*4) + (cy%3) + 1;
   break;
  case KEY_LEFT:
   if(cx!=0) cx--;
   x = ((cx/3)*4) + (cx%3) + 1;
   break;
  case KEY_RIGHT:
   if(cx!=8) cx++;
   x = ((cx/3)*4) + (cx%3) + 1;
   break;
  case '9':
   v++;
  case '8':
   v++;
  case '7':
   v++;
  case '6':
   v++;
  case '5':
   v++;
  case '4':
   v++;
  case '3':
   v++;
  case '2':
   v++;
  case '1':
   v++;
   if(B->ins(cx,cy,v)) {
    mvwaddch(b,y,x,A_BOLD|cc);
   } else {
    mvwaddch(b,y,x,A_STANDOUT|cc);
   }
   break;
  case ' ':
   B->ins(cx,cy,0);
   mvwaddch(b,y,x,cc);
   break;
  case 'c':
   B->complete();
  case KEY_DC:
   wclear(b);
   box(b,0,0);
   doku_grid(b);
   draw_board(b,B);
   break;
  case 'w':
   //draw_board(b,B);
   wmove(b,1,1);
   draw_blocked(b,B,B->get_raw(cx,cy));
   break;
  }
  wmove(b,y,x);
  wrefresh(b);
  cc = getch();
 }
 delete B;
 delwin(b);
 return 0;
}

void doku_grid(WINDOW *win) {
 mvwaddch(win,0,4,ACS_TTEE);
 mvwaddch(win,0,8,ACS_TTEE);
 mvwaddch(win,12,4,ACS_BTEE);
 mvwaddch(win,12,8,ACS_BTEE);
 mvwaddch(win,4,0,ACS_LTEE);
 mvwaddch(win,8,0,ACS_LTEE);
 mvwaddch(win,4,12,ACS_RTEE);
 mvwaddch(win,8,12,ACS_RTEE);
 chtype hl = win->_attrs | ACS_HLINE;
 chtype vl = win->_attrs | ACS_VLINE;
 chtype xc = win->_attrs | ACS_PLUS;
 chtype hline[] = { hl,hl,hl,xc,hl,hl,hl,xc,hl,hl,hl };
 mvwaddchstr(win,4,1,hline);
 mvwaddchstr(win,8,1,hline);
 for(int i=0;i<3;i++) {
  mvwaddch(win,1+i,4,vl);
  mvwaddch(win,1+i,8,vl);
  mvwaddch(win,5+i,4,vl);
  mvwaddch(win,5+i,8,vl);
  mvwaddch(win,9+i,4,vl);
  mvwaddch(win,9+i,8,vl);
 }
}

void draw_board(WINDOW *win,sudoku *b) {
 chtype ch[] = { win->_attrs|' ',
                 win->_attrs|'1'|A_BOLD,
                 win->_attrs|'2'|A_BOLD,
                 win->_attrs|'3'|A_BOLD,
                 win->_attrs|'4'|A_BOLD,
                 win->_attrs|'5'|A_BOLD,
                 win->_attrs|'6'|A_BOLD,
                 win->_attrs|'7'|A_BOLD,
                 win->_attrs|'8'|A_BOLD,
                 win->_attrs|'9'|A_BOLD };
 int x=0,y=0;
 for(y=0;y<9;y++) {
  for(x=0;x<9;x++) {
   mvwaddch(win,((y/3)*4) + (y%3) + 1,((x/3)*4) + (x%3) + 1,ch[b->get_raw(x,y)]);
  }
 }
}

void draw_blocked(WINDOW *win,sudoku *b,int v){ 
 if(v>9 || v<1) return;
chtype ch[] = { win->_attrs|' ',
                 win->_attrs|'1'|A_BOLD,
                 win->_attrs|'2'|A_BOLD,
                 win->_attrs|'3'|A_BOLD,
                 win->_attrs|'4'|A_BOLD,
                 win->_attrs|'5'|A_BOLD,
                 win->_attrs|'6'|A_BOLD,
                 win->_attrs|'7'|A_BOLD,
                 win->_attrs|'8'|A_BOLD,
                 win->_attrs|'9'|A_BOLD };
 for(int y=0;y<9;y++) {
  for(int x=0;x<9;x++) {
   if(!b->test(x,y,v)) {
    mvwaddch(win,((y/3)*4) + (y%3) + 1,((x/3)*4) + (x%3) + 1,'n');
   }
  }
 }
}
