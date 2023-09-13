#include "fila.h"

typedef struct ElemFila{
  double x;
  double y;
}elemento; 

typedef struct Fila_struc{
  
    void* queue[100];
    int capacity;
    int entradas;
    int inic, fim;

}fila;

Fila create_fila (void* f_aux){
  
  fila *f = (fila*)f_aux;
  f = (fila*)malloc(sizeof(fila));

  f->capacity = 100;
  f->entradas = 0;
  f->inic = 0;
  f->fim = 0;

  return f;

}

int fila_empty(Fila  f_aux){
  fila *f = (fila*)f_aux;
  return (f->entradas == 0);
}

int fila_full(Fila f_aux){
  fila *f = (fila*)f_aux;
  return (f->entradas == f->capacity);
}

void insertfila(Fila f_aux,double vx,double vy)
{
  fila *f = (fila*)f_aux;
  if(fila_full(f)){
    printf("Fila cheia\n");
    return;
  }
  elemento *p = (elemento*)malloc(sizeof(elemento));
  p->x = vx;
  p->y = vy;

  f->queue[f->fim] = p;
  // f->queue[f->fim].x = vx;
  // f->queue[f->fim].y = vy;
  f->fim = (f->fim + 1) % f->capacity;
  f->entradas++;
  
}

void cordremovidastxt(float x,float y,FILE *fp)
{ 
  fprintf(fp,"[*] rmp\n");
  fprintf(fp,"Cordenadas removidas: x = %lf  y = %lf\n\n",x,y);
  
}
int thereisnext(Fila f_aux, int num)
{
  fila *f = (fila*)f_aux;
  if(((f->inic + num + 1) % f->capacity) < f->fim){
    return 1;
  }
  else 
  return 0;
}

void removefila(void*  f_aux,FILE *fp)
{
  fila *f = (fila*)f_aux;
  if(fila_empty(f)){
    printf("Fila vazia\n");
    return;
  }
  elemento *p;

  double x = ((elemento*)f->queue[f->inic])->x;
  double y = ((elemento*)f->queue[f->inic])->y;
  // double x = f->queue[f->inic].x;
  // double y = f->queue[f->inic].y;
  f->inic = (f->inic + 1) % f->capacity;
  f->entradas--;
  cordremovidastxt(x,y,fp);
}

void destroyfila(void *f_aux){
  fila *f = (fila*)f_aux;
   int i= f->inic;
   while(thereisnext(f,i)!=0)
   {
     free((elemento*)f->queue[i]);
     i++;
   }
  free(f);
} 

double getXini(Fila f_aux)
{
  fila *f = (fila*)f_aux;
  return ((elemento*)f->queue[f->inic])->x;
}
int getFinic(Fila f_aux)
{
  fila *f = (fila*)f_aux;
  return f->inic;
}
double getYini(Fila f_aux)
{
  fila *f = (fila*)f_aux;
  return ((elemento*)f->queue[f->inic])->y;
}

double getXsucessor(Fila f_aux,int i)
{
   fila *f = (fila*)f_aux;
   int n = (f->inic + i + 1) % f->capacity;
  return ((elemento*)f->queue[n])->x;
}
double getYsucessor(Fila f_aux,int i)
{
   fila *f = (fila*)f_aux;
   int n = (f->inic + i + 1) % f->capacity;
   return ((elemento*)f->queue[n])->y;
  
}