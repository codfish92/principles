%option noyywrap

%{

#include <math.h>


%}
DIGIT [0-9]
%%
{DIGIT}+|{DIGIT}*\.{DIGIT}+ { printf ("A real number: %s (%d)\n", yytext, atoi(yytext));}
\+|\- { printf ("An operator: %s\n", yytext);}
{DIGIT}+i|{DIGIT}*\.{DIGIT}+i { printf ("An imaginary number: %s\n", yytext);}
{DIGIT}+[+-]{DIGIT}+i|{DIGIT}*\.{DIGIT}+[+-]{DIGIT}+i|{DIGIT}+[+-]{DIGIT}*\.{DIGIT}+i|{DIGIT}*\.{DIGIT}+[+-]{DIGIT}*\.{DIGIT}+i { printf ("A complex number: %s", yytext);}


%%
int main(int argc, char** argv)
{
	++argv, --argc;
if(argc > 0)
	yyin = fopen( argv[0], "r");
else
	yyin = stdin;
yylex();
}
