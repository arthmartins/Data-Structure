#ifndef RETANGULO_H
#define RETANGULO_H
#include "Tree.h"

/*
    *Função para alocar memoria e criar a struct do retangulo
    Pré-condição: nenhuma
    Pós-condição: retorna a struct do retangulo criada e alocada
*/
Info createElementor();


/*
    *Função para criar o svg do retangulo
    Pré-condição: node do retangulo a ser escrito
    Pós-condição: retorna uma string com informaçoes a colocar no svg
*/
char *svgret(Info p);

/*
    *Função para criar o txt com informaçoes do retangulo
    Pré-condição: info do retangulo, inteiro k e flag que servem de auxilio do que escrever
    Pós-condição: cria no arquivo o txt
*/
void buildtxtret(void* figure,int k,int flag);

/*
    *Função para conferir se a informação é do tipo retangulo
    Pré-condição: info do retangulo
    Pós-condição: retorna 1 para verdadeiro e 0 para falso
*/
int confereRectangle(Info r);

/*
    *Funções para setar as informações do retangulo
    Pré-condição: info do retangulo e informações a serem setadas
    Pós-condição: informações setadas na struct
*/
void setTyper(Info p,char c);
void setrectangle(Info p,double i, double x, double y, double w, double h, char corb[10],char corp[10]);

/*
    *Função para verificar se o retangulo esta dentro da regiao
    Pré-condição: info do retangulo, e numeros correspondentes do retangulo da região
    Pós-condição: retorna verdadeiro ou falso
*/
bool rectangleRegiao (Info i, double x1, double y1 , double w, double h);

/*
    *Funções para pegar informações especificas do retangulo(esta no nome a informação a ser obtida)
    Pré-condição: info do retangulo
    Pós-condição: informação especifica
*/
double getXrectangle(Info r);
double getYrectangle(Info r);
double getIrectangle( Info r);
double getHrectangle(Info r);
double getWrectangle(Info r);
char *getCorbrectangle(Info r);
char *getCorprectangle(Info r);


#endif