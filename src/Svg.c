#include "Svg.h"
#include "Circulo.h"
#include "Retangulo.h"
#include "Linha.h"
#include "Texto.h"


void makesvgaux(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux){

  //void* i = getInfoXyyT(aux,ix);
  FILE *makesvg = (FILE*)aux;
    
    if(confereLine(i) == 1){
        char *svga = svglinha(i);
        fprintf(makesvg,"%s",svga);
        free(svga);
  }
    else if(confereText(i) == 1){
        char *svgt = svgtexto(i);
        fprintf(makesvg,"%s",svgt);
        free(svgt);
    }
    else if(confereRectangle(i) == 1){
        char *svgr = svgret(i);
        fprintf(makesvg,"%s",svgr);
        free(svgr); 
  }else if(confereCircle(i) == 1){
        char *svgc = svgcirc(i);
        fprintf(makesvg,"%s",svgc);
        free(svgc);    
  } 
    
}


void makesvg(SRbTree tree,FILE* arq)
{
  percursoProfundidade(tree,makesvgaux,arq);

}


void openTagSVG (FILE *arquivo)
{
    fprintf(arquivo,"<svg xmlns=\"http://www.w3.org/2000/svg\">"); 
   
}

void closeTagSVG (FILE *arquivo)
{
    fprintf(arquivo,"\n</svg>");
}