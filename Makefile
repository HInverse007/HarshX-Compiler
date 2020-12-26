ANTLR4=java -Xmx500M -cp "/usr/local/lib/antlr-4.8-complete.jar:$CLASSPATH" org.antlr.v4.Tool

antlr:	HarshX.g4
		$(ANTLR4) -Dlanguage=Cpp -no-listener -visitor HarshX.g4
		g++ -g -std=c++14 main.cpp -o HarshX -I/usr/local/include/antlr4-runtime -Igenerated -I/usr/local/lib/ -Igenerated -I/usr/include/llvm-6.0  -I/usr/include/llvm-c-6.0 -lantlr4-runtime -lLLVM-6.0 
clean:	
		rm -f HarshXLexer.h HarshXParser.h expr *.tokens *.interp HarshXBaseVisitor.cpp \
		rm -f HarshXBaseVisitor.h HarshXParser.cpp HarshXLexer.cpp HarshXBaseVisitor.cpp  \
		rm -f HarshXVisitor.cpp  HarshXVisitor.h

