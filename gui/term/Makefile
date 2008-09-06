
COMPILER=g++
INCLUDE=-I../../include/gui/term/ -I../../include/gui/ -I../../include/socket/

test: 
	$(COMPILER) -g $(INCLUDE) -combine ../../socket/SkaarSocket.cpp TerminalGUI.cpp Test.cpp -o test

clean:
	@rm test

.PHONY: test clean
