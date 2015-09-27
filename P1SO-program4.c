#include <stdio.h>
#include <stdlib.h>

typedef struct Datos{
	char caracter;
	float flotante;
	long long int entero64;
}masDatos;

typedef struct NC{
	int entero;
	double doble;
	masDatos otros;
	struct NC *sig;	
} *NodoC;

typedef struct Nodo{
	NodoC prim;
	NodoC ult;
}*Cola;

Cola new(){
    Cola temp=(Cola) malloc (1*sizeof(struct Nodo));
    temp->prim=temp->ult=NULL;
    return temp;
}

Cola push(Cola q, int ent, double dob, masDatos otr){
    NodoC temp=(NodoC) malloc (sizeof(struct NC));
    Cola tempc= new();
    temp->entero=ent;
    temp->doble=dob;
    temp->otros=otr;

    if(q->prim==NULL) tempc->prim=tempc->ult=temp;
    else{
        q->ult->sig=temp;
        tempc->prim=q->prim;
        tempc->ult=temp;
        //q->ult=temp;
    }
    return tempc;
}

Cola pop(Cola q){  //Desformar
    Cola tempc=new();
    if(q->prim==q->ult){
        return tempc;
    }
    else{
        tempc->prim=q->prim->sig;
        tempc->ult=q->ult;
        return tempc;
    }
}

Cola front(Cola q){
	printf("Entero: %d\nDoble: %lf\n",q->prim->entero,q->prim->doble);
	printf("Otros datos\n");
	printf("Caracter: %c\n",q->prim->otros.caracter);
	printf("Flotante: %f\n",q->prim->otros.flotante);
	printf("Entero de 64 bits: %lld\n",q->prim->otros.entero64);
	printf("\n");
}

int main(){
	Cola a=new();
	masDatos otros;
	otros.caracter='c';
	otros.flotante=24.25;
	otros.entero64=56999999999;
	masDatos otros1;
	otros1.caracter='z';
	otros1.flotante=78.98;
	otros1.entero64=99009999999;
	a=push(a,1,3.1416,otros);
	a=push(a,5,29.06,otros1);
	front(a);
	a=pop(a);
	front(a);

	return 0;
}
