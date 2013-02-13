#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char* argv){
char* holder;
holder = malloc(2);
int txt = 65;
sprintf(holder, "%c",txt);
printf(holder);
}
