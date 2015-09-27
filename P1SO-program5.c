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
//Funciones evaluadoras
int prec(char c){
    switch(c){
    	case '{': return 0;
    	case '[': return 1;
        case '(': return 2;
        case '+': return 3;
        case '-': return 4;
        case '*': return 5;
        case '/': return 6;
        case '!': return 7;
    }
}
int esOperador(char c){
    if(c=='+' || c=='-' || c=='/' || c=='*' || c=='!' ||
       c=='(' || c==')' || c=='[' || c==']' || c=='{' || c=='}'){
        return 1;
    }
    else return 0;
}
int esOperando(char c){
    return esOperador(c)==0;
}
//Fin de funciones evaluadoras

//Funcion que evalua la expresion posfija

double evaluar(char posfija[100], int largo){
	double a, b, c, temp;
	double stac[100];
	int i, top=0;
	for(i=0;i<largo;i++){
		if(posfija[i]==',') continue;
		else if(esOperando(posfija[i])){
			temp=(double)posfija[i] -'0';
			char a=posfija[++i];
			while(a!=',' && esOperando(a)){
				temp*=10;
				temp+=(double)a -'0';
				a=posfija[++i];
			}
			i--;
			//printf("OPERANDO: %d\n", );
			stac[top++]=temp;
		}
		else {
			b=stac[--top];
			a=stac[--top];
			switch(posfija[i]){
				case '+': c=a+b; break;
        		case '-': c=a-b; break;
        		case '*': c=a*b; break;
        		case '/': c=a/b; break;

			}
			stac[top++]=c;
		}

	}
	return stac[top-1];
}
//Se termina de evaluar la funcion posfija

int main(){
	int n;
	Stack s;
	s=empty();
	char c;
	char posfija[100];
	int largo=0;
	int flag=0;
	 // Se pasa a posfija
    while(1){
    	if(!flag) scanf("%c",&c);
    	else flag=0;
        if(c=='\n' || c=='\0') break;
        if(c=='('||c=='{'||c=='[') s=push(c,s);
        else if(c==')' || c=='}' || c==']'){
        	char a=top(s);
            while(a!='(' && a!='{' && a!='['){
                posfija[largo++]=a;
                s=pop(s); a=top(s);
            }
            s=pop(s);
        }
        else if(esOperando(c)==1){
            posfija[largo++]=c;
            scanf("%c",&c);
            while(esOperando(c)){
            	if(c=='\n' || c=='\0'){
            		flag=1;
            		break;	
            	} 
            	posfija[largo++]=c;
            	scanf("%c",&c);
            }
            posfija[largo++]=',';
            flag=1;
            continue;
        }
        else if(esOperador(c)){
            while(!isEmpty(s) && (prec(top(s))>= prec(c))){
                posfija[largo++]=top(s);
                s=pop(s);
            }
            s=push(c,s);
        }
    }
    while(!isEmpty(s)){
        posfija[largo++]=top(s);
        s=pop(s);
    }
    // Se termina la conversion
    
    printf("%.2lf\n",evaluar(posfija, largo));
	return 0;
}
