#ifndef CIRCULO_H
#define CIRCULO_H
#include "SRB_Tree.h"

/*
    *Função para alocar memoria e criar a struct do circulo
    Pré-condição: nenhuma
    Pós-condição: retorna a struct do circulo criada e alocada
*/
void* createElementoc();


char *svgcirc(Info p);

/*
    *Função para conferir se a informação é do tipo circulo
    Pré-condição: info do circulo
    Pós-condição: retorna 1 para verdadeiro e 0 para falso
*/
int confereCircle(Info c);

/*
    *Funções para setar as informações do circulo
    Pré-condição: info do circulo e informações a serem setadas
    Pós-condição: informações setadas na struct
*/
void setTypec(Info p,char c);
void setcircle(Info p, double dx, double dy,double i,double r, char corb[10],char corp[10]);
/*
/*
    *Função para verificar se o circulo esta dentro da regiao
    Pré-condição: info do circulo, e numeros correspondentes do retangulo da região
    Pós-condição: retorna verdadeiro ou falso
*/
bool circleRegiao (Info i, double x1, double y1 , double w, double h);
/*

/*
    *Funções para pegar informações especificas do circulo(esta no nome a informação a ser obtida)
    Pré-condição: info do circulo
    Pós-condição: informação especifica
*/
double getXcircle(Info c);
double getYcircle(Info c);
double getIcircle(Info c);
double getRcircle(Info c);
char *getCorbcircle(Info c);
char *getCorpcircle(Info c);


void makeCMBB(Info p, double *mx1,double *mx2,double *my1,double *my2);
void printTxtCircle(FILE *txt, Info i);

#endif