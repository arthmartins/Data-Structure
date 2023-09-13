#include "Tree.h"
#include "Circulo.h"
#include "Retangulo.h"
#include "Linha.h"
#include "Texto.h"

typedef struct root_tree{
  double fd;
  struct Node_tree *root;
  int size_tree;
  int size_tree_r;
  int nRemovidos;
}tree_struc;

typedef struct Node_tree{
  void *data; 
  double x;
  double y;
  struct Node_tree *parent;
  struct Node_tree *left;
  struct Node_tree *center;
  struct Node_tree *right;
  char targetremoved; //n para não removido e s para removido
}node_tree;


XyyTree newXyyTree(double Fd)
{
  tree_struc *new_tree = (tree_struc*)malloc(sizeof(tree_struc));
  new_tree->root = NULL;
  new_tree->size_tree = 0;
  new_tree->size_tree_r = 0;
  new_tree->nRemovidos =0;
  new_tree->fd = Fd; 
  
  return new_tree;
}


Node insertXyyT(XyyTree tree, double x, double y, Info info)
{
    tree_struc *tree_aux = (tree_struc*)tree;
    node_tree **aux = &tree_aux->root;

    node_tree *node = (node_tree*)malloc(sizeof(node_tree));

      node->data = info;
      node->x= x;
      node->y = y;
      node->parent = NULL;
      node->left = NULL;
      node->right = NULL;
      node->center = NULL;
      node->targetremoved = 'n';

  if(tree_aux->root == NULL) // inserir na raiz
  {
    tree_aux->root = node;
  }
  else{
    while(*aux)
    {
      
      node->parent = *aux;
      if(y < (*aux)->y)
      {
        aux = &(*aux)->left;
       
      }
      else if(y >= (*aux)->y)
      {
        if(x < (*aux)->x)
        {
          aux = &(*aux)->center;
          
        }
        else if(x >= (*aux)->x)
        {
          aux = &(*aux)->right;
         
        }
       }
        
      }
     }
    *aux = node;
    tree_aux->size_tree++;

}

Node getNodeXyyT (XyyTree t, double x, double y, double epsilon){

  tree_struc *tree_aux = (tree_struc*)t;
  node_tree **aux = &tree_aux->root;

  while(*aux)
    {
      if(((*aux)->x - x < epsilon && (*aux)->y - y < epsilon && y - (*aux)->y < epsilon && x - (*aux)->x < epsilon )|| aux==NULL)
      {
        
        return *aux;
      }
      else if(y < (*aux)->y)
      {
        aux = &(*aux)->left;
      }
      else if(y >= (*aux)->y)
      {
        if(x < (*aux)->x)
        {
          aux = &(*aux)->center;
        }
        else if(x >= (*aux)->x)
        {
          aux = &(*aux)->right;
        }
       }
    }
      

  return NULL;
  
} 

Info getInfoXyyT (XyyTree t, Node n)
{
  node_tree *aux = (node_tree*)n;
  return aux->data;
}


void figureinside(node_tree *node, double x1,double y1,double x2, double y2,Lista list,FdentroDe f)
{ 
     if(node ==NULL)
  {
    return;
  }
    else{
        if(f(node->data,x1,y1,x2,y2)){
      insert(list,node->data);
   }

      figureinside(node->left,x1,y1,x2,y2,list,f);    
      figureinside(node->center,x1,y1,x2,y2,list,f);
      figureinside(node->right,x1,y1,x2,y2,list,f);
   
    
   }
}

Lista getInfosDentroRegiaoXyyT (XyyTree t, double x1, double y1, double x2, double y2, FdentroDe f)
{
  tree_struc *tree_aux = (tree_struc*)t;
  node_tree *aux = tree_aux->root;
  Lista lista = createlista();
  figureinside(aux,x1,y1,x2,y2,lista,f);
  return lista;
}

