#include "Svg.h"

void makesvgaux(Info i,double x,double y,void *aux){

  //void* i = getInfoXyyT(aux,ix);
  FILE *makesvg = (FILE*)aux;
  
    //  void* figure = getInfoXyyT(aux,i);
         
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
  }

             else  if(confereCircle(i) == 1){
               char *svgc = svgcirc(i);
               fprintf(makesvg,"%s",svgc);
                free(svgc);
       
  }
}


void makesvg(XyyTree tree,FILE* arq)
{
   visitaProfundidadeXyyT(tree,makesvgaux,arq);
   //visitaLarguraXyyT(tree,makesvgaux,arq);
}


void openTagSVG (FILE *arquivo)
{
    fprintf(arquivo,"<svg xmlns=\"http://www.w3.org/2000/svg\">"); 
}

void closeTagSVG (FILE *arquivo)
{
    fprintf(arquivo,"\n</svg>");
}