#include "Retangulo.h"

typedef struct retangulo
{   
    double i,x,y,w,h;
    char type;
    char corb[10];
    char corp[10];
    int energia;
    int riqueza;
    

}Rectangle;


Info createElementor(){
    Rectangle *aux = (Rectangle*)malloc(sizeof(Rectangle));
    aux->type = 'r';
    aux->energia = 0;
    aux->riqueza = 0;
    return aux;
}

void setEnergia(Info i, int v)
{
    Rectangle* aux = (Rectangle*)i;
    aux->energia = v;
}

int getEnergia(Info i)
{
    Rectangle* aux = (Rectangle*)i;
    return aux->energia;
}

void setRiqueza(Info i, int v)
{
    Rectangle* aux = (Rectangle*)i;
    aux->riqueza = v + aux->riqueza;
}

int getRiqueza(Info i)
{
    Rectangle* aux = (Rectangle*)i;
    return aux->riqueza;
}

int getArea(Info i)
{
    Rectangle* aux = (Rectangle*)i;
    int area;
    area = ((aux->x+aux->w)-aux->x)* ((aux->y +aux->h)-aux->y);
    return area;

}

void setTyper(Info p,char c)
{
  Rectangle* aux = (Rectangle*)p;
  aux->type = c;
}

void setXr(Info current, double xValue){
    Rectangle* aux = current;
    aux->x = xValue;
}


void setYr(Info current, double yValue){
    Rectangle* aux = current;
    aux->y = yValue;
}


void setHeightr(Info current, double raioValue){
    Rectangle* aux = current;
    aux->h = raioValue;
}


void setWidhtr(Info current, double larguraValue){
    Rectangle* aux = current;
    aux->w = larguraValue;
}


void setIdr(Info current, double idValue){
    Rectangle* aux = current;
    aux->i = idValue;
}

void setPreenchimentor(Info current, char* preenchimentoValue){
    Rectangle* aux = current;
    strcpy(aux->corp, preenchimentoValue);
}


void setContornor(Info current, char* contornoValue){
    Rectangle* aux = current;
    strcpy(aux->corb, contornoValue);
}


double getXrectangle(Info r){
    double xx=((Rectangle*)r)->x;
    return(xx);
}

double getYrectangle(Info r){
    double yy=((Rectangle*)r)->y;
    return(yy);
}


double getIrectangle(Info r){
    double ii = ((Rectangle*)r)->i;
    return (ii);
}

double getHrectangle(Info r){
    double hh=((Rectangle*)r)->h;
    return(hh);
}

double getWrectangle(Info r){
    double ww=((Rectangle*)r)->w;
    return(ww);
}

char *getCorbrectangle(Info r){
    return(((Rectangle*)r)->corb);
}

char *getCorprectangle(Info r){
    return(((Rectangle*)r)->corp);
}

char *svgret(Info p){
    Rectangle *aux = (Rectangle*)p;
    char *svg = malloc(sizeof(char)*500);
    char cor[10];

    if(aux->energia > 0 && aux->energia < 10)
    {
        strcpy(cor,"#FFCC00");
    }
    else if(aux->energia >= 10 && aux->energia <30)
    {
        strcpy(cor,"#217821");
    }
    else if(aux->energia >= 30)
    {
        strcpy(cor,"#800066");
    }else
    {
        strcpy(cor,"#484537");
    }

    sprintf(svg, "\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"%s\" stroke=\"%s\" stroke-width=\"1\"/>\n", aux->x, aux->y, aux->w, aux->h, cor,cor);
    return svg;
}

void setrectangle(Info p,double i, double x, double y, double w, double h, char corb[10],char corp[10])
{
    Rectangle *rec = (Rectangle*)p;
    
    setIdr(rec,i);
    setXr(rec,x);
    setYr(rec,y);
    setWidhtr(rec,w);
    setHeightr(rec,h);
    setContornor(rec,corb);
    setPreenchimentor(rec,corp);
}

int confereRectangle(Info r)
{
    // Rectangle *rr= (Rectangle*)r;
   // rr=(Rectangle*)r;
    Rectangle *rr = (Rectangle*)r;
    if(rr->type=='r'){
        return 1;
    }
    else{
        return(0);
    }
}

void makeRMBB(Info p, double *mx1,double *mx2,double *my1,double *my2)
{
  Rectangle *aux = (Rectangle*)p;
  *mx1 = aux->x;
  *my1 = aux->y;
  *mx2 = aux->x + aux->w;
  *my2 = aux->y + aux->h;

}

bool isNauAtigido(Info i, double x, double y)
{
    Rectangle *aux = (Rectangle*)i;
    if(x > aux->x && x < aux->x + aux->w && y > aux->y && y < aux->y +aux->h)
    {
        return true;
    }else
    {
        return false;
    }
}

bool rectangleRegiao (Info i, double x1, double y1 , double w, double h,double mx1, double mx2, double my1,double my2)
{

    bool interno = x1<=mx1 && y1<=my1 && (mx1+mx2)<=x1+w && (my1+my2) <= y1+h;
    return interno;
    
}

void printTxtRectangle(FILE *txt, Info i)
{
    Rectangle *aux = (Rectangle*)i;
    fprintf(txt,"\nRetangulo\nId = %.0lf\nx = %lf y = %lf\nCorBorda = %s CorPreenchimento = %s\nw = %lf h = %lf\nEnergia = %d\n",aux->i,aux->x,aux->y,aux->corb,aux->corp,aux->w,aux->h,aux->energia);

}