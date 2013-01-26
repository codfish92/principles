#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//prints the command with arguments, also will determine validity of command in process
void printCommandWithArgs(int argc, char* argv[]);

//determine valdity of command
int* isValidCommand(int argc, char* argv[]);

//take a string and prints the string in groups of 5 uppercase letters
//void printEncyptedText(char encryptedText[], FILE * output);

//gets a single line from file
char *fgetline(FILE *fp);

//takes the key supplied and 'sanitizes it' by removing all non letters and making all letters uppercase
char *loadKey(char* key);

//takes a single char and returns the encrypted text or decrypted text based off of a flag
char encrypt(char plaintext,char cipherChar, int flag);

int numChars, numLines, numLetters, numUpper, numLower, numDigit, numWhite, numElse = 0;


int main(int argc, char *argv[])
{
	FILE *inputFile, *outputFile; //input and output files
	int cipherSize;
	char *inputLines, *cipher;
	printCommandWithArgs(argc, argv); // prints command
	inputFile = fopen(argv[1], "rt"); //open file
	
	//check for null pointer
	if(!inputFile){
		printf("Error opening input file. Aborting");
		exit(EXIT_FAILURE);
	}

	//no output file given
	if(argc < 3){
		outputFile = stdout;
	}
	else{
		outputFile = fopen(argv[2], "wt");
		//check null pointer, switches to stdout if there is one
		if(!outputFile){
			printf("I'm herpderping on opening the output file %s", argv[2]);
			printf("I'm just gonna tennis racket to standard out");
			outputFile = stdout;
		}
	}
	cipher = loadKey(argv[3]);//load argument and make it the cipher
	inputLines = fgetline(inputFile);//holds the input
	int counter, cipherindex, group5;// for encryption
	group5 = 0; //for when outputing groups of 5
	cipherindex = 0;


	for(counter = 0; cipher[counter] != '\0'; counter++){
	}
	cipherSize = counter;


	while(inputLines != NULL){ //while fgetline returns a valid pointer
		for(counter = 0; inputLines[counter] != '\0'; counter++){ // while inputline doesn't return a null terminator
			numChars++; //for stats
			if((inputLines[counter] >= 97 && inputLines[counter] <= 121) || (inputLines[counter] >= 65 && inputLines[counter] <= 90)){ //only valid letters are encrypted 
				if(argv[3] != NULL && argv[3][0] == 100){// if the arg 3 is passed and is decrypt mode 'd'
					
					numLetters++; //for stats
					printf("%c", encrypt(inputLines[counter], cipher[cipherindex], 1));
					fprintf(outputFile, "%c", encrypt(inputLines[counter], cipher[cipherindex], 1));// write to file
					group5++;
					if(group5 == 5){
						fprintf(outputFile, "___");
						group5 = 0;
					}
					//incrment the cipher or shift it back to start
					if(cipherindex == cipherSize){
						cipherindex = 0;
					}
					else{
						cipherindex++;
					}
				}
				//if in encrypt mode
				else {
					//printf("%c", encrypt(inputLines[counter], cipher[cipherindex], 0));
					fprintf(outputFile, "%c", encrypt(inputLines[counter], cipher[cipherindex], 0));
					//increment the cipher or shift it back to start
					if(cipherindex == cipherSize - 1){
						cipherindex = 0;
					}
					else {
						cipherindex++;
					}
				}
			}
			//for when a non letter char is passed
			else{
				if(inputLines[counter] == 10)
					numLines++;
				else if(inputLines[counter] == 32)
					numWhite++;
				else if (inputLines[counter] >=48 && inputLines[counter] <= 57)
					numDigit++;
				else
					numElse++;
				printf("have been passed a non letter %d", inputLines[counter]);
				fprintf(outputFile, "%c", inputLines[counter]);
			}
		}
	inputLines = fgetline(inputFile);//get the next line or recive a null on fail
	}

	printf("The total number of lines was %d", numLines);

 	system("PAUSE");
	return 0;
}






