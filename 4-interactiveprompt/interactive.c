#include <stdio.h>

static char input[2048];
int main (int argv, char** argv){
	puts ("Lispy Version 0.0.0.1");
	puts ("Press Ctrl+c to Exit");
	while(1){
		fputs("lisp>", stdout);
		fgets(input,2048,stdin);
		printf("No you're a %s",input);
	}
	return 0;
}