#Bethelhem Nigat Nibret
# ID= 20170884
#Assignment 3
#File= Makefile


all: tester tester_private

tester: bst.o tester.o
	g++ -std=c++11 -o tester bst.o tester.o

tester_private: bst.o tester_private.o 
	g++ -std=c++11 -o tester_private bst.o tester_private.o

bst.o: bst.h bst.cpp
	g++ -std=c++11 -c bst.cpp

tester.o: tester.cpp
	g++ -std=c++11 -c tester.cpp

tester_private.o: tester_private.cpp
	g++ -std=c++11 -c tester_private.cpp

clean: #remove everthing with .o extension
	rm *.o tester tester_private tester.o bst.o tester_private # also remove output