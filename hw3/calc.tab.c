// This file emulates the file that would normally be created by Bison
// This file would normally be generated by Bison

#include <stdio.h>
#include <stdlib.h>

#include "calc.tab.h"

FILE *yyin = NULL;
char *yytext = NULL;

int ExportToken(FILE *yyout, int token, char *yytext) // takes an output file, a token, and a string
{
    fprintf(yyout, "<%03i> %s\n", token, ((yytext)? yytext:"")); // write the output, if no string exists, then use an empty string
    if (yytext) //if the text exists
       free(yytext); // deallocate it
    yytext = NULL; // make it null
    return 0;
}

int yyparse(char const *filename) // takes a string representing the file name
{
   FILE *yyout; //output file
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

