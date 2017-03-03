P1.out : Project1.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o
	g++ -std=c++11 -g -o P1.out Project1.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o

Project1.o : Project1.cpp SetLimits.h SyntacticalAnalyzer.h
	g++ -std=c++11 -g -c Project1.cpp

SetLimits.o : SetLimits.cpp SetLimits.h
	g++ -std=c++11 -g -c SetLimits.cpp

LexicalAnalyzer.o : LexicalAnalyzer.cpp LexicalAnalyzer.h
	g++ -std=c++11 -g -c LexicalAnalyzer.cpp

SyntacticalAnalyzer.o : SyntacticalAnalyzer.cpp SyntacticalAnalyzer.h LexicalAnalyzer.h
	g++ -std=c++11 -g -c SyntacticalAnalyzer.cpp

clean : 
	rm *.o P1.out *.gch *.lst *.dbg *.P1

submit : Project1.cpp LexicalAnalyzer.h LexicalAnalyzer.cpp SyntacticalAnalyzer.h SyntacticalAnalyzer.cpp makefile README.txt
	rm -rf TeamHP1
	mkdir TeamHP1
	cp Project1.cpp TeamHP1
	cp LexicalAnalyzer.h TeamHP1
	cp LexicalAnalyzer.cpp TeamHP1
	cp SyntacticalAnalyzer.h TeamHP1
	cp SyntacticalAnalyzer.cpp TeamHP1
	cp makefile TeamHP1
	cp README.txt TeamHP1
	tar cfvz TeamHP1.tgz TeamHP1
	cp TeamHP1.tgz ~tiawatts/cs460drop
