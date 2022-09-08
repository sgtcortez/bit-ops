CPP=clang++

CFLAGS=-g -Wall -Wextra -std=c++11
CFLAGS+=-Werror
CFLAGS+=-O0

STATICS=\
	BitOps.o

%.o: %.cpp %.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

main.out: main.cpp $(STATICS) 
	$(CPP) $(CFLAGS) -o $@ $^	

.PHONY: clean

clean:
	rm -f *.o *.so *.out
