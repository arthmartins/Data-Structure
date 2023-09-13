#ifndef LINHA_H
#define LINHA_H
#include "SRB_Tree.h"


/*
    *Função para alocar memoria e criar a struct da linha
    Pré-condição: nenhuma
    Pós-condição: retorna a struct do circulo criada e alocada
*/
Info createline(double i,double x1,double y1,double x2,double y2,char cor[10]);

/*
    *Função para criar o svg da linha
    Pré-condição: node da linha a ser escrito
    Pós-condição: retorna uma string com informaçoes a colocar no svg
*/
char *svglinha(Info  current);

/*
    *Função para conferir se a informação é do tipo linha
    Pré-condição: info do linha
    Pós-condição: retorna 1 para verdadeiro e 0 para falso
*/
int confereLine(Info l);

/*
    *Funções para setar as informações do linha
    Pré-condição: info do linha e informações a serem setadas
    Pós-condição: informações setadas na struct
*/
void setTypel(Info p,char c);
void setline(Info p,double i, double x, double y, double x2, double y2, char corp[10]);



/*
    *Funções para pegar informações especificas do linha(esta no nome a informação a ser obtida)
    Pré-condição: info do linha
    Pós-condição: informação especifica
*/
double getX1line(Info l);
double getY1line(Info l);
double getX2line(Info l);
double getY2line(Info l);
double getIline(Info l);
char *getCorline(Info l);
void printTxtLine(FILE *txt, Info i);


void makeLMBB(Info p, double *mx1,double *mx2,double *my1,double *my2);
#endif