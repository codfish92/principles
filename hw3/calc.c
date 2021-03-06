// This file would normally be generated by Flex

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 

#include "calc.tab.h"

/*Regex's explained
int
[0-9]+  this will match 1 or more digits (ie 1 or 4578)

float
[0-9]*\.[0-9]+|[0-9]+\.[0-9]*  this will match 0 or more digits, followed by a ., then followed by 1 or more digits(ie 123.5433 or .0) OR match 1 or more digits, followed by ., then 0 or more digits(ie 1.324 or 15.)

exp
[float]E[int]|[int]E[int]  this will match a float, followed by a E, followed by an int(ie 1.4E10 or .9E0 or 1.E4) OR match 1 int, followed by an E, followed by an int (ie 9E76)

ID
\bR[0-9]\b  this will match a R, followed by 1 digit (ie R0 or R7) 

Symbol

line comment
\/\/.*(?!\n)  this will match anything precceded by to //, but not the new line

block comment
\/\*.*\*\/ (dot all)  this will match any amount of charcters including new lines, that are inbetween the "/* '*'/ comment blocks

newLine


*/





int yylex(void)
{
   static int tokens = 0;
   
   int token;
   int yychar;
   
   //----------------------------------------------------------
   // This code is junk placeholder code to give an initial
   // lexer that will compile and run and do something.
   
   yychar = fgetc(yyin); // File assumed to be open and ready
   if (EOF == yychar) // if the char is the end of file character, 
   {
      token = END; // then it is an end token
      yytext = (char *) malloc(11*sizeof(char));
      sprintf(yytext, "%i", tokens);
   }
	//the following uses the same style above, but due to linker errors, is currently untested
	else if ('+' == yychar){
		token = ADD
		yytext = (char *) malloc(4*sizeof(char)); //ADD is three chars plus one null terminator
		sprintf(yytext, "%c", yychar);
		tokens++; //there is one more valid token
	}
	else if('-' == yychar){
		token = SUB
		yytext = (char *) malloc (4*sizeof(char)); 
		sprintf(yytext, "%c", yychar);
		tokens++;
	}
	else if ('^' == yychar){
		token = EXP
		yytext = (char *) malloc (4*sizeof(char));
		sprintf(yytext, "%c", yychar);
		tokens++;
	}
	else if ('*' == yychar){ // will need to throw in check for comments
		token = MUL
		yytext = (char *) malloc (4*sizeof(char));
		sprintf(yytext, "%c", yychar);
		tokens++;
	}
	else if ('/' == yychar){ // will need to thrown in check for comment
		token = DIV
		yytext = (char *) malloc (4*sizeof(char));
		sprintf(yytext, "%c", yychar);
		tokens++;
	}
	else if (';' == yychar){
		token == SEMI
		yytext = (char *) malloc (5*sizeof(char));
		sprintf(yytext, "%c" ,yychar);
		tokens++;
	}
	else if ('=' == yychar){
		token == ASSIGN
		yytext = (char *) malloc(7*sizeof(char));
		sprintf(yytext, "%c" ,yychar);
		tokens++;
	}
	else if ('(' == yychar){
		token = OPAREN;
		yytext = (char *) malloc(7*sizeof(char));
		sprintf(yytext, "%c", yychar);
		tokens++;
	}
	else if (')' == yychar){
		token = CPAREN;
		yytext = (char *) malloc(7*sizeof(char));
		sprintf(yytext, "%c", yychar);
		tokens++;
	}
	else if ('R' == yychar){
	//stuff
	}
	else if ('0' <= yychar && '9' >= yychar) {
	//stuff
	}


   else // if all other recognitions fail, then it must be a bad token
   {
      token = BAD;
      yytext = (char *) malloc(4*sizeof(char));
      if (isgraph(yychar)&&('#' != yychar))
         sprintf(yytext, "%c", yychar);
      else
         sprintf(yytext, "#%02X", (yychar&0xFF));
   }
   //----------------------------------------------------------
   
   return token;
}

int main(int argc, char *argv[])
{

   if (argc <= 1)
   {
      printf("USAGE: calc inputfilename\n");
      exit(EXIT_FAILURE);
   }
   
   yyparse(argv[1]);
   
   printf("Hit ENTER to exit.");
   fgetc(stdin);
   
   return 0;
}
