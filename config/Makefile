
COMPILER=g++
INCLUDE=../include/config/

test: 
	$(COMPILER) -g -I$(INCLUDE) -I../include/tools/stringtokenizer/ -combine ../tools/stringtokenizer/StringTokenizer.cpp \
			Config.cpp ConfigSection.cpp Test.cpp -o test

clean:
	@rm test
	@rm skaar.conf*

.PHONY: test clean
