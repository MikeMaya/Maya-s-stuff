#include <window.h>
#include <stdio.h>

int main(){
	HANDLE hSemaforo;
	int i=1;
	//Apartura del semaforo
	if((hSemaforo=OpenSemaphore(SEMAPHORE_ALL_ACCESS,FALSe,"Semaforo"))==NULL){
		printf("Falla al invocar OpenSemaphore: %d\n",GetLastError());
		return -1;
	}
	while(i<4){
		//Prueba del semaforo
		WaitForSingleObject(hSemaforo,INFINITE);

		//Seccion critica
		printf("Soy el hijo entrando %i de 3 veces al semaforo\n",i);
		Sleep(5000);

		//Liberando el semaforo
		if(!ReleaseSemaphore(hSemaforo,1,NULL)){
			printf("Falla al invocar ReleaseSemaphore: %d\n",GetLastError());
		}

		printf("Soy el hijo liberando %i de 3 veces al semaforo\n",i);
		Sleep(5000);
		i++;
	}
}
