cmake .;
cd parser;
flex lexer.l;
bison --defines=tokens.h parser.y;
cp parser.tab.c parser.tab.cpp;
cp lex.yy.c lex.yy.cpp;
rm parser.tab.c;
rm lex.yy.c;
cd ..;
make;
./dbproject dataset/customer.sql;