void getnodesAuxiliar(node_tree *aux,Lista list,double x1, double y1, double w, double h)
{ 
    
     if(aux ==NULL)
  {
    return;
  }
    else{
        if(aux->x > x1 && aux->x < x1+w && aux->y >y1 && aux->y < y1+h){
        insert(list,aux);
   }

      getnodesAuxiliar(aux->left,list,x1,y1,w,h);    
      getnodesAuxiliar(aux->center,list,x1,y1,w,h); 
      getnodesAuxiliar(aux->right,list,x1,y1,w,h); 
    }
}
Lista getNodesDentroRegiaoXyyT (XyyTree t, double x1, double y1, double w, double h) 
{
  tree_struc *tree_aux = (tree_struc*)t;
  node_tree *aux = tree_aux->root;
  Lista lista = createlista();
  getnodesAuxiliar(aux,lista,x1,y1,w,h);
  return lista;
}



/*void figurehit(XyyTree t,node_tree *node , double x, double y, Lista list,FatingidoPor f)
{
  tree_struc *tree = (tree_struc*)t;
   if(node ==NULL)
  {
    return;
  }
    else{

    if(f(node->data,x,y)){
      lista_inserenofim(list,node->data);
   }
    figurehit(tree,node->left,x,y,list,f);
    figurehit(tree,node->center,x,y,list,f);
    figurehit(tree,node->right,x,y,list,f);
   }
}  */

/*Lista getInfosAtingidoPontoXyyT (XyyTree t, double x, double y, FatingidoPor f) 
{
  tree_struc *tree_aux = (tree_struc*)t;
  node_tree *aux = tree_aux->root;
  Lista lista = inicia();
  figurehit(tree_aux,aux,x,y,lista,f);
  return lista;
} */


FvisitaNo contaNoRemovido (Info i,double x,double y,void *aux){
  int *nRemoved= (int*)aux;
  if(((node_tree*)i)->targetremoved=='s'){
    nRemoved++; //incremento
  }
  aux = nRemoved;
  return(aux);
}


/*FvisitaNo printaNodeTree (Info i,double x,double y, void *aux){
  printf("\n %0.2lf",x);
}
*/
void visitaPaux(node_tree *node, FvisitaNo f, void *aux){
  if(node ==NULL)
  {
    return;
  }

  else{
    
    if(node->targetremoved != 's'){
    f(node->data,node->x,node->y,aux);
    }
    visitaPaux(node->left,f,aux);

    visitaPaux(node->center,f,aux);

    visitaPaux(node->right,f,aux);
    
    

  }
}

void visitaProfundidadeXyyT (XyyTree t, FvisitaNo f, void *aux)
{

  tree_struc *tree= (tree_struc*)t;
  node_tree *auxNode = tree->root;
  visitaPaux(auxNode,f,aux);

}

void visitaLaux(node_tree *node,FvisitaNo f,void *aux){

int ind;
for(ind=0;ind<3;ind++){
  if(ind==0 && node->left!=NULL && node->targetremoved !='s'){
    f(node->left,node->left->x,node->left->y,aux);
  
  }

  if(ind==1 && node->center!=NULL && node->targetremoved !='s'){
    f(node->center,node->center->x,node->center->y,aux);
  
  }

  if(ind==2 && node->right!=NULL && node->targetremoved !='s'){
    f(node->right,node->right->x,node->right->y,aux);
 
  }
}
    if((char*)aux=='t')
    {
     aux = 'c';
   }
}

void visitaLaux2(node_tree *node,FvisitaNo f,void *aux){
   if(node->left!=NULL){
   
    visitaLaux(node->left,f,aux);
    if((char*)aux=='t')
   {
    aux = 'c';
  }
  }
  if(node->center!=NULL){
  
    visitaLaux(node->center,f,aux);
   
  }
  if(node->right!=NULL){
  
    visitaLaux(node->right,f,aux);
  }
  
  if(node->left!=NULL){
  
     if((char*)aux=='c')
   {
    aux = 't';
}
    visitaLaux2(node->left,f,aux);
    
  }
  if(node->center!=NULL){
     if((char*)aux=='c')
   {
    aux = 't';
}
    visitaLaux2(node->center,f,aux);
    
  }
  if(node->right!=NULL){
     if((char*)aux=='c')
   {
    aux = 't';
}
    visitaLaux2(node->right,f,aux);
   
  }
  
}

