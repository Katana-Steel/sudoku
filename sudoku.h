#ifndef __sudoku_h
#define __sudoku_h

#include <vector>

class sudoku {
  int *b;
  bool box(int x,int y,int v);
  bool col(int x,int y,int v);
  bool row(int x,int y,int v);
  void pass(int i);
  int cbox(int d,int v,int &x,int &y);

  sudoku& operator=(const sudoku& old) {};
  sudoku(const sudoku& old) {};
public:
  sudoku();
  ~sudoku();

  void complete(void);
  void clear(void);
  bool ins(int x,int y,int v);
  bool test(int x,int y,int v);
  char get(int x,int y);
  char get_raw(int x,int y);
};

#endif
