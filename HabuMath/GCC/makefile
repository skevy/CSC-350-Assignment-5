#Can use "-MM" to make dependecy list

#Include files path
INCLUDE = ../Include/

#Source files path 
SOURCE = ../Source/

#Debug output path
DEBUG_PATH = Debug/

#Release output path
RELEASE_PATH = Release/

#Release Optimization
OPT = -O

#Release Binary Name
RELEASE_NAME = FibonacciRel.out

#Release Binary Name
DEBUG_NAME = FibonacciDebug.out

debug: Fibonacci.do Main.do
	g++ -o $(DEBUG_PATH)a.out -g -lpthread $(DEBUG_PATH)Main.o $(DEBUG_PATH)Fibonacci.o

release: Fibonacci.o Main.o
	g++ -o $(RELEASE_PATH)a.out -lpthread $(RELEASE_PATH)Main.o $(RELEASE_PATH)Fibonacci.o  

Fibonacci.do: $(INCLUDE)Fibonacci.hpp $(SOURCE)Fibonacci.cpp
	g++ -o $(DEBUG_PATH)Fibonacci.o -Wall -c -g -DLINUX -D_REENTRANT -I$(INCLUDE) $(SOURCE)Fibonacci.cpp 

Main.do: $(SOURCE)Main.cpp
	g++ -o $(DEBUG_PATH)Main.o -Wall -c -g -DLINUX -D_REENTRANT -I$(INCLUDE) $(SOURCE)Main.cpp 

Fibonacci.o: $(INCLUDE)Fibonacci.hpp $(SOURCE)Fibonacci.cpp
	g++ -o $(RELEASE_PATH)Fibonacci.o -c -DLINUX -D_REENTRANT -I$(INCLUDE) $(SOURCE)Fibonacci.cpp

Main.o: $(SOURCE)Main.cpp
	g++ -o $(RELEASE_PATH)Main.o -c -DLINUX -D_REENTRANT -I$(INCLUDE) $(SOURCE)Main.cpp