void visitaLarguraXyyT (XyyTree t, FvisitaNo f, void *aux){
  tree_struc *tree= (tree_struc*)t;
  node_tree *auxNode = tree->root;


  f(auxNode,auxNode->x,auxNode->y,aux);//printar a raiz
  if((char*)aux=='c')
   {
    aux = 't';
  }
  visitaLaux(auxNode,f,aux);
  visitaLaux2(auxNode,f,aux);
} 

void freeXyyt(XyyTree tree_ref,Node node)
{
  tree_struc *t = (tree_struc*)tree_ref;
  node_tree *no = (node_tree*)node;
  if(no ==NULL)
  {
    return;
  }
  else{
    freeXyyt(t,no->left);

    freeXyyt(t,no->center);

    freeXyyt(t,no->right);

    free(no);
  }
}

typedef struct RemoveAssistent{
  node_tree vetorN[15];
  tree_struc *oldt;
  tree_struc *t;
  int indiceAUX;
}RA;

int Identificaparentesco(node_tree *n){
  if(n==NULL || n->parent==NULL){
    return -1;
  }
  node_tree *pai = n->parent;
  if(pai->left==n){
    return(1);
  }
  if(pai->center==n){
    return(2);
  }
  if(pai->right==n){
    return(3);
  }

}
//---------------------------------------------------FUNÇÃO QUICK SORT------------------------------------------------------------------------------------
void quick_sort(node_tree a[], int left, int right) {
    int i, j, y;
    int x;
    i = left;
    j = right;
    x = a[(left + right) / 2].x;
    while(i <= j) {
        while(a[i].x < x && i < right) {
            i++;
        }
        while(a[j].x > x && j > left) {
            j--;
        }
        if(i <= j) {
            y = a[i].x;
            a[i].x = a[j].x;
            a[j].x = y;
            i++;
            j--;
        }
    }
    if(j > left) {
        quick_sort(a, left, j);
    }
    if(i < right) {
        quick_sort(a, i, right);
    }
}

//-------------------------------------------------------------------------------FUNÇÃO VISITA NÓ PARA REMOÇÃO--------------------------------------------------------------------
FvisitaNo OrdenaeInsere (Info i,double x,double y,void *aux){
 RA *ra = (RA*)aux;
 node_tree *auxNode = (node_tree*)i;
 tree_struc *tree = ((RA*)aux)->t;
 int ind,indAux = ra->indiceAUX;

 if(auxNode->targetremoved!='s')
 {

  if(ra->indiceAUX<15){
    ra->vetorN[indAux]= *(node_tree*)i;
    indAux++;
    quick_sort(ra->vetorN,0,indAux);

    if(tree->size_tree<15){
      if(indAux==tree->size_tree){
        for(ind=0;ind<indAux;ind++){
          node_tree element = ra->vetorN[ind];
          insertXyyT(tree,element.x,element.y,element.data);
        }
      }
    }

    else if(indAux==15){
      for (ind=0;ind<15;ind++){
        node_tree element = ra->vetorN[ind];
        insertXyyT(tree,element.x,element.y,element.data);
        indAux++;
      }
    }

  }

  else{
    insertXyyT(tree,auxNode->x,auxNode->y,auxNode->data);
    indAux++;
  }

  ra->indiceAUX = indAux;
 }

  if(indAux-1==ra->oldt->size_tree-ra->oldt->size_tree_r){
    tree_struc *velhaArvore = ra->oldt;
    ra->oldt = ra->t; 
    freeXyyt(velhaArvore,velhaArvore->root);
  }

  return (tree);

}

//-----------------------------------------------------------------------------------------FUNÇÃO REMOVE---------------------------------------------------------------------

