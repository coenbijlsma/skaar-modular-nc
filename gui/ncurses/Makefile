
COMPILER=g++
INCLUDE=-I../../include/gui/ncurses/ -I../../include/gui/ -I../../include/socket/

test: 
	$(COMPILER) -g $(INCLUDE) -combine ../../socket/SkaarSocket.cpp ScreenBuffer.cpp Screen.cpp Test.cpp -lpanel -lncurses -o test

clean:
	@rm test

.PHONY: test clean
