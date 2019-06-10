#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main(){
    Nodo *raiz=NULL;
	int x,i,op;
	i = 0;

	do{
        printf("\n\nINGRESAR UNA OPERACION PARA EL ARBOL AVL:");
        printf("\n1)INSERTAR DATO");
        printf("\n2)ELIMINAR DATO");
        printf("\n3)SALIR DEL PROGRAMA");
		scanf("%d",&op);

		switch(op){
			case 1:
			    printf("\nIngrese el valor que desea insertar al arbol:");
			    scanf("%d",&x);

			    break;

			case 2:
			    printf("\nIngrese el valor que desea eliminar del arbol:");
			    scanf("%d",&x);
			    break;

		    case 3:
		        printf("Saliendo del programa, adios");
		        break;
		}
	}while(op > 0 && op < 3);
	return 0;
}

