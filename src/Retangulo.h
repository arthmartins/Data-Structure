#ifndef RETANGULO_H
#define RETANGULO_H
#include "SRB_Tree.h"

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



void makeRMBB(Info p, double *smx1,double *mx2,double *my1,double *my2);
void setEnergia(Info i, int v);
int getEnergia(Info i);
int getArea(Info i);
bool isNauAtigido(Info i, double x, double y);
bool rectangleRegiao (Info i, double x1, double y1 , double w, double h,double mx1, double mx2, double my1,double my2);
void setRiqueza(Info i, int v);
int getRiqueza(Info i);
void printTxtRectangle(FILE *txt, Info i);

#endif