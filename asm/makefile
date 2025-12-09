CFLAGS=-std=c++17

all: asm

asm: asm.o lexer.o
	$(CXX) $(CFLAGS) asm.o lexer.o -o $@

lexer.o: lexer.h lexer.cpp
	$(CXX) $(CFLAGS) -c lexer.cpp

asm.o: lexer.h asm.cpp
	$(CXX) $(CFLAGS) -c asm.cpp

clean:
	rm -f asm *.o *.bin
