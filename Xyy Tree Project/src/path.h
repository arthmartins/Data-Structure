#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED

typedef void *Path;

/*
    Função para criar a struct de path
    Pré-condição: 
    Pós-condição: retorna um endereço para a struct de path criada e alocada.

*/
Path createPaths();

/*
    Função para ler os paths de entrada (argv)
    Pré-condição: struct para path, int argc, char* argv[]
    Pós-condição: retorna os paths lidos e colocados na struct de Path

*/
void readpaths(Path , int , char *argv[]);

/*
    Função para fazer o arquivo final de entrada geo
    Pré-condição: Struct de path
    Pós-condição: a versão final do nome do arquivo de entrada geo feito

*/
void finalgeo(Path p);

/*
    Função para fazer o arquivo final de saida geo
    Pré-condição: Struct de path
    Pós-condição: a versão final do nome do arquivo de saida geo feito

*/
void finaloutgeo(Path p);

/*
    Função para fazer o arquivo final do svg geo
    Pré-condição: Struct de path
    Pós-condição: a versão final do nome do svg feito

*/
void finalsvgname(Path p);

/*
    Função para fazer o arquivo final de saida qry
    Pré-condição: Struct de path
    Pós-condição: a versão final do nome do arquivo de saida qry feito

*/
void finaloutqry(Path p);

/*
    Função para fazer o arquivo final de entrada qry
    Pré-condição: Struct de path
    Pós-condição: a versão final do nome do arquivo de entrada qry feito

*/
void finalqry(Path p);

/*
    Função para fazer o arquivo final do svg qry
    Pré-condição: Struct de path
    Pós-condição: a versão final do nome do arquivo do svg qry feito

*/
void finalsvgqry(Path p);

/*
    Função para fazer o arquivo final do txt
    Pré-condição: Struct de path
    Pós-condição: a versão final do nome do arquivo do txt

*/
void finaltxt(Path p);

/*
    Funções para pegar os nomes de seus respectivos arquivos
    Pré-condição: Struct de path
    Pós-condição: string com o nome do respectivo arquivo captada

*/
char *getArqqry(Path p);
char *getgeo(Path p);
char* getqry(Path p);
char *getoutgeo(Path p);
char *getoutqry(Path p);
char *getsvgname(Path p);
char *getsvgqry(Path p);
char *gettxtname(Path p);

/*
    Funções para setar os arquivos de entrada passado pelo argv
    Pré-condição: Struct de path e string com o nome a ser setado
    Pós-condição: nome de seus respectivos arquivos setados

*/
void set_Inpath(Path , char *);
void set_Outpath(Path p, char *out);
void set_ArqGeo(Path p, char* setgeo);
void set_ArqQry(Path p, char* setqry);

/*
    Função para dar free na struct de Path
    Pré-condição: Struct de path
    Pós-condição: Path liberado e desalocado

*/
void freepaths(Path p);
  
#endif