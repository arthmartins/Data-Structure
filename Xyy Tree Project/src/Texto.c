#include "Texto.h"
#include "qry.h"
typedef struct texto
{
double i,x,y; 
char corb[10];
char corp[10];
char a; 
char txto[100]; 
double xanc;
char type;

}Text;



Info createElementot(){
    Text *aux = (Text*)malloc(sizeof(Text));
    aux->type = 't';
    return aux;
}

void setTypet(Info p,char c)
{
  Text* aux = (Text*)p;
  aux->type = c;
}

int confereText(Info t){
    Text *tt = (Text*)t;

    if(tt->type=='t'){
        return(1);
    }
    else{
        return(0);
    }

}

void setXt(Info current, double xValue){
    Text* aux = current;
    aux->x = xValue;
}


void setYt(Info  current, double yValue){
     Text* aux = current;
    aux->y = yValue;
}


void setIdt(Info current, double idValue){
    Text* aux = current;
    aux->i = idValue;
}


void setPreenchimentot(Info current, char* preenchimentoValue){
    Text* aux = current;
    strcpy(aux->corp, preenchimentoValue);
   // return aux;
}


void setContornot(Info current, char* contornoValue){
    Text* aux = current;
    strcpy(aux->corb, contornoValue);
    //return aux;
}

void setTextot(Info current, char* textoValue){
    Text* aux = current;
    strcpy(aux->txto, textoValue);
  //  return aux;
}

void setAncorat(Info current, char ancoraValue){
    Text* aux = current;
    aux->a = ancoraValue;

     if (aux->a=='i'){
                aux->xanc = aux->x;
            } else if (aux->a=='m'){
                aux->xanc = aux->x + (strlen(aux->txto)/2);
            }  else if (aux->a=='f'){
                aux->xanc = aux->x + strlen(aux->txto);
            }
} 

double getXtext(Info t){
    double xx= ((Text*)t)->x;
    return(xx);
}

double getYtext(Info t){
    double yy= ((Text*)t)->y;
    return(yy);
}


double getItext ( Info t){
    double ii = ((Text*)t)->i;
    return (ii);
}

char *getCorbtext(Info t){
    return(((Text*)t)->corb);
}

char *getCorptext(Info t){
    return(((Text*)t)->corp);
}

char getAtext (Info t){
    char aa = ((Text*)t)->a;
    return(aa);
}

char *getTexttext (Info t){
    return(((Text*)t)->txto);
}

char *svgtexto(Info current){
    Text* t = current;
    char *svgtexto = malloc(sizeof(char)*500);
    sprintf(svgtexto, "\n\t<text x=\"%lf\" y=\"%lf\" fill=\"%s\" fill-opacity=\"3\"   stroke=\"%s\">%s</text>", t->x, t->y, t->corp, t->corb, t->txto);
    

    return svgtexto;
}

bool textRegiao (Info i, double x1, double y1 , double w, double h)
{
    double xt = getXtext(i);
    double yt = getYtext(i);

    bool interno = x1<= xt && xt<=x1+w && y1 <= yt && yt<=y1+h;
    if(interno)
    {
        buildtxttex(i,0,2);
    }
    return interno;
    
} 

void settext(Info p,double i, double x, double y, char corb[10],char corp[10], char texto[100], char a)
{
    Text *t = (Text*)p;

    setIdt(t,i);
    setXt(t,x);           
    setYt(t,y);
    setContornot(t,corb);          
    setPreenchimentot(t,corp);      
    setTextot(t,texto);
    setAncorat(t,a);

}

void buildtxttex(void* figure,int k,int flag)
{   
    Text* p = (Text*)figure;
    FILE *fp = fopen(gettxtuniversalname(),"a");
    if(flag ==0){
    fprintf(fp,"[*]inp %d\n",k);
    fprintf(fp,"Cordenadas inseridas: x = %lf  y = %lf\n",p->x,p->y);
    }
            else if(flag == 1){
                fprintf(fp,"[*]dels\n");
             fprintf(fp,"Informacoes da figura removida");
    }  
     else if(flag == 2){
            fprintf(fp,"[*]sel\n");
    }

    fprintf(fp,"Coordenadas x = %lf  y = %lf ",p->x,p->y);
    fprintf(fp,"Id = %lf\nFigura = Text\n CorBorda = %s CorPreenchimento = %s\n Ancora x = %lf\n Ancora y = %lf\n Texto = %s\n\n",p->i,p->corb,p->corp,p->xanc,p->y,p->txto);
   
    fclose(fp);
}