// this is the command that will output the apporiate text to screen, also checks if command is valid
void printCommandWithArgs(int argc, char* argv[]) {
  int* isValid;
  isValid = (int*) malloc(4);
  isValid = isValidCommand(argc, argv);
  if(0 == isValid){
		system("PAUSE"); // no output needed on this func, since isValidCommand will output before returning
		exit (EXIT_FAILURE);
	}
//prints the mode
	if(argc == 5){
 		 printf("The ");
 		 printf(argv[4]);
 	 	printf(" command was used.\n");
	}
	else{
		printf("The encrypt command was used.\n");
	}
//prints the cipher key used
	if(argc >= 4){
		printf("The cipher key used was '");
		printf(argv[3]);	
		printf("'\n");	
	}
	else{
		printf("The cipher key used was 'Colorado School of Mines'\n");
	}
//prints the outputfile or states that standard out is used
	if(argc >=3){
		printf("The output file is ");
		printf(argv[2]);
		printf("\n");
	}
	else{
		printf("No output file given, printing result to console.\n");
	}
//prints the input file
	printf("The input file is ");
	printf(argv[1]);
	printf("\n");
}





// checks to see if the command given is valid, since a command is only 'invalid' if there are too few arguments or the mode is incorrect, only need to check the mode and the argument count
int* isValidCommand(int argc, char* argv[]){
	int* isValid;
	isValid = (int*)malloc(4);
	if(argc < 2 || argc >= 6){
		printf("No input file given\n");
		printf("Usage of command is: command inputFile, outputFile, cipherKey, mode\n");
		printf("If there is outputFile given, output will be sent to standard out\n");
		printf("If there is no cipherKey, the cipher key will use a default\n");
		printf("If there is no mode, then encyrption is the default mode. valid modes are encrypt and decrypt\n");
		*isValid = 0;
		return isValid;        
  	 }
	 else if(argc == 5){
		if(strcmp(argv[4], "encrypt") == 1 && strcmp(argv[4], "decrypt") == 1){ //strcmp compares two strings, and will return a 0 if they are equal. 
			printf("Invalid mode. Use either 'encrypt' or 'decrypt'.\n");
			printf(argv[4]);
			*isValid = 0;
			return isValid;

		}
	  }
		*isValid = 1;
		return isValid;
}





char *fgetline(FILE *fp)
{
     char *p;     // pointer to buffer
     int length;  // length of string, not counting NUL
     int bufsize; // length of buffer
     int c;       // one-character buffer (is int to hold status values)
     
     // Do not attempt to read from either standard output device   
     if ( (stdout==fp) || (stderr==fp) )
        return NULL;
     
     // Check if end of file has already been reached.
     if (fp) // fp is assumed to be a file.
        if (feof(fp))
           return NULL;
           
     // Read from stdin (keyboard) if fp is NULL  
     if (!fp) 
        fp = stdin;

     // Allocate initial buffer to just hold the NUL terminator
     p = NULL;
     bufsize = 1;
     length = 0;
     p = (char *) realloc(p, bufsize*sizeof(char));
     if (!p)
        return NULL; // Allocation failed
     
     while (1) // Will exit via RETURN
     {
        c = getc(fp);
        if ((EOF==c)||('\n'==c))
           return p; // Read operation complete. Do not store EOL/EOF
        
        if ( !((length+1)<(bufsize-1)) ) // Grow buffer if needed
        {
           bufsize <<= 1; // Double the buffer size
           p = (char *) realloc(p, bufsize*sizeof(char));
           if (!p)
              return NULL; // Allocation failed, data may be lost
        }
        
        p[length++] = c; // Add the new character to the string
        p[length] = 0;   // Regenerate the NUL terminator
     }
           
     return NULL; // Should never get here
}

