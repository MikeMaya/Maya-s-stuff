#include <window.h>
#inclide <stdio.h>
int main(int argc, char argv*[]){
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	HANDLE hSemaforo;
	int i=1;
	ZeroMemory(&si,sizeof(si));
	si.cb=sizeof(si);
	ZeroMemory(&pi,sizeof(pi));
	if(argc!=2){
		printf("usar:%s Nombre:programa_hijo\n",argv[0]);
		return;
	}
	//Creacion del semaforo
	if((hSemaforo=CreateSemaphore(NULL,1,1,"Semaforo"))==NULL){
		printf("Falla al invocar CreateSemaphore: %d\n",GetLastError());
		return -1;
	}
	//Creacion de proceso hijo
	if(!CreateProcess(NULL,argv[1],NULL,NULL,FALSE,0,NULL,NULL,&si,&pi)){
		printf("Falla al invocar CreateProcess: %d\n");
		return -1;
	}
	while(i<4){
		//Prueba del semaforo
		WaitForSingleObject(hSemaforo, INFINITE);

		//Seccion critica
		printf("Soy el padre entrando %i de 3 veces al semaforo\n", i);
		Sleep(5000);

		//Liberar el semaforo
		if(!ReleaseSemaphore(hSemaforo,1,NULL)){
			printf("Falla al invocar ReleaseSemaphore: &d\n",GetLastError());
		}

		printf("Soy el padre liberando  %i de 3 veces al semaforo\n",i);
		Sleep(5000);
		i++;		
	}
	//Terminacion controlada del proceso e hilo 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}
