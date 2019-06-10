#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED

typedef struct nodo{
    int dato, altura;
    struct nodo *izquierdo, *derecho;
}Nodo;

Nodo* asignar_nodo(int dato);
Nodo* insertar(int dato, Nodo* raiz);
Nodo* eliminar(int dato, Nodo* raiz);
void pre_order(Nodo* raiz);
void in_order(Nodo* raiz);
void post_order(Nodo* raiz);
int altura(Nodo* raiz);
int maximo(int a, int b);
void recorrer(Nodo* raiz);

#endif // AVL_H_INCLUDED
