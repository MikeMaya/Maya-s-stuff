#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/sem.h>
#define TAM_MEM 400            	/*Tamaño de la memoria compartida en bytes*/

int main(){
	int i,j,k=0;
	int m1[10][10],m2[10][10];
	float mf1[10][10];
	float mf2[10][10];
	float mfr1[10][10];
	float mfr2[10][10];
	int shmid,semid;
	key_t km1,ks1;
	int *shm, *s;
	int semban=IPC_CREAT|0666;
	int nsems=1;
	int nsops;
	pid_t pid;
	struct sembuf *sops=(struct sembuf*) malloc(2*sizeof(struct sembuf));
	//Se leen los datos
	FILE *fin = fopen("matriz.in","r");
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			fscanf(fin, "%d",&m1[i][j]);
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			fscanf(fin,"%d",&m2[i][j]);
	fclose(fin);
	//Creamos la memoria 1
	km1=71;
	if((shmid = shmget(km1,TAM_MEM, IPC_CREAT | 0666))<0){
    	perror("Error al obtener memoria compartida: shmget");
    	exit(-1);
	}
	if((shm = shmat(shmid,NULL, 0))== (char *) -1){
    	perror("Error al enlazar la memoria compartida: shmat");
    	exit(-1);
	}
	s=shm;
	//Creamo el semaforo
	printf("Inciando semaforo...\n");
	if((semid=semget(ks1,nsems,semban))==-1){
		perror("semget: error al iniciar el semaforo");
		exit(1);
	} else printf("Semaforo inciado...\n");
	//Creamos al hijo
	if((pid=fork())<0){
		perror("fork: error al crear proceso\n");
		exit(1);
	}
	if(pid==0){ //sons stuff
		int mr[10][10];
		//Leemos las matrices 1  2 del padre
		while(k<2){
			s=shm;
			nsops=2;
			sops[0].sem_num=0;
			sops[0].sem_op=0;
			sops[0].sem_flg=SEM_UNDO;
			sops[1].sem_num=0;
			sops[1].sem_op=1;
			sops[1].sem_flg=SEM_UNDO|IPC_NOWAIT;
			if((j=semop(semid,sops,nsops))==-1){
				perror("semop: error en operacion del semaforo\n");
			}
			else {
				printf("\n\nProceso Hijo - leyendo matriz %d\n",k+1);
				//Escribimos en la memoria
				if(k==0){
					for(i=0;i<10;i++)
	    				for(j=0;j<10;j++)
	        				m1[i][j]=*s++;
	        	}
	        	if(k==1){
					for(i=0;i<10;i++)
	    				for(j=0;j<10;j++)
	        				m2[i][j]=*s++;
	        	}
				nsops=1;
				sops[0].sem_num=0;
				sops[0].sem_op=-1;
				sops[0].sem_flg=SEM_UNDO|IPC_NOWAIT;
				if((j=semop(semid,sops,nsops))==-1){
					perror("semop: error en operacion del semaforo\n");
				}
				else printf("Proceso Hijo regresa el control del semaforo\n");
				sleep(1);
			}
			++k;
		}
		//Calculo de multiplicacion
		for(i=0;i<10;i++)
	    	for(j=0;j<10;j++)
	        	mr[i][j]=m1[i][0]*m2[0][j] + m1[i][1]*m2[1][j]  + m1[i][2]*m2[2][j]  
	    		+ m1[i][3]*m2[3][j]  + m1[i][4]*m2[4][j]  + m1[i][5]*m2[5][j]  + m1[i][6]*m2[6][j]  
	    		+ m1[i][7]*m2[7][j]  + m1[i][8]*m2[8][j]  + m1[i][9]*m2[9][j];
		//Espacio de memoria para escribir 
		km1=72;
		if((shmid = shmget(km1,TAM_MEM, IPC_CREAT | 0666))<0){
	    	perror("Error al obtener memoria compartida: shmget");
	    	exit(-1);
		}
		if((shm = shmat(shmid,NULL, 0))== (char *) -1){
	    	perror("Error al enlazar la memoria compartida: shmat");
	    	exit(-1);
		}
		//Semaforo de escritura
		k=0;
		while(k<1){
			s=shm;
			nsops=2;
			sops[0].sem_num=0;
			sops[0].sem_op=0;
			sops[0].sem_flg=SEM_UNDO;
			sops[1].sem_num=0;
			sops[1].sem_op=1;
			sops[1].sem_flg=SEM_UNDO|IPC_NOWAIT;
			if((j=semop(semid,sops,nsops))==-1){
				perror("semop: error en operacion del semaforo\n");
			}
			else {
				printf("\n\nProceso Hijo - escribiendo matriz de resultados\n");
				//Escribimos en la memoria
				for(i=0;i<10;i++)
	    			for(j=0;j<10;j++)
	        			*s++=mr[i][j];
				nsops=1;
				sops[0].sem_num=0;
				sops[0].sem_op=-1;
				sops[0].sem_flg=SEM_UNDO|IPC_NOWAIT;
				if((j=semop(semid,sops,nsops))==-1){
					perror("semop: error en operacion del semaforo\n");
				}
				else printf("Proceso Hijo regresa el control del semaforo\n");
				sleep(1);
			}
			++k;
		}
		//Leemos las matrices a mandar
		fin = fopen("matriz2.in","r");
		for(i=0;i<10;i++)
			for(j=0;j<10;j++)
				fscanf(fin, "%d",&m1[i][j]);
		for(i=0;i<10;i++)
			for(j=0;j<10;j++)
				fscanf(fin,"%d",&m2[i][j]);
		fclose(fin);
		//Abrimos la memoria 1
		km1=71;
		if((shmid = shmget(km1,TAM_MEM, IPC_CREAT | 0666))<0){
	    	perror("Error al obtener memoria compartida: shmget");
	    	exit(-1);
		}
		if((shm = shmat(shmid,NULL, 0))== (char *) -1){
	    	perror("Error al enlazar la memoria compartida: shmat");
	    	exit(-1);
		}
		//Creamos al nieto
		if((pid=fork())<0){
			perror("fork: error al crear proceso\n");
			exit(1);
		}
		if(pid==0){ //Grandsons stuff
			i=j=k=0;
			while(k<2){
				s=shm;
				nsops=2;
				sops[0].sem_num=0;
				sops[0].sem_op=0;
				sops[0].sem_flg=SEM_UNDO;
				sops[1].sem_num=0;
				sops[1].sem_op=1;
				sops[1].sem_flg=SEM_UNDO|IPC_NOWAIT;
				if((j=semop(semid,sops,nsops))==-1){
					perror("semop: error en operacion del semaforo\n");
				}
				else {
					printf("\n\nProceso Nieto - leyendo matriz %d\n",k+1);
					//Escribimos en la memoria
					if(k==0){
						for(i=0;i<10;i++)
		    				for(j=0;j<10;j++)
		        				m1[i][j]=*s++;
		        	}
		        	if(k==1){
						for(i=0;i<10;i++)
		    				for(j=0;j<10;j++)
		        				m2[i][j]=*s++;
		        	}
					nsops=1;
					sops[0].sem_num=0;
					sops[0].sem_op=-1;
					sops[0].sem_flg=SEM_UNDO|IPC_NOWAIT;
					if((j=semop(semid,sops,nsops))==-1){
						perror("semop: error en operacion del semaforo\n");
					}
					else printf("Proceso Nieto regresa el control del semaforo\n");
					sleep(3);
				}
				++k;

			}
			for(i=0;i<10;i++)
				for(j=0;j<10;j++)
					m1[i][j]+=m2[i][j];	
			//Espacio de memoria para escribir 
			km1=73;
			if((shmid = shmget(km1,TAM_MEM, IPC_CREAT | 0666))<0){
		    	perror("Error al obtener memoria compartida: shmget");
		    	exit(-1);
			}
			if((shm = shmat(shmid,NULL, 0))== (char *) -1){
		    	perror("Error al enlazar la memoria compartida: shmat");
		    	exit(-1);
			}
			s=shm;
			*s='\0';
			k=i=j=0;
			//Semaforo de escritura
			while(k<1){
				s=shm;
				nsops=2;
				sops[0].sem_num=0;
				sops[0].sem_op=0;
				sops[0].sem_flg=SEM_UNDO;
				sops[1].sem_num=0;
				sops[1].sem_op=1;
				sops[1].sem_flg=SEM_UNDO|IPC_NOWAIT;
				if((j=semop(semid,sops,nsops))==-1){
					perror("semop: error en operacion del semaforo\n");
				}
				else {
					printf("\n\nProceso Nieto - escribiendo matriz de resultados\n");
					//Escribimos en la memoria
					for(i=0;i<10;i++)
		    			for(j=0;j<10;j++)
		        			*s++=m1[i][j];
					nsops=1;
					sops[0].sem_num=0;
					sops[0].sem_op=-1;
					sops[0].sem_flg=SEM_UNDO|IPC_NOWAIT;
					if((j=semop(semid,sops,nsops))==-1){
						perror("semop: error en operacion del semaforo\n");
					}
					else printf("Proceso Hijo regresa el control del semaforo\n");
					sleep(1);
				}
				++k;
			}
			exit(1);
		}
		//Mandamos matrices al nieto
		i=j=k=0;
		while(k<2){
			s=shm;
			nsops=2;
			sops[0].sem_num=0;
			sops[0].sem_op=0;
			sops[0].sem_flg=SEM_UNDO;
			sops[1].sem_num=0;
			sops[1].sem_op=1;
			sops[1].sem_flg=SEM_UNDO|IPC_NOWAIT;
			if((j=semop(semid,sops,nsops))==-1){
				perror("semop: error en operacion del semaforo\n");
			}
			else {
				printf("\n\nProceso Hijo - escribiendo matriz %d\n",k+1);
				//Escribimos en la memoria
				if(k==0){
					for(i=0;i<10;i++)
	    				for(j=0;j<10;j++)
	        				*s++=m1[i][j];			
	        	}
	        	if(k==1){
					for(i=0;i<10;i++)
	    				for(j=0;j<10;j++)
	        				*s++=m2[i][j];			
	        	}
				nsops=1;
				sops[0].sem_num=0;
				sops[0].sem_op=-1;
				sops[0].sem_flg=SEM_UNDO|IPC_NOWAIT;
				if((j=semop(semid,sops,nsops))==-1){
					perror("semop: error en operacion del semaforo\n");
				}
				else printf("Proceso hijo regresa el control del semaforo\n");
				sleep(3);
			}
			++k;
		}
	    exit(1);
	}
	//Padre escribe al hijo
	while(k<2){
		s=shm;
		nsops=2;
		sops[0].sem_num=0;
		sops[0].sem_op=0;
		sops[0].sem_flg=SEM_UNDO;
		sops[1].sem_num=0;
		sops[1].sem_op=1;
		sops[1].sem_flg=SEM_UNDO|IPC_NOWAIT;
		if((j=semop(semid,sops,nsops))==-1){
			perror("semop: error en operacion del semaforo\n");
		}
		else {
			printf("\n\nProceso Padre - escribiendo matriz %d\n",k+1);
			//Escribimos en la memoria
			if(k==0){
				for(i=0;i<10;i++)
    				for(j=0;j<10;j++)
        				*s++=m1[i][j];			
        	}
        	if(k==1){
				for(i=0;i<10;i++)
    				for(j=0;j<10;j++)
        				*s++=m2[i][j];			
        	}
			nsops=1;
			sops[0].sem_num=0;
			sops[0].sem_op=-1;
			sops[0].sem_flg=SEM_UNDO|IPC_NOWAIT;
			if((j=semop(semid,sops,nsops))==-1){
				perror("semop: error en operacion del semaforo\n");
			}
			else printf("Proceso Padre regresa el control del semaforo\n");
			sleep(1);
		}
		++k;
	}
	//Memoria 2
	km1=72;
	if((shmid = shmget(km1,TAM_MEM, IPC_CREAT | 0666))<0){
    	perror("Error al obtener memoria compartida: shmget");
    	exit(-1);
	}
	if((shm = shmat(shmid,NULL, 0))== (char *) -1){
    	perror("Error al enlazar la memoria compartida: shmat");
    	exit(-1);
	}
	*s='\0';
	k=i=j=0;
	//Padre lee del hijo
	while(k<1){
		s=shm;
		nsops=2;
		sops[0].sem_num=0;
		sops[0].sem_op=0;
		sops[0].sem_flg=SEM_UNDO;
		sops[1].sem_num=0;
		sops[1].sem_op=1;
		sops[1].sem_flg=SEM_UNDO|IPC_NOWAIT;
		if((j=semop(semid,sops,nsops))==-1){
			perror("semop: error en operacion del semaforo\n");
		}
		else {
			printf("\n\nProceso Padre - leyendo matriz resultante\n");
			//Escribimos en la memoria
        	for(i=0;i<10 && *s!='\0';i++)
	    		for(j=0;j<10;j++)
	        		mf1[i][j]=*s++;
	       	nsops=1;
			sops[0].sem_num=0;
			sops[0].sem_op=-1;
			sops[0].sem_flg=SEM_UNDO|IPC_NOWAIT;
			if((j=semop(semid,sops,nsops))==-1){
				perror("semop: error en operacion del semaforo\n");
			}
			else printf("Proceso Padre regresa el control del semaforo\n");
			sleep(1);
			++k;
		}
	}
	km1=73;
	if((shmid = shmget(km1,TAM_MEM, IPC_CREAT | 0666))<0){
    	perror("Error al obtener memoria compartida: shmget");
    	exit(-1);
	}
	if((shm = shmat(shmid,NULL, 0))== (char *) -1){
    	perror("Error al enlazar la memoria compartida: shmat");
    	exit(-1);
	}
	s=shm;
	*s='\0';
	k=i=j=0;
	//Padre lee del nieto
	while(k<1){
		s=shm;
		nsops=2;
		sops[0].sem_num=0;
		sops[0].sem_op=0;
		sops[0].sem_flg=SEM_UNDO;
		sops[1].sem_num=0;
		sops[1].sem_op=1;
		sops[1].sem_flg=SEM_UNDO|IPC_NOWAIT;
		if((j=semop(semid,sops,nsops))==-1){
			perror("semop: error en operacion del semaforo\n");
		}
		else {
			printf("\n\nProceso Padre - leyendo matriz resultante 2\n");
			//Escribimos en la memoria
        	for(i=0;i<10 && *s!='\0';i++)
	    		for(j=0;j<10;j++)
	        		mf2[i][j]=*s++;
	       	nsops=1;
			sops[0].sem_num=0;
			sops[0].sem_op=-1;
			sops[0].sem_flg=SEM_UNDO|IPC_NOWAIT;
			if((j=semop(semid,sops,nsops))==-1){
				perror("semop: error en operacion del semaforo\n");
			}
			else printf("Proceso Padre regresa el control del semaforo\n");
			sleep(3);
			if(i>0)++k;
		}
	}
	//Imprimimos las matrices
	puts("DATOS DEL HIJO");
	for(i=0;i<10;i++){
		for(j=0;j<10;j++)
			printf("%.2f ",mf1[i][j]);
		puts("");
	}
	puts("");
	puts("DATOS DEL NIETO");
	for(i=0;i<10;i++){
		for(j=0;j<10;j++)
			printf("%.2f ",mf2[i][j]);
		puts("");
	}
	//Sacampos la inversa de los resultados
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			if(i==j) mfr1[i][j]=mfr2[i][j]=1;
			else mfr1[i][j]=mfr2[i][j]=0;
		}
	}
	for(i=0;i<10;i++){
		float divi=mf1[i][i];
		float divi2=mf2[i][i];
		j=i;
		for(j=i;j<10;j++){
			mf1[i][j]/=divi;
			mfr1[i][j]/=divi;
			mf2[i][j]/=divi2;
			mfr2[i][j]/=divi2;
		}
		int k=0;
		for(k=i+1;k<10;k++){
			float num=mf1[k][i];
			float num2=mf2[k][i];
			for(j=i;j<10;j++){
				mf1[k][j]-=(mf1[i][j]*num);
				mfr1[k][j]-=(mf1[i][j]*num);
				mf2[k][j]-=(mf2[i][j]*num2);
				mfr2[k][j]-=(mf2[i][j]*num2);
			}
		}
	}
	for(i=0;i<10;i++){
		for(j=i+1;j<10;j++){
			mfr1[i][j]-=mf1[i][j];
			mfr2[i][j]-=mf2[i][j];
		}
	}
	//Se guardan la matriz del hijo
	FILE *fout = fopen("MatrizInversa1", "w");
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			fprintf(fout,"%.2f ",mfr1[i][j]);
		}
		fprintf(fout,"\n");
	}
	fclose(fout);
	
	fout = fopen("MatrizInversa2", "w");
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			fprintf(fout,"%.2f ",mfr2[i][j]);
		}
		fprintf(fout,"\n");
	}
	fclose(fout);
	puts("");
	puts("Se han guardado las inversas en los archivos");
	exit(1);
}	
