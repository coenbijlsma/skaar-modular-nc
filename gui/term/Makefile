
COMPILER=g++
INCLUDE=-I../../include/gui/term/ -I../../include/gui/

test: 
	$(COMPILER) -g $(INCLUDE) -combine TerminalGUI.cpp Test.cpp -o test

clean:
	@rm test

.PHONY: test clean
