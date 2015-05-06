#include "sudoku.h"


sudoku::sudoku() {
  b = new int[81];
  for(int i=0;i<81;i++) b[i] = 10;
}

sudoku::~sudoku() {
 delete[] b;
}

void sudoku::clear(void) {
  for(int i=0;i<81;i++) b[i] = 10;
}

void sudoku::complete(void) {
 for(int i=0;i<18;i++){
  for(int j=i%9;j>=0;j--) {
   pass(j+1);
  }
 }
}

void sudoku::pass(int i){
  int c;
  int x=0,y=0;
  for(int r=0;r<9;r++) {
    c = cbox(r,i,x,y);
    if(c==1) ins(x,y,i);
  }
}

int sudoku::cbox(int d, int v,int &x,int &y) {
  int c=0;
  int x_y=0;
  int q = d%3;
  int m = -1;
  int sy = d/3*3;
  for(int i=0;i<9;i++) {
    if(i%3 == 0) m++;
    x_y = q*3+(m+sy)*9+i%3;
    if(b[x_y] == 10 && col(x_y%9,x_y/9,v) 
&& row(x_y%9,x_y/9,v)) { 
      if(b[x_y] == v) return 0;
      c++; 
      x=x_y%9; 
      y=x_y/9; 
    }
  }
  return c;
}

bool sudoku::box(int x, int y, int v) {
  int d = (x/3+((y/3)*3));
  int p = (x%3+((y%3)*3));
  int q = d%3;
  int m = -1;
  int sy = (y/3)*3;
  for(int i=0;i<9;i++) {
    if(i%3 == 0) m++;
    if(i==p) continue;
    if(b[q*3+(m+sy)*9+i%3] == v) return false;
  }
  return true;
}

bool sudoku::col(int x, int y, int v) {
  for(int i=0;i<9;i++) {
    if(i==y) continue;
    if(b[x+9*i] == v) return false;
  }
  return true;
}

bool sudoku::row(int x, int y, int v) {
  for(int i=0;i<9;i++) {
    if(i==x) continue;
    if(b[y*9+i] == v) return false;
  }
  return true;
}

bool sudoku::ins(int x, int y, int v) {
  if(x>8) return false;
  if(y>8) return false;
  if(v==0) {
    b[x+(y*9)] = 10;
    return true;
  }
  if(!box(x,y,v)) return false;
  if(!col(x,y,v)) return false;
  if(!row(x,y,v)) return false;
  b[x+(y*9)] = v;
  return true;
}

bool sudoku::test(int x, int y, int v) {
  if(x>8) return false;
  if(y>8) return false;
  if(v==0) {
    return true;
  }
  if(!box(x,y,v)) return false;
  if(!col(x,y,v)) return false;
  if(!row(x,y,v)) return false;
  return true;
}

char sudoku::get(int x, int y) {
 if(x>8 || y>8) return -1;
 char ret = get_raw(x,y);
 if(ret == 0) return ' ';
 return ret+48;
}

char sudoku::get_raw(int x, int y) {
 if(x>8 || y>8) return -1;
 return (b[x+(y*9)] == 10) ? 0 : b[x+(y*9)];
}
