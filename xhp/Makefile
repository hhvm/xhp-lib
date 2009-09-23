ifdef DEBUG
CPPFLAGS = -fPIC -ggdb -Wall -DDEBUG
else
CPPFLAGS = -fPIC -g -Wall -O3
endif

all: libxhp.a libxhp.so

clean:
	-rm libxhp.a xhpize parser.yacc.cpp scanner.lex.cpp scanner.lex.hpp parser.yacc.output parser.yacc.hpp *.o 2>/dev/null

parser.yacc.cpp: parser.y
	bison --debug -d -o $@ $<

parser.yacc.hpp: parser.yacc.cpp

scanner.lex.cpp: scanner.l
	flex -C --header-file=scanner.lex.hpp -o $@ -d $<

scanner.lex.hpp: scanner.lex.cpp

%.o: %.cpp
	$(CXX) -c $(CPPFLAGS) -o $@ $<

xhp_preprocess.o: xhp_preprocess.cpp scanner.lex.hpp parser.yacc.hpp
parser.yacc.o: scanner.lex.hpp
scanner.lex.o: parser.yacc.hpp

libxhp.a: code_rope.o scanner.lex.o parser.yacc.o xhp_preprocess.o
	$(AR) -crs $@ $^

libxhp.so: code_rope.o scanner.lex.o parser.yacc.o xhp_preprocess.o
	g++ -shared -Wl,-soname,libxhp.so -o libxhp.so $^

xhpize: xhpize.cpp libxhp.a
	$(CXX) $(CPPFLAGS) -o $@ $^

.PHONY: all clean tags
