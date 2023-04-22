CXX=clang++

# User defined variables. 
# Example: make OTHER_FLAGS="-g -DDEBUG=1"
OTHER_FLAGS=

CXXFLAGS=-std=c++11 ${OTHER_FLAGS} 

STATICS=\
	BitOps.o

main.out: main.cpp $(STATICS) 
	$(CXX) -o $@ $< $(LINKS) $(CXXFLAGS) $(STATICS)

.PHONY: clean

clean:
	rm -f *.o *.so *.out
