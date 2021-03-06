// This file emulates the file that would normally be created by Bison
// This file would normally be generated by Bison

#include <stdio.h>
#include <stdlib.h>

#include "calc.tab.h"

FILE *yyin = NULL;
char *yytext = NULL;

char * convertInts(int givenInts){
	char * returnString;
	if(givenInts == 263){
		returnString = malloc(4);
		sprintf(returnString, "MUL");
		return returnString;
	}
	else if(givenInts == 0){
		returnString = malloc(4);
		sprintf(returnString, "END");
		return returnString;
	}
	else if (givenInts == 269){
		returnString = malloc(8);
		sprintf(returnString, "NEWLINE");
		return returnString;
	}
	else if (givenInts == 259){
		returnString = malloc(7);
		sprintf(returnString, "OPAREN");
		return returnString;
	}
	else if (givenInts == 260){
		returnString = malloc(7);
		sprintf(returnString, "CPAREN");
		return returnString;
	}
	else if (givenInts == 261){
		returnString = malloc(7);
		sprintf(returnString, "ASSIGN");
		return returnString;
	}
	else if(givenInts == 262){
		returnString = malloc(4);
		sprintf(returnString, "EXP");
		return returnString;
	}
	else if(givenInts == 264){
		returnString = malloc(4);
		sprintf(returnString, "DIV");
		return returnString;
	}
	else if(givenInts == 265){
		returnString = malloc(4);
		sprintf(returnString, "ADD");
		return returnString;
	}
	else if(givenInts == 266){
		returnString = malloc(4);
		sprintf(returnString, "SUB");
		return returnString;
	}
	else if(givenInts == 267){
		returnString = malloc(5);
		sprintf(returnString, "SEMI");
		return returnString;
	}
	else if (givenInts == 268){
		returnString = malloc(4);
		sprintf(returnString, "BAD");
		return returnString;
	}
	else if (givenInts == 270){
		returnString = malloc(7);
		sprintf(returnString, "EOLCMT");
		return returnString;
	}
	else if (givenInts == 271){
		returnString = malloc(7);
		sprintf(returnString, "BLKCMT");
		return returnString;
	}
	else if (givenInts ==256){
		returnString = malloc(3);
		sprintf(returnString, "ID");
		return returnString;
	}
	else if(givenInts == 257){
		returnString = malloc(4);
		sprintf(returnString, "INT");
		return returnString;
	}
	else if (givenInts == 258){
		returnString = malloc(4);
		sprintf(returnString, "FLT");
		return returnString;
	}
	else
		printf("hello there");
}

int ExportToken(FILE *yyout, int token, char *yytext)
{
	char * tokenInText;
	tokenInText = convertInts(token);
    fprintf(yyout, "<%s> %s\n", tokenInText, ((yytext)? yytext:""));
    if (yytext)
       free(yytext);
    yytext = NULL;
    free(tokenInText);
    return 0;
}

int yyparse(char const *filename)
{
   FILE *yyout;
   int token;
   
   yyin = fopen(filename, "rt");
   if (!yyin)
   {
      printf("File %s failed to open.\n", filename);
      return -1;
   }

   yyout = fopen(OUTPUTFILE, "wt");
   if (!yyout)
   {
      printf("File %s failed to open.\n", OUTPUTFILE);
      return -2;
   }

   while (token=yylex())
      ExportToken(yyout, token, yytext);
   ExportToken(yyout, token, yytext);
   
   fclose(yyin);
   fclose(yyout);
   
   return 0;
}


