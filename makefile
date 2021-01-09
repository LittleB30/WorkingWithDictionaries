CC=g++
CFLAGS=-std=c++11
all:Dictionary SpellingChecker spellingTest
	$(CC) $(CFLAGS) Dictionary.o SpellingChecker.o spellingTest.o -o out
Dictionary:Dictionary.cpp
	$(CC) $(CFLAGS) -c Dictionary.cpp
SpellingChecker:SpellingChecker.cpp
	$(CC) $(CFLAGS) -c SpellingChecker.cpp
spellingTest:spellingTest.cpp
	$(CC) $(CFLAGS) -c spellingTest.cpp
clean:
	rm *.o out