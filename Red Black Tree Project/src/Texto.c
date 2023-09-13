#include "Texto.h"

typedef struct texto
{
double i,x,y; 
char corb[10];
char corp[10];
char a; 
char txto[100]; 
char xanc[10];
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
    Text* aux = (Text*)current;
    aux->a = ancoraValue;

    if (aux->a=='f')
        strcpy (aux->xanc, "end");
    else if (aux->a=='m')
        strcpy (aux->xanc, "middle");
    else if (aux->a=='i')
        strcpy (aux->xanc, "start");
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

char *getTextotext (Info t){
    return(((Text*)t)->txto);
}

char *svgtexto(Info current){
    Text* t = current;
    char *svgtexto = malloc(sizeof(char)*500);
   // if(strcmp(t->txto,">-|-<")==0){
      //  sprintf(svgtexto, "\n\t<text x=\"%lf\" y=\"%lf\" fill=\"%s\" fill-opacity=\"3\"   stroke=\"%s\"> <![CDATA[%s]> </text>", t->x, t->y, t->corp, t->corb,t->txto);
   // }
    sprintf(svgtexto, "\n\t<text x=\"%lf\" y=\"%lf\" fill=\"%s\" fill-opacity=\"1\" text-anchor=\"%s\" stroke=\"%s\"> <![CDATA[%s]]> </text>", t->x, t->y, t->corp, t->xanc, t->corb, t->txto);
    

    return svgtexto;
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

void makeTMBB(Info p, double *mx1,double *mx2,double *my1,double *my2)
{
  Text *aux = (Text*)p;
  *mx1 = aux->x;
  *my1 = aux->y;
  *mx2 = aux->x; //*5 é uma escala para ter o final do texto

  *my2 = aux->y;

}

void printTxtText(FILE *txt, Info i)
{
    Text *aux = (Text*)i;
    fprintf(txt,"\nTexto\nId = %.0lf\nx = %lf y = %lf\nCorBorda = %s CorPreenchimento = %s\nTexto = %s\n",aux->i,aux->x,aux->y,aux->corb,aux->corp,aux->txto);

}