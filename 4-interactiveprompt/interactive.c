#include <stdio.h>

static char input[2048];
int main (int arga, char** argv){
	puts ("Lispy Version 0.0.0.1");
	puts ("Press Ctrl+c to Exit");
	/*infinite loop*/
	while(1){
		
		/*Output our prompt??*/
		/*Also doesn't print newline char*/
		/*needs a file to write to -> stdout (special case) takes care of it*/
		fputs("lisp>", stdout);
		
		/*readline max 2048 chars*/
		/*same manner as 'fputs' | 'fgets' needs to read from file -> 'stdin' takes care of it*/
		/*'fgets' waits for user input*/
		/*'input' is variable that is passed down to 'printf'*/
		fgets(input,2048,stdin);
		
		/*look at documentation for more use*/
		/*http://en.cppreference.com*/
		printf("No you're a %s",input);
	}
	return 0;
}