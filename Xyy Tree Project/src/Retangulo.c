#include "Retangulo.h"
#include "qry.h"
typedef struct retangulo
{   
    double i,x,y,w,h;
    char type;
    char corb[10];
    char corp[10];
    

}Rectangle;


Info createElementor(){
    Rectangle *aux = (Rectangle*)malloc(sizeof(Rectangle));
     aux->type = 'r';
    return aux;
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
    sprintf(svg, "\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"%s\" stroke=\"%s\" stroke-width=\"1\"/>\n", aux->x, aux->y, aux->w, aux->h, aux->corp, aux->corb);
    return svg;
}

bool rectangleRegiao (Info i, double x1, double y1 , double w, double h)
{
    double hr = getHrectangle(i);
    double wr = getWrectangle(i);
    double xr = getXrectangle(i);
    double yr = getYrectangle(i);

    bool interno = x1<=xr && y1<=yr && (xr+wr)<=x1+w && (yr+hr) <= y1+h;
    if(interno)
    {
        buildtxtret(i,0,2);
    }
    return interno;
    
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

void buildtxtret(void* figure,int k,int flag)
{
    Rectangle* p =(Rectangle*)figure;
    FILE *fp = fopen(gettxtuniversalname(),"a");
    if(flag==0){
    fprintf(fp,"[*]inp %d\n",k);
    fprintf(fp,"Cordenadas inseridas: x = %lf  y = %lf\n",p->x,p->y);
    }   
        else if(flag==1){
            fprintf(fp,"[*]dels\n");
             fprintf(fp,"Informacoes da figura removida");
    }   else if(flag==2){
            fprintf(fp,"[*]sel\n");
    }
    
    fprintf(fp,"Coordenadas x = %lf  y = %lf ",p->x,p->y);
    fprintf(fp,"Id = %lf\n Figura = Retangulo\n Largura = %lf\n Altura = %lf\n CorBorda = %s CorPreenchimento = %s\n\n",p->i,p->w,p->h,p->corb,p->corp);
    fclose(fp);
}