void removeNoXyyT (XyyTree t, Node n)
{
  node_tree *nn = (node_tree*)n;
  tree_struc *tt= (tree_struc*)t;
  node_tree *left = nn->left;
  node_tree *center = nn->center;
  node_tree *right = nn->right;
  int auxint = Identificaparentesco(nn); //ELEEEE NÃO É O PAIII, ratinhooooo
  
  switch (auxint)
  {
    case 1:;
      if (left==NULL&&center==NULL&&right==NULL){
        nn->parent->left = NULL;
        free(nn->data);
        free(nn);
      } 

      else 
      {
        if(left!=NULL&&center==NULL&&right==NULL){
          nn->left->parent = nn->parent;
          nn->parent->left = nn->left;
          free(nn->data);
          free(nn);
        }
        if(left==NULL&&center!=NULL&&right==NULL){
          nn->center->parent = nn->parent;
          nn->parent->left = nn->center;
          free(nn->data);
          free(nn);
        }
        if(left==NULL&&center==NULL&&right!=NULL){
          nn->right->parent = nn->parent;
          nn->parent->left = nn->right;
          free(nn->data);
          free(nn);
        }

        if(left!=NULL&&right!=NULL||left!=NULL&&center!=NULL||center!=NULL&&right!=NULL){
          nn->targetremoved = 's';
          tt->size_tree_r = tt->size_tree_r + 1;
          int AUXfd = tt->size_tree_r/tt->size_tree;

          if (AUXfd > tt->fd){
            tree_struc *newT = newXyyTree(tt->fd);
            

            RA *ra=(RA*)malloc(sizeof(RA));
            ra->t = newT;
            ra->oldt = tt;
            ra->indiceAUX = 0;
            
            void *voidRa = &ra;
            visitaLarguraXyyT(tt,OrdenaeInsere,voidRa);
          } 
        }
      }

    break;
    case 2:;

        if (left==NULL&&center==NULL&&right==NULL){
        nn->parent->center = NULL;
        free(nn->data);
        free(nn);
      } 

      else 
      {
        if(left!=NULL&&center==NULL&&right==NULL){
          nn->left->parent = nn->parent;
          nn->parent->center = nn->left;
          free(nn->data);
          free(nn);
        }
        if(left==NULL&&center!=NULL&&right==NULL){
          nn->center->parent = nn->parent;
          nn->parent->center = nn->center;
          free(nn->data);
          free(nn);
        }
        if(left==NULL&&center==NULL&&right!=NULL){
          nn->right->parent = nn->parent;
          nn->parent->center = nn->right;
          free(nn->data);
          free(nn);
        }

        if(left!=NULL&&right!=NULL||left!=NULL&&center!=NULL||center!=NULL&&right!=NULL){
          nn->targetremoved = 's';
          tt->size_tree_r = tt->size_tree_r + 1;
          int AUXfd = tt->size_tree_r/tt->size_tree;

          if (AUXfd > tt->fd){
            tree_struc *newT = newXyyTree(tt->fd);
            

            RA *ra=(RA*)malloc(sizeof(RA));
            ra->t = newT;
            ra->oldt = tt;
            ra->indiceAUX = 0;
            
            void *voidRa = &ra;
            visitaLarguraXyyT(tt,OrdenaeInsere,voidRa);
          } 
        }
      }

    break;

    case 3:;
      if (left==NULL&&center==NULL&&right==NULL){
        nn->parent->right = NULL;
        free(nn->data);
        free(nn);
      } 

      else 
      {
        if(left!=NULL&&center==NULL&&right==NULL){
          nn->left->parent = nn->parent;
          nn->parent->right = nn->left;
          free(nn->data);
          free(nn);
        }
        if(left==NULL&&center!=NULL&&right==NULL){
          nn->center->parent = nn->parent;
          nn->parent->right = nn->center;
          free(nn->data);
          free(nn);
        }
        if(left==NULL&&center==NULL&&right!=NULL){
          nn->right->parent = nn->parent;
          nn->parent->right = nn->right;
          free(nn->data);
          free(nn);
        }

        if(left!=NULL&&right!=NULL||left!=NULL&&center!=NULL||center!=NULL&&right!=NULL){
          nn->targetremoved = 's';
          tt->size_tree_r = tt->size_tree_r + 1;
          int AUXfd = tt->size_tree_r/tt->size_tree;

          if (AUXfd > tt->fd){
            tree_struc *newT = newXyyTree(tt->fd);
            

            RA *ra=(RA*)malloc(sizeof(RA));
            ra->t = newT;
            ra->oldt = tt;
            ra->indiceAUX = 0;
            
            void *voidRa = &ra;
            visitaLarguraXyyT(tt,OrdenaeInsere,voidRa);
          } 
        }
      }

    break;

    default:
      
    break;
  }
  tt->nRemovidos++;
}

