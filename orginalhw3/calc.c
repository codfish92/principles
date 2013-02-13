// This file would normally be generated by Flex

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>
#include "calc.tab.h"
typedef enum {
	START, INTEGER, FLOATSTART, FLOAT,  FLOATNOE, E, EXPO //these represent each circle on a state diagram, not all states are accepting states
} numberState;
typedef enum {
	T_INTEGER, T_FLOAT, T_EOF, T_BAD ,T_NONE//the type of integer, it is only used for numbers
} tokenType;

int yylex(void)
{
	static int tokens = 0;
	static int buffer = 0; // make the buffer 
	int token;
	int yychar;
	char *holder;
	char * yystring;
	numberState state = START;
	tokenType type = T_NONE;
	holder = malloc(2 * sizeof(char));
	yystring =  malloc(256*sizeof(char));//pre allocate a string
	yystring[0] = '\0';//set the first char to the null, so we have a string of length 0
	
	//--------------------------------------------------------
	// This code is junk placeholder code to give an initial
	// lexer that will compile and run and do something.
	if(buffer){
		yychar = buffer;
		buffer = 0;
  }
	else
		yychar = fgetc(yyin); // File assumed to be open and ready
//remember to including identifiers
	while(EOF != buffer && EOF != yychar){ // for handleing numbers such as floats and ints
		yychar = buffer; //put the char in the buffer into the yychar
		switch (state){
			case START: // if in the start state
				if('.' == yychar){ // if the next char is .
					state = FLOATSTART; //move to the float start
					sprintf(holder, "%c", yychar);
					strcat(yystring, holder);//add to yystring
				}
				else if(isdigit(yychar)){//is a digit
					state = INTEGER;//state is integer
					type = T_INTEGER;//token is integer
					sprintf(holder, "%c", yychar);
					strcat(yystring, holder);//add to yystring
				}
				else
					goto bad;//get out of case statement
				break;
			case INTEGER://have seen a num but no . or E
				if('.' == yychar){// is a dot
					state = FLOATNOE;// float but not an E float
					type = T_FlOAT;// float token
					sprintf(holder, "%c", yychar);
					strcat(yystring, holder);//add to yystring
				}
				else if (isdigit(yychar)){
					sprintf(holder, "%c", yychar);
					strcat(yystring, holder);//add to yystring
				}
				else if('E' == yychar){
					state = E;// have seen an e
					type = T_BAD;//potential for bad token
					sprintf(holder, "%c", yychar);
					strcat(yystring, holder);//add to yystring
				}
				else
					goto bad;
				break;
			case FLOATSTART://if we have seen a . but no num
				if(isdigit(yychar)){// is num
					sprintf(holder, "%c", yychar);
					strcat(yystring, holder);//add to yystring
					state = FLOATNOE;//a float but with no e
					type = T_FLOAT;//type is float
				}
				else
					goto bad;
				break;
			case FLOATNOE:
				if(isdigit(yychar)){
					sprintf(holder, "%c", yychar);
					strcat(yystring, holder);//add to yystring
				}
				else if ('E'== yychar){
					state = E;//e float
					type = T_BAD;//potintial for bad token
					sprintf(holder, "%c", yychar);
					strcat(yystring, holder);//add to yystring
				}
				else
					goto bad;
				break;
			case E:
				if('+' == yychar || '-' == yychar){//have seen a plus or minus
					sprintf(holder, "%c", yychar);
					strcat(yystring, holder);//add to yystring
					state = EXPO;//now have a num with an E with a plus or minus, but still no accepting state
				}
				else
					goto bad;
				break;
			case EXPO:
				if(isdigit(yychar)){
					sprintf(holder, "%c", yychar);
					strcat(yystring, holder);//add to yystring
					state = FLOAT; // we are now a float with an e
					type = T_FLOAT;// float
				}
				else
					goto bad;
				break;
			case FLOAT:
				if(isdigit(yychar)){
					sprintf(holder, "%c", yychar);
					strcat(yystring, holder);//add to yystring
				}
				else
					goto bad;
				break;
		}
		buffer = fgetc(yyin); //load the next char
	}
	bad: 
	if(T_FLOAT == type){
		token = FLT;
		yytext = malloc((strlen(yystring)+1)*sizeof(char));
		sprintf(yytext, yystring);
	}
	else if (T_INTEGER == type){
		token = INT;
		yytext = malloc((strlen(yystring)+1)*sizeof(char));
		sprintf(yytext, yystring);
		
	}
	else if (T_EOF == type){
		
	}
	else if (T_BAD == type){
		token = BAD;
		yytext = malloc((strlen(yystring)+1)*sizeof(char));
		sprintf(yytext, yystring);
	}

	if (EOF == yychar)//if the end of file is encountered
	{
	   token = END;
	   yytext = (char *) malloc(11*sizeof(char));
	   sprintf(yytext, "%i", tokens);
	}
	else if ('R' == yychar){//could be an id
	   buffer = fgetc(yyin);
	   if(isdigit(buffer)){
		sprintf(holder, "%c", yychar);
		strcat(yystring, holder);//add to yystring

	   }
	   else{
	  	token = BAD;
	   	yytext = (char *) malloc(4*sizeof(char));
	   	if (isgraph(yychar)&&('#' != yychar))
	      		sprintf(yytext, "%c", yychar);
	  	 else
	      		sprintf(yytext, "#%02X", (yychar&0xFF));

	   }
	}
	else if('+' == yychar){// a plus
	token = ADD;
	yytext = (char *) malloc(4*sizeof(char));
	sprintf(yytext, "%c", yychar);
	tokens++;
	}
	else if('-' == yychar){ // a sub
	token = SUB;
	yytext = (char *) malloc(4*sizeof(char));
	sprintf(yytext, "%c", yychar);
	tokens++;

	}
	else if('*' == yychar){// a mult
	token = MUL;
	yytext = (char *) malloc(4*sizeof(char));
	sprintf(yytext, "%c", yychar);
	tokens++;

	}
	else if('=' == yychar){// an assign
	token = ASSIGN;
	yytext = (char *) malloc(4*sizeof(char));
	sprintf(yytext, "%c", yychar);
	tokens++;

	}
	else if('^' == yychar){// an exponet
	token = EXP;
	yytext = (char *) malloc(4*sizeof(char));
	sprintf(yytext, "%c", yychar);
	tokens++;

	}
	else if('(' == yychar){ // an open paren
	token = OPAREN;
	yytext = (char *) malloc(4*sizeof(char));
	sprintf(yytext, "%c", yychar);
	tokens++;

	}
	else if(')' == yychar){ // a close paren
	token = CPAREN;
	yytext = (char *) malloc(4*sizeof(char));
	sprintf(yytext, "%c", yychar);
	tokens++;

	}
	else if(';' == yychar){ // a semi
	token = SEMI;
	yytext = (char *) malloc(4*sizeof(char));
	sprintf(yytext, "%c", yychar);
	tokens++;

	}
		

	else if ('/' == yychar){ //we've seen one /
		buffer = fgetc(yyin); // look ahead
		if ('/' == buffer){ // if the lookahead is another /, we are in an eol comment
			int numChars;
			numChars = 0;
			buffer = fgetc(yyin);//get the next char
			while('\n' != buffer && EOF != buffer){ //while were not looking at EOF or a newline
				numChars++;//add number of chars
				yystring = (char *) realloc((numChars+1)*sizeof(char));// realloc space
				sprintf(holder, "%c", yychar);
				strcat(yystring, holder);//add to yystring
				buffer = fgetc(yyin);//load next char
			}
			token = EOLCMT;
			yytext = (char *) malloc((strlen(yystring)+1)*sizeof(char));
			sprintf(yytext, yystring);
	
		}
		else if('*' == buffer){ // a block comment
			int numChars;
			numChars = 0;
			buffer = fgetc(yyin);//get next char
			while(EOF != buffer){//while we are not at EOF
				numChars++;
				yystring = (char *) realloc((numChars+1)*sizeof(char));
				sprintf(holder, "%c", yychar);
				strcat(yystring, holder);//add to yystring
				if('*' == buffer){ //we could be at end
					buffer = fgetc(yyin);//load next char
					numChars++;
					if(EOF == buffer)//if its the EOF, break
						break
					else if('/' == buffer){ //we are at the end of block comment
						yystring = (char*) realloc((numChars+1) * sizeof(char));
						sprintf(holder, "%c", yychar);
						strcat(yystring, holder);//add to yystring
						token = BLKCMT;
						yytext = (char *) malloc((strlen(yystring)+1)*sizeof(char));
						sprintf(yytext, yystring);
						break;
					}
					else{	//we are not at end of block comment, so just add buffer to token and continue
						yystring = (char*) realloc((numChars+1) *sizeof(char));
						strncat(yystring, &buffer, 1);
				 		sprintf(holder, "%c", yychar);
						strcat(yystring, holder);//add to yystring
					}
				}
				buffer = fgetc(yyin);
			}
			if(EOF == buffer){//if we broke from the while loop, but it may have been because an EOF was encountered, which makes the token bad
				token = BAD;
				yytext = (char*) malloc((strlen(yystring)+1)*sizeof(char));
				sprintf(yytext,yystring);
			}
	
		}
		else{//otherwise the / is a div token
			token = DIV;
			yytext = (char *) malloc(4*sizeof(char));
			sprintf(yytext, "%c", yychar);
			tokens++;
		}
	}
	else
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
