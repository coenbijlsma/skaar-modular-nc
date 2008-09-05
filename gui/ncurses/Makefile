
COMPILER=g++
INCLUDE=-I../../include/gui/ncurses/ -I../../include/gui/

test: 
	$(COMPILER) -g $(INCLUDE) -combine ScreenBuffer.cpp Screen.cpp Test.cpp -lpanel -lncurses -o test

clean:
	@rm test

.PHONY: test clean
