#ifndef QRY_H
#define QRY_H
#include "Tree.h"
#include "Circulo.h"
#include "Retangulo.h"
#include "Linha.h"
#include "Texto.h"
#include "Lista.h"

/*
    Função para fazer a leitura do qry
    Pré-condição: Arvore criada e Path para pegar os nomes dos arquivos
    Pós-condição: arquivo .qry lido

*/
void readqry(XyyTree tree,Path);

/*
    Função para pegar o nome do arquivo .txt
    Pré-condição:
    Pós-condição: nome do arquvio .txt captado

*/
char *gettxtuniversalname();

#endif