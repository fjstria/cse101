#------------------------------------------------------------------------------
#  Makefile
#  Makefile for Dictionary ADT
#
#  make                		makes Order and WordFrequency
#  make DictionaryTest      make DictionaryTest
#  make clean          		removes binary files
#  make check1         		runs valgrind on DictionaryTest
#  make check2         		runs valgrind on Order with in5 junk5
#  make check3				runs valgrind on WordFrequency with GutenBerg.txt
#------------------------------------------------------------------------------

All : Order WordFrequency

Order : Order.o Dictionary.o
	g++ -std=c++17 -Wall -o Order Order.o Dictionary.o 

Order.o : Dictionary.h Order.cpp
	g++ -std=c++17 -Wall -c Order.cpp

WordFrequency : WordFrequency.o Dictionary.o
	g++ -std=c++17 -Wall -o WordFrequency WordFrequency.o Dictionary.o 

WordFrequency.o : Dictionary.h WordFrequency.cpp
	g++ -std=c++17 -Wall -c WordFrequency.cpp

DictionaryTest : DictionaryTest.o Dictionary.o
	g++ -std=c++17 -Wall -o DictionaryTest DictionaryTest.o Dictionary.o 

DictionaryTest.o : Dictionary.h DictionaryTest.cpp
	g++ -std=c++17 -Wall -c DictionaryTest.cpp

Dictionary.o : Dictionary.h Dictionary.cpp
	g++ -std=c++17 -Wall -c Dictionary.cpp

clean :
	rm -f Order Order.o WordFrequency WordFrequency.o DictionaryTest DictionaryTest.o Dictionary.o

check1 : DictionaryTest
	valgrind --leak-check=full DictionaryTest

check2 : Order
	valgrind --leak-check=full Order in5 junk5

check3 : WordFrequency
	valgrind --leak-check=full WordFrequency GutenBerg.txt

