#include <stdio.h>

int main(){
	int n;
	scanf("%d",&n);
	int tam, i, j;
	if(n%2==0) n++;
	for(tam=0;tam<n;tam++){
		if(tam==n/2){
			for(j=0;j<n*3;j++) printf("*");
		}else {
			for(j=0;j<n*3;j++){
				if(j<n){
					if(j>=n/2 && j<=n/2+i) printf("*");
					else printf(" ");
				} else if(j>=n && j<n*2){
					if(j==3*n/2) printf("*");
					else if(j<3*n/2+i+1 && j>3*n/2-i-1) printf("*");
					else printf(" ");
				} else if(j>=n*2){
					if(j%n<i+1) printf("*");
					else printf(" ");
				}
			}
		}
		printf("\n");
		if(tam+1>n/2) i--;
		else i++;
	}
	return 0;
}
