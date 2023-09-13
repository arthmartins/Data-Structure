#include "Circulo.h"
#include "qry.h"
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

bool circleRegiao (Info i, double x1, double y1 , double w, double h)
{
    double rc = getRcircle(i);
    double xc = getXcircle(i);
    double yc = getYcircle(i);

    bool interno = ((xc-rc) >= x1) && ((xc+rc) <= x1+w) && (yc-rc) >= y1 && ((yc +rc) <= y1+h);

    if(interno){
      buildtxtcirc(i,0,2);
    }
    return interno;
    
}

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

void buildtxtcirc(Info figure,int k,int flag)
{
    Circle *p = (Circle*)figure;
    FILE *fp = fopen(gettxtuniversalname(),"a");

    if(flag == 0){
    fprintf(fp,"[*]inp %d\n",k);
    fprintf(fp,"Cordenadas inseridas: x = %lf  y = %lf\n",p->x,p->y);
    }
             else if(flag == 1){
            fprintf(fp,"[*]dels\n");
             fprintf(fp,"Informacoes da figura removida\n");
    }   else if(flag == 2){
            fprintf(fp,"[*]sel\n");
    }
    
    fprintf(fp,"Coordenadas x = %lf  y = %lf ",p->x,p->y);
    fprintf(fp,"Id = %lf\n Figura = Circulo\n Raio = %lf\nCorBorda = %s CorPreenchimento = %s\n\n",p->i,p->r,p->corb,p->corp);
    
    fclose(fp);
}