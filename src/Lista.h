#include "bibliotecas.h"
#ifndef LISTA_H
#define LISTA_H
#include "bibliotecas.h"

typedef void *nodep;
/*  Função para cria uma lista vazia.
    Retorna: ponteiro para a lista criada.
*/
Lista createlista();


/*
    Função para pegar o primeiro node da lista.
    Pré-condição: lista não vazia.
    Pós-condição: retorna um void* para primeiro node da lista.

*/
nodep getBegin(Lista listacurrent);

/*
    Função para pegar o ultimo node da lista.
    Pré-condição: lista não vazia.
    Pós-condição: retorna um void* para o ultimo node da lista.

*/
nodep getLast(Lista listacurrent);

/*
    Função para pegar o proximo node da lista.
    Pré-condição: lista não vazia, node atual
    Pós-condição: retorna um void* para o proximo node da lista.

*/
nodep getNext(Lista listacurrent, nodep current);

/*
    Função para pegar o node anterior da lista.
    Pré-condição: lista não vazia, node atual
    Pós-condição: retorna um void* para o node anterior da lista.

*/
nodep getPrev(Lista listacurrent, nodep current);

/*
    Função para pegar a info(void* das struct das formas geometricas) do node.
    Pré-condição: lista não vazia, node atual
    Pós-condição: retorna um void* com informação que esta no void* do node

*/
nodep getInfo(Lista l, nodep current);


/*  Confere se a lista esta vazia
    Pré-condição: lista criada
    Pós-condição: retorna 1 se a lista estiver vazia, 0 caso contrário
*/
int confereEmpty(Lista L);

/*  Função para inserir uma struct na lista
    Pré-condição: lista criada, struct a ser inserida sendo passada como void pointer e uma char para o tipo de struct
    Pós-condição: struct inserida na lista
*/
void insert(Lista Laux,nodep p); 

/*
    Função para destruir a lista
    Pré-condição: lista criada e passada como referencia
    Pós-condição: lista destruida
*/
void destroylista(Lista L_ref);

/*
    Função para destruir por completa a lista, inclusive as info
    Pré-condição: lista criada e passada como referencia
    Pós-condição: lista totalmente destruida
*/
void destroylistacomplete(void* *L_ref);

/*
    Função para remover um no da lista
    Pré-condição: lista não vazia, node para remover
    Pós-condição: no removido da lista

*/
void Removenode_list (Lista list, nodep node_to_remove);

/*
    Função para saber o tamanho da lista
    Pré-condição: lista criada
    Pós-condição: retorna um inteiro para a quantidade de elemntos da lista

*/
int listasize(Lista aux);

#endif   