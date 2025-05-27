CXX=clang++

wordcount: WordCount.o lab07Test.o
	${CXX} WordCount.o lab07Test.o -o wordcount

WordCount.o: WordCount.cpp
	${CXX} -c WordCount.cpp

lab06Test.o: lab07Test.cpp
	${CXX} -c lab07Test.cpp

clean:
	/bin/rm -f *.o wordcount