char * loadKey(char* key){
	char * cipher;
	int i, number, offset;
	offset = 0 ;// ofset is incase the key provided has non letters in it, iteration can still procede normally and have no garbage values in cipher
	if(NULL == key){
		cipher = (char*) malloc(22);
		cipher = "COLORADOSCHOOLOFMINES";
		return cipher;
	}
	else{

		number = 0;
		//cuz strlen cant be used...
		for(i = 0; key[i] != 0 && key[i] != 10; i++){ // '\0' '\n'
			number++;
		}

		//will be more than enough, since numChars +1 will only be upperbound on size of cipher
		cipher = (char*) malloc(numChars + 1);

		for(i = 0; i < numChars; i++){
			if(key[i] >= 97 && key[i] <= 121){ // 'a' || 'z"
				cipher[i-offset] = key[i] - 32;
			}
			else if(key[i] >= 65 && key[i] <= 90){ // 'A' || 'Z'
				cipher[i-offset] = key[i];
			}
			else{
				offset++;
			}
		}
		cipher[i-offset + 1] = 0;//'\0'
		return cipher;
	}
}



char encrypt(char plaintext, char cipherChar, int flag){
	int plainNum, cipherNum, shiftamount ;
	cipherNum = cipherChar - 65;
	shiftamount = 0;


	//char * returnChar;
	//returnChar = (char)malloc(1);

	//if text is a lowercase char
	if(plaintext >= 97 && plaintext <= 121){ // 'a' || 'z'
		
		plainNum = plaintext - 97;
	}
	//if text is uppercase
	else{
		plainNum = plaintext - 65;
	}
	if((plaintext >= 65 && plaintext <= 90) || (plaintext >= 97 && plaintext <= 121)){ // >= 'A' || <= 'Z' || >= 'a' || <= 'z'
		//for capitals
		if(plaintext >= 65 && plaintext <= 90){ // 'A' || 'Z'
			numUpper++; //for stats
			//encrypt
			if(flag == 0){
				shiftamount = (cipherNum + plainNum) % 26;

				//*returnChar = shiftamount + 65;
				//return returnChar;

				return shiftamount + 65;
			}
			//decrypt
			else {
				shiftamount = plainNum - cipherNum;
				if(shiftamount < 0){
					shiftamount = shiftamount + 26;
				}
				//*returnChar = shiftamount + 65;
				//return returnChar;
				return shiftamount + 65;
			}
		}
		//for lowercase
		else {
			numLower++; //stats
			//encrypt
			if(flag == 0){
				shiftamount = (cipherNum + plainNum) % 26;
				//*returnChar = shiftamount + 97;
				//return returnChar;
				return shiftamount + 97;
			}
			//decrypt
			else {
				shiftamount = plainNum - cipherNum;
				if(shiftamount < 0){
					shiftamount = shiftamount + 26;
				}
				//*returnChar = shiftamount + 97;
				//return returnChar;
				return shiftamount + 97;
			}
		}
	}
	//should only occur if for some reason the call before hand passed a non letter char
	else {
		//*returnChar = plaintext;
		//return returnChar;
		return plaintext;
	}
}




/*
//when given a string of encrypted text, this function will put it in groups of 5 uppercase letters. Does no encyrption, simply prints
void printEncyptedText(char encryptedText[], FILE *output) {
	int i, j, index, groupsOfFive;
	char holder;
	//for if the string is not an even number of 5 ie 13
	if(strlen(encryptedText)%5 != 0){
		//prints all chars up to the last group of 5
		
		groupsOfFive = strlen(encryptedText)/5;

		for(i = 0; i < strlen(encryptedText)/5 ; i++){
			
			for(j = 0; j < 5; j++){
				index = 5*i + j; 
				fprintf(output, "%c", encryptedText[index]);
					
			}
			fprintf(output, "   ");
		}
		for( i = 0; i < strlen(encryptedText)%5; i++){
			fprintf(output, "%c", encryptedText[5*groupsOfFive+i]);
		}
	}
	//for if the string is an even number of 5 ie 15
	else {
		for(i = 0; i < strlen(encryptedText)/5; i++){
			for(j = 0; j < 5; j++){
				index = 5*i + j;
				fprintf(output, "%c", encryptedText[index]);
			}
			fprintf(output, "   ");
		}
	}


	printf("\n");
	return;
}

*/

