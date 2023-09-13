#include "Linha.h"
#include "qry.h"

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




char *svglinha(Info current){
    Line* aux = (Line*)current;
    char *svg = malloc(sizeof(char)*300);
    sprintf(svg, "\n\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:%s;stroke-width:2\"/>",aux->x1,aux->y1,aux->x2,aux->y2,aux->cor);
    return svg;
}

bool lineRegiao (Info i, double x1, double y1 , double w, double h)
{
    double x1l = getX1line(i);
    double x2l = getX2line(i);
    double y1l = getY1line(i);
    double y2l  = getY2line(i);

    bool interno = x1l>=x1 && x1l<=x1+w && y1l >= y1 && y1l <=y1+h && x2l>=x1 && x2l<=x1+w && y2l >= y1 && y2l <=y1+h; 
    if(interno){
        buildtxtlin(i,0,0,0,0,0,2);
    }
    return interno;
    
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

void buildtxtlin(Info figure,double menorx,double menory,double bigx,double bigy,int k,int flag)
{   
    Line* p = (Line*)figure;
    FILE *fp = fopen(gettxtuniversalname(),"a");
    if(flag==0){
    fprintf(fp,"[*]inp %d\n",k);
    fprintf(fp,"Cordenadas inseridas: x = %lf  y = %lf\n",menorx,menory);
    fprintf(fp,"Id = %lf\nFigura = Linha\n Outra cordenada: x = %lf y = %lf\n Cor = %s\n\n",p->i,bigx,bigy,p->cor);
 

    }       else if(flag==1){
            fprintf(fp,"[*]dels\n");
             fprintf(fp,"Informacoes da figura removida");
    }   else if(flag == 2){
            fprintf(fp,"[*]sel\n");
    }
    if(flag != 0){
    fprintf(fp,"Coordenadas x1 = %lf  y1 = %lf\n ",p->x1,p->y1);

     fprintf(fp,"Coordenadas x2 = %lf  y2 = %lf \n",p->x2,p->y2);

    fprintf(fp,"Id = %lf\nFigura = Linha\n  Cor = %s\n\n",p->i,p->cor);
     
    }
    fclose(fp);
}