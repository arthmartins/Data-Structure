#include "Lista.h"
#include "Circulo.h"
#include "Retangulo.h"
#include "Linha.h"
#include "Texto.h"



typedef struct struc_node_list 
{   
    void *info; 
    struct struc_node_list  *next, *prev;
    
}node_list;


typedef struct struc_lista
{
    int entries;
    struct struc_node_list  *begin;
    struct struc_node_list  *end;
}lista; 



void *createlista()
{ 
    lista *L = (lista*)malloc(sizeof(lista));
    L->begin = NULL;
    L->end = NULL;
    L->entries = 0;

    return L;
}

int listasize(Lista aux)
{
    lista *l = (lista*)aux;
    return l->entries;
}

nodep getBegin(Lista listacurrent){
    lista* listAux =(lista*)listacurrent;
    
    if (listAux->entries == 0 || listAux->begin == NULL)
        return NULL;
    else
    return listAux->begin;

}
nodep getLast(Lista listacurrent)
{
    lista* listAux =(lista*)listacurrent;
    
    if (listAux->entries == 0 || listAux->end == NULL)
        return NULL;
    else
    return listAux->end;
}


nodep getNext(Lista listacurrent, nodep current){
    lista* listAux = (lista*)listacurrent;
    node_list *aux = (node_list*)current; 

    if(aux == NULL){
        return NULL;
    }else{
        return aux->next;
    }


}
nodep getPrev(Lista listacurrent, nodep current){
    lista* listAux = (lista*)listacurrent;
    node_list *aux = (node_list*)current; 

    if(aux == NULL){
        return NULL;
    }else{
        return aux->prev;
    }


}

nodep getInfo(Lista l, nodep current){
    if(l == NULL){
        printf("Erro: Lista não existe\n");
        return 0;
    }

    if(current == NULL){
        printf("Erro: Posic não existe\n");
    }

    node_list *node_lis  = (node_list*)current;
    return node_lis->info;
}



int confereEmpty(void * L)
{
    lista *L1 = (lista*)L;
    if(L1->entries == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void insert(void* Laux, void *p)
{
     lista *L = (lista*)Laux;

   // L = (lista*)Laux;
    node_list *aux;
    aux = (node_list*)malloc(sizeof(node_list));
    aux->info = p;
  
    if(L->begin == NULL){
        L->begin = aux;
        aux->prev = NULL;
    }else{
        aux->prev = L->end;
        aux->prev->next = aux;
    }

    L->end = aux;
    aux->next = NULL;

     L->entries++; 

    
}

 //FUNÇÕES QUE SERIAM UTILIZADAS NO QRY

void destroylista(void* *L_ref) { 

    lista *L = (lista*)L_ref;
    

    node_list *p = L->begin;
    node_list *aux ;
    while(p!=NULL){
    
        aux = p;
        p = p->next;
        free(aux);
    }
    L->entries = 0; 

    free(L);


}
void destroylistacomplete(void* *L_ref) { 

    lista *L = (lista*)L_ref;
    

    node_list *p = L->begin;
    node_list *aux ;
    while(p!=NULL){
    
        aux = p;
        p = p->next;
        free(aux->info);
        free(aux);
    }
    L->entries = 0; 

    free(L);
}

void Removenode_list (Lista list, nodep node_to_remove){
    lista *list_aux = (lista*) list;
    node_list  *node_list_aux = (node_list*)node_to_remove;
    

    if(list_aux->entries == 0)
        return;

    if(!node_list_aux){
        return;
    }
       
    node_list *aux;

    if(node_list_aux->prev){
        aux = node_list_aux->prev;
        aux->next = node_list_aux->next;
    }else{
        list_aux->begin = node_list_aux->next;
    }

    if(node_list_aux->next==NULL){
       aux = node_list_aux->next;
        //list_aux->visit++;
        aux->prev = node_list_aux->prev;
    }else{
        list_aux->end = node_list_aux->prev;
    }

    free(node_list_aux);
    list_aux->entries--;  
}


