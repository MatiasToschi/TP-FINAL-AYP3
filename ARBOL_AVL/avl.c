#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

Nodo* asignar_nodo(int dato){
    Nodo *n;
    n =(Nodo*) malloc(sizeof(Nodo));
    n->izquierdo = NULL;
	n->derecho = NULL;
    n->dato = dato;
    n->altura = 1;
    return n;
}

Nodo* rotacion_simple_izquierda(Nodo *raiz){
    Nodo* auxiliar = (Nodo*) malloc(sizeof(Nodo));

    auxiliar = raiz->izquierdo;
    raiz->izquierdo = auxiliar->derecho;
    auxiliar->derecho = raiz;

    raiz->altura = maximo(altura(raiz->izquierdo), altura(raiz->derecho)) + 1;
    auxiliar->altura = maximo(altura(auxiliar->izquierdo), altura(raiz)) + 1;
    return auxiliar;
}

Nodo* rotacion_simple_derecha(Nodo *raiz){
    Nodo* auxiliar = (Nodo*) malloc(sizeof(Nodo));

    auxiliar = raiz->derecho;
    raiz->derecho = auxiliar->izquierdo;
    auxiliar->izquierdo = raiz;

	raiz->altura = maximo(altura(raiz->izquierdo), altura(raiz->derecho)) + 1;
	auxiliar->altura = maximo(altura(auxiliar->derecho), altura(raiz)) + 1;
    return auxiliar;
}

Nodo* rotacion_doble_izquierda(Nodo *raiz){
    raiz->izquierdo = rotacion_simple_derecha(raiz->izquierdo);
    return rotacion_simple_izquierda(raiz);
}

Nodo* rotacion_doble_derecha(Nodo *raiz){
    raiz->derecho = rotacion_simple_izquierda(raiz->derecho);
    return rotacion_simple_derecha(raiz);
}


/* Inserta un dato en el arbol, el dato no debe estar ya en el arbol */
Nodo* insertar(int dato, Nodo *raiz){
	if(raiz == NULL){
		return asignar_nodo(dato);
	}else if(dato > raiz->dato){
        raiz->izquierdo = insertar(dato,raiz->izquierdo);
        if((altura(raiz->izquierdo) - altura(raiz->derecho)) == 2){
            if(dato < raiz->izquierdo->dato){
                raiz = rotacion_simple_izquierda(raiz);
            }else{
                raiz = rotacion_doble_izquierda(raiz);
            }
        }
	}else if(dato < raiz->dato){
	    raiz->derecho = insertar(dato, raiz->derecho);
        if((altura(raiz->derecho) - altura(raiz->izquierdo)) == 2){
            printf("el arbol esta desvalanciado hacia la der");
            if(dato > raiz->derecho->dato){
                raiz = rotacion_simple_derecha(raiz);
            }else{
                raiz = rotacion_doble_derecha(raiz);
            }
        }
	}else{
		printf("\nEl dato %d ya se encuentra en el arbol\n",dato);
	}
	raiz->altura = maximo(altura(raiz->derecho),altura(raiz->izquierdo)) + 1;
	return raiz;
}

/* Calcula la altura del arbol o de cualquier subarbol ingresado */
int altura(Nodo *raiz){
    if(raiz == NULL){
        return 0;
    }else{
        return raiz->altura;
    }
}

int calculador_de_balance(Nodo *raiz){
	int altura_izq, altura_der;
    if(raiz==NULL){
        return 0;
    }
    if(raiz->izquierdo==NULL){
        altura_izq = 0;
    }else{
        altura_izq = 1 + raiz->izquierdo->altura;
    }

    if(raiz->derecho==NULL){
        altura_der = 0;
    }else{
        altura_der = 1 + raiz->derecho->altura;
    }
    return(altura_izq - altura_der);
}

