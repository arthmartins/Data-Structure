#ifndef FUNCTIONSPATH_H_INCLUDED
#define FUNCTIONSPATH_H_INCLUDED
#include "bibliotecas.h"

/*
    Função para ler o argc e argv
    Pré-condição: argc, argv e struct do path
    Pós-condição: leitura do argv completa

*/
void readArgcArgv(int , char**, Path);

/*
    Função auxiliar para fazer a versão final de entrada geo
    Pré-condição: duas strings
    Pós-condição: retorna a versão de entrada geo final

*/
char *makegeo(char *, char *);

/*
    Função auxiliar para fazer a versão final de saida geo
    Pré-condição: duas strings
    Pós-condição: retorna a versão de saida geo final

*/
char* makeoutgeo(char *,char *);

/*
    Função auxiliar para fazer a versão final do svg
    Pré-condição: uma string
    Pós-condição: retorna a versão svg final

*/
char *makesvgname(char *);

/*
    Função auxiliar para fazer a versão final de entrada qry
    Pré-condição: duas strings
    Pós-condição: retorna a versão de entrada qry final

*/
char *makeqry(char *,char *);

/*
    Função auxiliar para fazer a versão final de saida qry
    Pré-condição: tres strings
    Pós-condição: retorna a versão de saida qry final

*/
char *makeoutqry(char *, char*,char *);

/*
    Função auxiliar para fazer a versão final svg qry
    Pré-condição: uma string
    Pós-condição: retorna a versão  svg qry final

*/
char* makesvgnameqry(char *outqry);

/*
    Função auxiliar para fazer a versão final do txt
    Pré-condição: uma string
    Pós-condição: retorna a versão do txt final

*/
char *maketxtname(char *);
#endif