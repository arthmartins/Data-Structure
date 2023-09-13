#ifndef TEXTO_H
#define TEXTO_H
#include "SRB_Tree.h"

/*
    *Função para alocar memoria e criar a struct do texto
    Pré-condição: nenhuma
    Pós-condição: retorna a struct do texto criada e alocada
*/
Info createElementot();

/*
    *Função para criar o svg do texto
    Pré-condição: node do texto a ser escrito
    Pós-condição: retorna uma string com informaçoes a colocar no svg
*/
char *svgtexto(Info current);


/*
    *Função para conferir se a informação é do tipo texto
    Pré-condição: info do texto
    Pós-condição: retorna 1 para verdadeiro e 0 para falso
*/
int confereText(Info t);

/*
    *Funções para setar as informações do texto
    Pré-condição: info do texto e informações a serem setadas
    Pós-condição: informações setadas na struct
*/
void setTypet(Info p,char c);
void settext(Info p,double i, double x, double y, char corb[10],char corp[10], char texto[100], char a);

/*
    *Funções para pegar informações especificas do texto(esta no nome a informação a ser obtida)
    Pré-condição: info do texto
    Pós-condição: informação especifica
*/
double getXtext(Info t);
double getYtext(Info t);
double getItext ( Info t);
char *getCorbtext(Info t);
char *getCorptext(Info t);
char getAtext (Info t);
char *getTextotext(Info t);

void printTxtText(FILE *txt, Info i);
void makeTMBB(Info p, double *mx1,double *mx2,double *my1,double *my2);

#endif