/* Elimina un dato del arbol, mientras el arbol no este vacio */
Nodo* eliminar(int dato, Nodo* raiz){
	if(raiz != NULL){
	    //Compara si el dato es menor al donde se encuentra llama al metodo hacia e su hijo izquierdo
        if(dato < raiz->dato){
            raiz->izquierdo = eliminar(dato,raiz->izquierdo);
        }//Compara si el dato es mayor al donde se encuentra
        else if(dato > raiz->dato){
            raiz->derecho = eliminar(dato,raiz->derecho);
        }//se verifica que el valor es el que corresponde con el nodo
        else if(dato == raiz->dato){
            Nodo *auxiliar = NULL;
            //Si tiene izquierdo
            if(raiz->izquierdo != NULL){
                //se guarda el derecho para colocar lo a la derecha del valor a remplazar
                auxiliar = raiz->derecho;
                // el izquierdo toma la posicion de raiz
                raiz = raiz->izquierdo;
				// Este puntero se usa para llegar a la derecha del izquierdo y colocar el resto que quedo en la derecha
                Nodo* puntero_de_avance = raiz;
				// en caso de que el while se rompa ya se puede ocupar directamente esa posicion
				// este termina en el elemento mayor del sub arbol
				while(puntero_de_avance->derecho != NULL){
					// Como raiz esta apuntando al izq se busca el elemento más grande del sub arbol
					puntero_de_avance = puntero_de_avance->derecho;
				}
				// El supuesto hijo derecho sea un nodo o null se coloca como el nuevo elemento mayor del sub arbol
				puntero_de_avance->derecho = auxiliar;
            }else if(raiz->derecho != NULL){
				//se guarda el izquierdo para colocar lo a la izquierda del valor a remplazar
				auxiliar = raiz->izquierdo;
                // el derecho toma la posicion de raiz
                raiz = raiz->derecho;
				// Este puntero se usa para llegar a la derecha del izquierdo y colocar el resto que quedo en la derecha
				Nodo* puntero_de_avance = raiz;
				// en caso de que el while se rompa ya se puede ocupar directamente esa posicion
				// este termina en el elemento menor del sub arbol
				while(puntero_de_avance->izquierdo != NULL){
					puntero_de_avance = puntero_de_avance->izquierdo;
				}
				// El supuesto hijo izquierdo sea un nodo o null se coloca como el nuevo elemento menor del sub arbol
				puntero_de_avance->izquierdo = auxiliar;
			}else{
				// Si no tiene derecho ni izquierdo la direccion de memoria se "limpia"
				// igualandola a NULL y se retorna;
				return raiz = NULL;
			}
			// falta balancear antes de retornar
            return raiz;
        }
	}else{
        //El valor no esta en el arbol
	}
}


/* Recorre el arbol en pre-orden */
void pre_order(Nodo *raiz){
	printf("%d ",raiz->dato);
	if(raiz->izquierdo != NULL){
		pre_order(raiz->izquierdo);
	}
	if(raiz->derecho != NULL){
		pre_order(raiz->derecho);
	}
}

/* Recorre el arbol en in-orden */
void in_order(Nodo *raiz){
	if(raiz->izquierdo != NULL){
		in_order(raiz->izquierdo);
	}
	printf("%d ",raiz->dato);
	if(raiz->derecho != NULL){
		in_order(raiz->derecho);
	}
}

/* Recorre el arbol en post-orden */
void post_order(Nodo *raiz){
	if(raiz->izquierdo != NULL){
		post_order(raiz->izquierdo);
	}
	if(raiz->derecho != NULL){
		post_order(raiz->derecho);
	}
	printf("%d ",raiz->dato);
}

void recorrer(Nodo* raiz){
    printf("\nSecuencia preorder:\n");
    pre_order(raiz);
    printf("\n\nSecuencia inorder:\n");
    in_order(raiz);
    printf("\n\nSecuencia postorder:\n");
    post_order(raiz);
    printf("\n");
}

int maximo(int a, int b){
	return a > b ? a : b;
}