//-------------------------------------------DESTROI TREEXyyt--------------------------------------------------//

void percorreRemoveAUX(node_tree *node, FvisitaNo f, void *aux){
  if(node ==NULL)
  {
    return;
  }

  else{
    
    percorreRemoveAUX(node->left,f,aux);

    percorreRemoveAUX(node->center,f,aux);

    percorreRemoveAUX(node->right,f,aux);
    

    f(node,node->x,node->y,aux);

  }
}

void percorrePraRemover(XyyTree t, FvisitaNo f, void *aux)
{

  tree_struc *tree= (tree_struc*)t;
  node_tree *auxNode = tree->root;
  percorreRemoveAUX(auxNode,f,aux);

}

void destroiNOtree (Info i,double x,double y,void *aux){
  node_tree *auxx = (node_tree*)i;
  free(auxx->data);
  free(auxx);
}

void FreeXyyT (XyyTree t){
  void *aux;
  percorrePraRemover(t,destroiNOtree,aux);
  free(t);
}

void _imprimeDadosFigura(Info i,FILE *txt)
{
  
    if(confereLine(i) == 1)
    {   
         fprintf(txt,"[id: %0.2lf] x1: %0.2lf y1: %0.2lf x2: %0.2lf y2: %0.2lf tipo: LINHA cor: %s\n",getIline(i),getX1line(i),getY1line(i),getX2line(i),getY2line(i),getCorline(i));
    }
    else if(confereRectangle(i) == 1)
    {
         fprintf(txt,"[id: %0.2lf] x: %0.2lf y: %0.2lf tipo: RETANGULO cor borda: %s cor preenchimento: %s\n",getIrectangle(i),getXrectangle(i),getYrectangle(i),getCorbrectangle(i),getCorprectangle(i));
    }
    else if(confereText(i) == 1)
    {
         fprintf(txt,"[id: %0.2lf] x: %0.2lf y: %0.2lf tipo: TEXTO cor borda: %s cor preenchimento: %s\n",getItext(i),getXtext(i),getYtext(i),getCorbtext(i),getCorptext(i));
    }
    else if(confereCircle(i) == 1)
    {
         fprintf(txt,"[id: %0.2lf] x: %0.2lf y: %0.2lf tipo: CIRCULO cor borda: %s cor preenchimento: %s\n",getIcircle(i),getXcircle(i),getYcircle(i),getCorbcircle(i),getCorpcircle(i));
       
    }
}

void _imprimeDadosDoNo(node_tree *no,FILE *fp,int margem){
    int i;
    for(i=0;i<margem;i++)
    {
      fprintf(fp," ");
    }
    if(no->targetremoved== 's'){
        fprintf(fp," REMOVIDO: x = %lf y = %lf\n",no->x,no->y);
    }else{
      _imprimeDadosFigura(no->data,fp);
    }
}


void _dumpTreeAux(node_tree *r, FILE *fp, int margem)
{
    if (r == NULL){
      return;
    }

    _imprimeDadosDoNo(r,fp,margem);

   if (r->left != NULL){
      _dumpTreeAux(r->left, fp, margem + 2);
   }
   if (r->center != NULL) {
      _dumpTreeAux(r->center, fp, margem + 2);
   }
   if (r->right != NULL) {
      _dumpTreeAux(r->right, fp, margem + 2);
   }

   
}


void dumpTree(XyyTree t,FILE *fp)
{
  tree_struc* tree = (tree_struc*)t;
  node_tree *aux= tree->root;
  int m =0;
  fprintf(fp,"Número de nós: %d\n Número de nós removidos: %d\n Fator de degradação: %lf\n",tree->size_tree,tree->nRemovidos,tree->fd);
  _dumpTreeAux(aux,fp,m);
}