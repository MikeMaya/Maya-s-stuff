#include <stdio.h>
#include <stdlib.h>
// Se define la pila
typedef struct NP{
    char c;
    struct NP *sig;
} *NodoP;
typedef struct Snodo{
	NodoP prim;
}*Stack;

int isEmpty(Stack s){
	return s->prim==NULL;
}
Stack empty(){
	Stack temp=(Stack)malloc(sizeof(struct Snodo));
	temp->prim=NULL;
	return temp;
}
Stack push(char c, Stack s){
	NodoP temp=(NodoP)malloc(sizeof(struct NP));
	temp->c=c;
	if(isEmpty(s)){
		s->prim=temp;
		temp->sig=NULL;
	}
	else {
		temp->sig=s->prim;
		s->prim=temp;
	}
	return s;
}
char top(Stack s){
	return s->prim->c;
}
Stack pop(Stack s){
	if(s->prim->sig==NULL){
		s->prim=NULL;
	}
	else {
		s->prim=s->prim->sig;
	}
	return s;
}
//Termina definicion pila

int main(){
	int n;
	Stack s;
	s=empty();
	char c;
    while(scanf("%c",&c)){
    	if(c=='\n' || c=='\0') break;
    	if(c=='('||c=='{'||c=='[') s=push(c,s);
	    else if(c==')'){
	        if(isEmpty(s)){
	            printf("No es una cadena balanceada\n");
	        	return 0;
			}
			else if(top(s)=='(') s=pop(s);
			else {
				printf("No es una cadena balanceada\n");
	        	return 0;
			}
    	}
        else if(c=='}'){
	        if(isEmpty(s)){
	            printf("No es una cadena balanceada\n");
	        	return 0;
			}
			else if(top(s)=='{') s=pop(s);
			else {
				printf("No es una cadena balanceada\n");
	        	return 0;
			}
    	}
    	else if(c==']'){
	        if(isEmpty(s)){
	            printf("No es una cadena balanceada\n");
	        	return 0;
			}
			else if(top(s)=='[') s=pop(s);
			else {
				printf("No es una cadena balanceada\n");
	        	return 0;
			}
    	}
    }
    if(isEmpty(s)) printf("Es una cadena balanceada\n");
    else printf("No es una cadena balanceada\n");
	return 0;
}
