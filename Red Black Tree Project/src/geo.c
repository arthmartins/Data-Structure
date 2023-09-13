#include "SRB_Tree.h"
#include "Circulo.h"
#include "Retangulo.h"
#include "Texto.h"
#include "Linha.h"
#include "Svg.h"
#include "geo.h"
#include "path.h"
#include "system.h"

void readGeo(SRbTree tree,Path path)
{
    finalgeo(path);
    FILE *arquivo = fopen(getgeo(path), "r");
    finaloutgeo(path);
    finalsvgname(path);
    FILE *svggeo = fopen(getsvgname(path), "w");
    

    // FILE *arquivo = fopen("comandos.geo", "r");
    // FILE *svggeo = fopen("svgGEO.svg","w");
    openTagSVG(svggeo);
    char var;
    double  x,y,i,r,w,h,x2,y2;
    char a;
    char corb[10];
    char *corb2;
    char corp[10];
    char texto[100];
    double mx1, mx2, my1, my2;
    
   while (fscanf(arquivo,"%c", &var) != -1)
    {
        switch (var)
        {          
        case 'c': ;
            
            void *p = createElementoc();
            fscanf(arquivo, "%lf %lf %lf %lf %s %s", &i,&x,&y,&r,corb,corp);
            setcircle(p,x,y,i,r,corb,corp);
            makeCMBB(p,&mx1,&mx2,&my1,&my2);
            insertSRb(tree,x,y, mx1, my1, mx2, my2, p);
            
            break;

        case 'r': ;
            
            void *P = createElementor();
            fscanf(arquivo, "%lf %lf %lf %lf %lf %s %s", &i,&x,&y,&w,&h,corb,corp);
            setrectangle(P,i,x,y,w,h,corb,corp);
            makeRMBB(P,&mx1,&mx2,&my1,&my2);
            insertSRb(tree,x,y, mx1, my1, mx2, my2, P);
            
        break;

         case 'l': ;
        
            fscanf(arquivo,"%lf %lf %lf %lf %lf %s" ,&i,&x,&y,&x2,&y2,corp);
            void *l = createline(i,x,y, x2,y2,corp);
            setTypel(l,'l');
            makeLMBB(l,&mx1,&mx2,&my1,&my2);
            insertSRb(tree,x,y, mx1, my1, mx2,my2, l);
            
            break;

        case 't': ;

            
            void *t = createElementot();
            
            fscanf(arquivo, "%lf %lf %lf %s %s %c %s",&i,&x,&y,corb,corp,&a,texto);
            settext(t,i,x,y,corb,corp,texto,a);
            setTypet(t,'t');
            setAncorat(t,a);
            makeTMBB(t,&mx1,&mx2,&my1,&my2);
            insertSRb(tree,x,y, mx1, my1, mx2, my2, t);
            
            break;
    
            

        }       
    }

    makesvg(tree,svggeo);
    closeTagSVG(svggeo);
    fclose(arquivo); 
    fclose(svggeo);

    finaldotgeo(path);
    printSRb(tree,getdotgeo(path));
    
   
}