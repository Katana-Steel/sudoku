CXX=g++
OBJZ=main.o sudoku.o board.o

all:
	@echo "choose either 'make release' or 'make debug'"

debug: sudoku

release: sudoku clean_tmp
	@strip sudoku

sudoku: $(OBJZ)
	@echo sudoku
	@$(CXX) -g -o sudoku $(OBJZ) -lncurses

.cc.o:
	@echo $<
	@$(CXX) -c -g $<

clean: clean_tmp
	@echo Cleaning
	@rm -f sudoku

clean_tmp:
	@rm -f *.o *~