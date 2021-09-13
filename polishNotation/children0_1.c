#include "mpc.h"
#ifdef _WIN32

/*seen only in file in which it is declared*/
static char buffer[2048];
int number_of_nodes(mpc_ast_t* t){
	if(t-> children_num==0){return 1;}
	if(t-> children_num>=1){
		int total =1;
		for(int i = 0; i< t-> children_num; i++){
				total = total + number_of_nodes(t->children[i]);
		}
		return total;
		}
}
char* readline(char* prompt){
	fputs(prompt, stdout);
	fgets(buffer, 2048, stdin);
	
	/*This function returns a pointer to the allocated memory, or NULL if the request fails.*/
	char* cpy = malloc(strlen(buffer)+1);
	
	/*Copies the character string pointed to by src, including the null terminator, to the character 
	array whose first element is pointed to by dest.*/
	strcpy(cpy, buffer);
	
	cpy[strlen(cpy)-1]='\0';
	return cpy;
}
void add_history(char* unused){}

#else
#include <editline/readline.h>
#include <editline/history.h>
#endif

/*Use operator string to see which operation to perform */
/* 'strcmp compares 'op' and another char; if same return 0*/
long eval_op(long x, char* op, long y){
	if (strcmp(op,"+")== 0){return x+y;}
	if (strcmp(op,"-")== 0){return x-y;}
	if (strcmp(op,"*")== 0){return x*y;}
	if (strcmp(op,"/")== 0){return x/y;}
	return 0;
	
}

long eval(mpc_ast_t* t){
/* 	foo->bar == (*foo).bar	*/
printf("Number of nodes %d \n",number_of_nodes(t));
	/*If tagged as number return it derectly.*/
	/*comparing strings if equals; return pointer or something like this*/
	/*So if tag is "number" if statement == true*/
	if(strstr(t->tag,"number")){
		/*'atoi' char to intiger */
		return atoi(t->contents);
	}
	/* The operator is always secnod child. */
	char* op = t->children[1]->contents;
	
	/*Storing third chld in x */
	long x = eval(t->children[2]);
	
	/*iterate the remaining children and combining. */
	int i = 3;
	while (strstr(t->children[i]->tag,"expr")){
		printf("Children %s  ",t->children[i]);
		x=eval_op(x,op,eval(t->children[i]));
		printf("while loop x eval %d  ",x);
		i++; 
	}
	return x;
	
}
int main(int argc, char** argv){
	mpc_parser_t* Number= mpc_new("number");
	mpc_parser_t* Expr= mpc_new("expr");
	mpc_parser_t* Operator= mpc_new("operator");
	mpc_parser_t* Lispy= mpc_new("lispy");
mpca_lang(MPCA_LANG_DEFAULT,
"														\
number		: /-?[0-9]+/;								\
operator	: '+'|'-'|'/'|'*';							\
expr 		:<number> | '(' <operator> <expr> +	')';	\
lispy		:/^/<operator> <expr>+ /$/;					\
",
Number,Operator,Lispy,Expr);
puts("Lispy version 0.0.0.3");
puts("Press Ctrl+C to exit");
while(1){
char* input = readline("lispy>");
add_history(input);

/* what is this?*/
mpc_result_t r;
if(mpc_parse("<stdin>",input,Lispy,&r)){
	long result = eval(r.output);
	/*%li shortcut for long integer*/
	printf("%li\n",result);
	mpc_ast_delete(r.output);
}else{
	mpc_err_print(r.error);
	mpc_err_delete(r.error);
}
/*What is this?*/
free(input);

}
mpc_cleanup(4,Number,Operator,Expr,Lispy);
return 0;
}

























































