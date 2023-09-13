#ifndef FILA_H
#define FILA_H
#include "Tree.h"

/*
    Função para criar a fila circular
    Pós-condição: retorna uma fila vazia

*/
Fila create_fila (void* f_aux);

/*
    Função para saber se a fila esta vazia
    Pré-condição: Fila criada
    Pós-condição: retorna 1 para verdadeiro e 0 para falso

*/
int fila_empty(Fila  f_aux);

/*
    Função para saber se a fila esta cheia
    Pré-condição: Fila criada
    Pós-condição: retorna 1 para verdadeiro e 0 para falso

*/
int fila_full(Fila f_aux);
 
/*
    Função para inserir na fila
    Pré-condição: Fila criada, x e y que serão inseridos
    Pós-condição: x e y inseridos na fila

*/
void insertfila(Fila f_aux,double vx,double vy);

/*
    Função para remover o primeiro elemento da fila
    Pré-condição: Fila criada, arquivo que sera escrito as coordenadas removidas
    Pós-condição: primeiro elemento da fila removido e coordenadas reportadas

*/
void removefila(void*  f_aux,FILE* fp);

/*
    Função para dar free em toda a lista
    Pré-condição: Fila criada
    Pós-condição: Fila liberada

*/
void destroyfila(Fila f_aux);

/*
    Função para pegar as coordenadas do começo da fila
    Pré-condição: Fila criada
    Pós-condição: Retorna o x e o y em suas respectivas funções

*/
double getXini(Fila f);
double getYini(Fila f);

/*
    Função para pegar as coordenadas do proximo elemento da fila
    Pré-condição: Fila criada e int i para acompanhar na formula de pegar o sucessor (f->inic + i + 1) % f->capacity
    Pós-condição: Retorna o x e o y em suas respectivas funções

*/
double getXsucessor(Fila f,int i);
double getYsucessor(Fila f,int i);

/*
    Função para saber se existe sucessor na fila
    Pré-condição: Fila criada e int num para acompanhar na formula de saber se existe o sucessor (f->inic + num + 1) % f->capacity
    Pós-condição: Retorna 1 para verdadeiro e 0 para falso

*/
int thereisnext(Fila f, int num);

#endif
