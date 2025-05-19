CXX=clang++

wordcount: WordCount.o lab06Test.o
	${CXX} WordCount.o lab06Test.o -o wordcount

WordCount.o: WordCount.cpp
	${CXX} -c WordCount.cpp

lab06Test.o: lab06Test.cpp
	${CXX} -c lab06Test.cpp

clean:
	/bin/rm -f *.o wordcount