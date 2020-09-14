#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int factorial(int f){
	int fact=f;
	if(fact>=1){
    	fact=f*factorial(f-1);
    	return fact;
	}else{
    	return 1;
	}
}
int main (int argc, char *argv[]) {
  int k; 
  printf("\n ***************************************************");
  printf("\n Fuera de la región paralela, se utilizan 4 threads");
  printf("\n ***************************************************");
  printf("\n \n Ingresa un valor para k : ");
  scanf("%d",&k); //Almacena el valor de la variable
  omp_set_num_threads(4);

 	double et = 0.0;
 	double tini, tfin, tiempo;
 	tini = omp_get_wtime(); // Tiempo inicio

  #pragma omp parallel reduction(+:et)
  {
 	int id = omp_get_thread_num();// identificador de hilos
 	int nt = omp_get_num_threads(); // devuelve la cantidad de hilos.
 	double e=0;
 	for (int i=id; i<k; i+=nt){
     	double m = factorial(i);
     	e+=1.0/m;  //e=e+1.0/fact
     	}	et+=e;

     	tfin = omp_get_wtime();// fin del tiempo de ejecución
     	tiempo = tfin - tini; // calculo del tiempo
  }
  printf("El valor de épsilon es: %.10f",et);
  printf("\n Tiempo de ejecucion: %.8f\n", tiempo );
  return 0;
  }
