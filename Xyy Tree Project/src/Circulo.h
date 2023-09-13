#ifndef CIRCULO_H
#define CIRCULO_H
#include "Tree.h"

/*
    *Função para alocar memoria e criar a struct do circulo
    Pré-condição: nenhuma
    Pós-condição: retorna a struct do circulo criada e alocada
*/
void* createElementoc();

Info createCircle(double i,double x,double y, double r,char corb[10], char corp[10]);
/*
    *Função para criar o svg do circulo
    Pré-condição: node do circulo a ser escrito
    Pós-condição: retorna uma string com informaçoes a colocar no svg
*/
char *svgcirc(Info p);

/*
    *Função para criar o txt com informaçoes do circulo
    Pré-condição: info do circulo, inteiro k e flag que servem de auxilio do que escrever
    Pós-condição: cria no arquivo o txt
*/
void buildtxtcirc(Info figure,int k,int flag);

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
    *Função para verificar se o circulo esta dentro da regiao
    Pré-condição: info do circulo, e numeros correspondentes do retangulo da região
    Pós-condição: retorna verdadeiro ou falso
*/
bool circleRegiao (Info i, double x1, double y1 , double w, double h);

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




#endif