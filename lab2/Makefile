#
# Makefile för sorteringslösning
#

CCC	= g++ -std=c++17 -O3 -Wall -Wextra

all: encrypt decrypt brute

brute: brute.cpp key.o
	$(CCC) $(LFLAGS) -o brute brute.cpp key.o

encrypt: encrypt.cpp key.o
	$(CCC) $(LFLAGS) -o encrypt encrypt.cpp key.o

decrypt: decrypt.cpp key.o
	$(CCC) $(LFLAGS) -o decrypt decrypt.cpp key.o

key.o: key.cpp key.h
	$(CCC) $(LDFLAGS) -c key.cpp

clean:
	@ \rm -rf *.o *.gch core

zap: clean
	@ \rm -f brute encrypt decrypt *~
