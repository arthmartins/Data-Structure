#include "geo.h"
#include "Circulo.h"
#include "Retangulo.h"
#include "Texto.h"
#include "Linha.h"
#include "Svg.h"
#include "path.h"
#include "pathauxiliar.h"

void readgeo(XyyTree tree, Path pathh)
{   
     finalgeo(pathh);
     FILE *arquivo = fopen(getgeo(pathh), "r");
    // FILE *arquivo = fopen("comandos.geo", "r");
    //  FILE *svggeo = fopen("svgGEO.svg","w");
     finaloutgeo(pathh);
     finalsvgname(pathh);
     FILE *svggeo = fopen(getsvgname(pathh), "w");
    openTagSVG(svggeo);
    char var;
    double  x,y,i,r,w,h,x2,y2;
    char a;
    char corb[10];
    char *corb2;
    char corp[10];
    char texto[100];
    
   while (fscanf(arquivo,"%c", &var) != -1)
    {
        switch (var)
        {          
        case 'c': ;
        
            void *p = createElementoc();
            fscanf(arquivo, "%lf %lf %lf %lf %s %s", &i,&x,&y,&r,corb,corp);
            setcircle(p,x,y,i,r,corb,corp);
            setTypec(p,'c');
            insertXyyT(tree,x,y,p); 
            
            break;

        case 'r': ;

            void *P = createElementor();
            fscanf(arquivo, "%lf %lf %lf %lf %lf %s %s", &i,&x,&y,&w,&h,corb,corp);
            setrectangle(P,i,x,y,w,h,corb,corp);
            insertXyyT(tree,x,y,P);
            
        break;

         case 'l': ;

            fscanf(arquivo,"%lf %lf %lf %lf %lf %s" ,&i,&x,&y,&x2,&y2,corp);
            void *l = createline(i,x,y, x2,y2,corp);
            insertXyyT(tree,x,y,l);
            
            break;

        case 't': ;

            
            void *t = createElementot();

            fscanf(arquivo, "%lf %lf %lf %s %s %c %[^\n]",&i,&x,&y,corb,corp,&a,texto);
            //fgets(texto,100,arquivo);
            settext(t,i,x,y,corb,corp,texto,a);
            setTypec(t,'t');
            insertXyyT(tree,x,y,t);

            break;
    
            default:
            break;

        }       
    }
    makesvg(tree,svggeo);
    closeTagSVG(svggeo);
    fclose(arquivo); 
    fclose(svggeo);
    
   
}