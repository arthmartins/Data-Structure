#ifndef SVG_H
#define SVG_H
#include "SRB_Tree.h"

/*
        Função para a criação do arquivo svg
        Pré-condição: lista criada, path de entrada do geo e path de saida do svg
        Pós-condição: arquivo svg criado
*/
void makesvg(SRbTree tree,FILE* arq);

/*
    Funções para fechar e abrir a tag do SVG
    Pré-condição: FILE .svg
    Pós-condição: svg aberto ou fechado

*/
void closeTagSVG (FILE *arquivo);
void openTagSVG (FILE *arquivo);


#endif
