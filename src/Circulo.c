#include "Circulo.h"

typedef struct circulo
{  
    double i,x,y,r;
    char type;
    char corb[10];
    char corp[10]; 

}Circle; 

Info createElementoc(){
    Circle *aux = (Circle*)malloc(sizeof(Circle));
    aux->type = 'c';
    return aux;
}

int confereCircle(Info c){
  Circle *cc= (Circle*)c;
  
    if(cc->type=='c'){
    return (1);
    
  }
  else{
    return(0);
  }
}

void makeCMBB(Info p, double *mx1,double *mx2,double *my1,double *my2)
{
  Circle* aux = (Circle*)p;
  *mx1 = aux->x - aux->r;
  *my1 = aux->y - aux->r;
  *mx2 = aux->x + aux->r;
  *my2 = aux->y + aux->r;

}

void setTypec(Info p,char c)
{
  Circle* aux = (Circle*)p;
  aux->type = c;
}

void setXc(Info current, double xValue){
    Circle* aux = current;
    aux->x = xValue;
}


void setYc(Info current, double yValue){
    Circle* aux = current;
    aux->y = yValue;
}

void setRaioc(Info current, double raioValue){
    Circle* aux = (Circle*)current;
    aux->r = raioValue;
}

void setIdc(Info current, double idValue){
    Circle* aux =(Circle*)current;
    aux->i = idValue;
}


void setPreenchimentoc(Info current, char* preenchimentoValue){
    Circle* aux = (Circle*)current;
    strcpy(aux->corp, preenchimentoValue);
}


void setContornoc(Info current, char* contornoValue){
    Circle* aux = (Circle*)current;
    strcpy(aux->corb, contornoValue);
}

double getXcircle(Info c){
  double xx=((Circle*)c)->x;
  return(xx);
}

double getYcircle(Info c){
  double yy=((Circle*)c)->y;
  return(yy);
}

double getIcircle(Info c){
  double ii = ((Circle*)c)->i;
  return (ii);
}

double getRcircle(Info c){
  double rr = ((Circle*)c)->r;
  return(rr);
}

char *getCorbcircle(Info c){
    return(((Circle*)c)->corb);
}

char *getCorpcircle(Info c){
    return(((Circle*)c)->corp);
}



char *svgcirc(Info p){
    Circle *c = (Circle*)p;
    char *svg = malloc(sizeof(char)*500);
    sprintf(svg, "\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" stroke-width=\"1\" fill=\"%s\" />\n", c->x, c->y, c->r, c->corb, c->corp);
    return svg;
}

/*bool circleRegiao (Info i, double x1, double y1 , double w, double h)
{
    double rc = getRcircle(i);
    double xc = getXcircle(i);
    double yc = getYcircle(i);

    bool interno = ((xc-rc) >= x1) && ((xc+rc) <= x1+w) && (yc-rc) >= y1 && ((yc +rc) <= y1+h);

    if(interno){
      buildtxtcirc(i,0,2);
    }
    return interno;
    
}*/

void setcircle(Info p, double dx, double dy,double i,double r, char corb[10],char corp[10])
{
    Circle *aux = (Circle*)p;

    setIdc(p,i);
    setXc(p,dx);
    setYc(p,dy);
    setRaioc(p,r);
    setContornoc(p,corb);
    setPreenchimentoc(p,corp);
    
}

void printTxtCircle(FILE *txt, Info i)
{
    Circle *aux = (Circle*)i;
    fprintf(txt,"\nCirculo\nId = %.0lf\nx = %lf y = %lf\nCorBorda = %s CorPreenchimento = %s\nRaio = %lf\n",aux->i,aux->x,aux->y,aux->corb,aux->corp,aux->r);

}