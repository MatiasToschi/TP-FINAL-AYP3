#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int dato, altura;
    struct nodo *izquierdo, *derecho;
}Nodo;

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
    // Si el nodo esta vacio le asigna uno
    if(raiz == NULL){
        raiz = asignar_nodo(dato);
    }
    //si el dato es mayor este se inserta a la derecha
    else if(raiz->dato < dato){
        raiz->derecho = insertar(dato, raiz->derecho);
        //se establece la nueva altura del nodo tomando la altura maxima de sus hijos
        raiz->altura = 1 + maximo(altura(raiz->izquierdo),altura(raiz->derecho));
        if(calculador_de_balance(raiz)== -2){
            //si se desbalancea a la derecha
            // se implementan las rotaciones
            if(raiz->derecho->dato < dato){
                raiz = rotacion_simple_derecha(raiz);
            }else{
                raiz = rotacion_doble_derecha(raiz);
            }
        }
    }
    //si el dato es menor este se inserta a la izquierda
    else if (raiz->dato > dato){
        raiz->izquierdo = insertar(dato, raiz->izquierdo);
        //se establece la nueva altura del nodo tomando la altura maxima de sus hijos
        raiz->altura = 1 + maximo(altura(raiz->izquierdo),altura(raiz->derecho));
        if(calculador_de_balance(raiz) == 2){
            // Si se desbalancea a la izquierda
            // se implementan las rotaciones
            if(raiz->izquierdo->dato > dato){
                raiz = rotacion_simple_izquierda(raiz);
            }else{
                raiz = rotacion_doble_izquierda(raiz);
            }
        }
    }else
    // si no se cumple ninguno de los casos anteriores se asume que el dato ya existe dentro del arbol
    {
        printf("El dato %d ya existe dentro del arbol", dato);
    }
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
    // Si la raiz es 0 no se calcula el balance
    if(raiz == NULL){
        return 0;
    }
    // Se verifica la altura por el metodo altura
    // si retorna 2 el desbalance es a la izquierda
    // si retorna -2 el desbalance es a la derecha
    printf("altura izq %d \n", altura(raiz->izquierdo));
    return altura(raiz->izquierdo) - altura(raiz->derecho);
}

Nodo* nodo_mayor(Nodo* raiz){
    // se guarda el nodo recibido para avanzar sobre sus "hijos"
    Nodo* puntero_nodo = raiz;
    if(raiz != NULL){
        while(puntero_nodo->derecho != NULL){
            puntero_nodo = puntero_nodo->derecho;
        }
    }
    // devuelve el nodo mayor de un arbol/ sub-arbol o en defecto la raiz
    return puntero_nodo;
}

Nodo* nodo_menor(Nodo* raiz){
    // se guarda el nodo recibido para avanzar sobre sus "hijos"
    Nodo* puntero_nodo = raiz;
    if(raiz != NULL){
        while(puntero_nodo->izquierdo != NULL){
            puntero_nodo = puntero_nodo->izquierdo;
        }
    }
    // devuelve el nodo menor de un arbol/ sub-arbol o en defecto la raiz
    return puntero_nodo;
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
            //si tiene izquierdo
            Nodo* auxliar = NULL;
            if(raiz->izquierdo != NULL){
                auxliar = nodo_mayor(raiz->izquierdo);
                raiz->dato = auxliar->dato;
                raiz->izquierdo = eliminar(raiz->izquierdo,auxliar->dato);
            }
            // si tiene derecho
            else if(raiz->derecho != NULL){
                auxliar = nodo_menor(raiz->derecho);
                raiz->dato = auxliar->dato;
                raiz->derecho = eliminar(raiz->derecho, auxliar->dato);
            }
            //no tiene hijos
            else{
                raiz = NULL;
                // en caso de que el nodo no tiene hijos unicamente
                // borra la referencia, y la retorna para volver al
                // nivel anterior y continuar con la recursividad
                return raiz;
            }
			// se ajusta la altura
            raiz->altura = maximo(altura(raiz->izquierdo),altura(raiz->derecho)) + 1;
			// se balancea
            if(calculador_de_balance(raiz)==2){

            }else if(calculador_de_balance(raiz) == -2){

            }
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

int main(){
    Nodo *raiz=NULL;
	int x,i,op;
	i = 0;

	do{
        printf("\n\nINGRESAR UNA OPERACION PARA EL ARBOL AVL:");
        printf("\n1)INSERTAR DATO");
        printf("\n2)ELIMINAR DATO");
        printf("\n3)SALIR DEL PROGRAMA \n");
		scanf("%d",&op);

		switch(op){
			case 1:
			    printf("\nIngrese el valor que desea insertar al arbol:");
			    scanf("%d",&x);
                raiz = insertar(x,raiz);
                if(raiz == NULL){

                }
			    break;

			case 2:
			    printf("\nIngrese el valor que desea eliminar del arbol: ");
			    scanf("%d",&x);
			    break;

		    case 3:
		        printf("Saliendo del programa, adios ");
		        break;
		}
	}while(op > 0 && op < 3);
	return 0;
}

