#include <stdio.h>

/*program runs even without specification of the function output*/
char Hello(){
	puts("Hello_World!");
}
int main(int argc,char** argv){
	int i = 0;
	while(i<10){
		Hello();
		i = i +1;
	}
	
}