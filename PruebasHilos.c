#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void *saludo(void *arg);
void gotoxy(int x, int y);

typedef struct datos{
	int x,y;
	char *cadena;
}parametros;

int main(){
	
	pthread_t hilo1, hilo2; /**Se crean dos hilos**/
	
	/**Se crean dos estructuras que contienen los parametros para la funcion que va a ejecutar cada hilo**/
	parametros p1;
	p1.x = 2;
	p1.y = 8;
	p1.cadena = "Hola";
	
	parametros p2;
	p2.x = 6;
	p2.y = 8;
	p2.cadena = "Mundo";
	
	/**
	 * Funcion para inicializar los hilos
	 * Recibe 4 parametros:
	 * 1. Direccion del hilo que creamos
	 * 2. Puntero a struct con los atributos del hilo (se puede pasar NULL)
	 * 3. Direcicon de la funcion que el hilo va a ejecutar(solo funcion sin parametros)
	 * 4. Puntero para pasar un parametro(solo se puede uno por lo que es mejor crear un struct con los parametros necesarios y 
	      pasar el puntero por referencia de ese struct)
	**/
	pthread_create(&hilo1, NULL, &saludo, (void *)&p1);
	pthread_create(&hilo2, NULL, &saludo, (void *)&p2);
	
	/**
	 * Funcion para anadir hilos al Main Thread(el Main Thread no termina hasta que el hilo que se pasa por parametro finalize)
	 * Recibe dos parametros:
	 * 1. Identificador del hilo que vamos a anadir al Main Thread para que se ejecute paralelamente.
	 * 2. Valor de terminacion del hilo (se puede pasar NULL)
	**/
	pthread_join(hilo1, NULL); 
	pthread_join(hilo2, NULL);
	
	return 0;
} 

/**
 * Funcion ejecutada por los hilos.
 * Recibe un void *, esto nos permite que pueda recibir cualquier tipo de parametro.
**/
void *saludo(void *arg){
	parametros *p = (parametros *)arg; //Se castea el parametro de entrada a un puntero a struct de tipo parametro
	int x = p->x; int y = p->y;
	for(int i = 0; i < strlen(p->cadena); i++){
		fflush(stdout);
		gotoxy(x,y);
		x++;
		printf("%c", p->cadena[i]);
		sleep(1); //Se espera 1 seg por iteracion
	}
	printf("\n");
}

/**
 * Funcion para mover la posicion en terminal donde se imprimira la salida estandar mediante coordenadas X y Y.
**/
void gotoxy(int x, int y){
	printf("\033[%d;%df", y,x);
}
