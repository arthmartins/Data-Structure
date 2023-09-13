#include "Linha.h"


typedef struct linha
{  
    char type;
    double i,x1,y1,x2,y2;
    char cor[10];
    

}Line;

void* createline(double i,double x1,double y1,double x2,double y2,char cor[10]){
    Line *l=(Line*)malloc(sizeof(Line));
    //strcpy(l->com,"l");
    l->type = 'l';
    l->i=i;
    l->x1=x1;
    l->y1=y1;
    l->x2=x2;
    l->y2=y2;
    strcpy(l->cor,cor);
   
    return(l);
}
    

int confereLine(Info l){
    Line *ll = (Line*)l;
    
    if(ll->type=='l'){
        return(1);
    }
    else{
        return(0);
    }
}

void setTypel(Info p,char c)
{
    Line* aux= (Line*)p;
    aux->type = c;
}

void setX1l(Info current, double xValue){
    Line* aux = current;
    aux->x1 = xValue;
}

void setX2l(Info current, double xValue){
    Line* aux = current;
    aux->x2 = xValue;
}


void setY1l(Info current, double yValue){
    Line* aux = current;
    aux->y1= yValue;
}

void setY2l(Info current, double yValue){
    Line* aux = current;
    aux->y2= yValue;
}


void setIdl(Info current, double idValue){
     Line* aux = current;
    aux->i = idValue;
}


double getX1line(Info l){
    double xx=((Line*)l)->x1;
    return(xx);
}

double getY1line(Info l){
    double yy=((Line*)l)->y1;
    return(yy);
}

double getX2line(Info l){
    double xx=((Line*)l)->x2;
    return(xx);
}

double getY2line(Info l){
    double yy=((Line*)l)->y2;
    return(yy);
}

double getIline(Info l){
    double ii = ((Line*)l)->i;
    return(ii);
}

char *getCorline(Info l){
    return(((Line*)l)->cor);
}


void setPreenchimentol(Info current, char* preenchimentoValue){
    Line* aux = current;
    strcpy(aux->cor, preenchimentoValue);
}

void makeLMBB(Info p, double *mx1,double *mx2,double *my1,double *my2)
{
  Line* aux = (Line*)p;
  *mx1 = aux->x1;
  *my1 = aux->y1;
  *mx2 = aux->x2;
  *my2 = aux->y2;

}

char *svglinha(Info current){
    Line* aux = (Line*)current;
    char *svg = malloc(sizeof(char)*300);
    sprintf(svg, "\n\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:%s;stroke-width:2\"/>",aux->x1,aux->y1,aux->x2,aux->y2,aux->cor);
    return svg;
}


void setline(Info p,double i, double x, double y, double x2, double y2, char corp[10])
{
    Line *l = (Line*)p;

    setIdl(l,i);
    setX1l(l,x);
    setY1l(l,y);
    setX2l(l,x2);
    setY2l(l,y2);
    setPreenchimentol(l,corp);   
}

void printTxtLine(FILE *txt, Info i)
{
    Line *aux = (Line*)i;
    fprintf(txt,"\nLinha\nId = %.0lf\nx1 = %lf y1 = %lf\nx2 = %lf y2 = %lf\nCor = %s\n",aux->i,aux->x1,aux->y1,aux->x2,aux->y2,aux->cor);

}
