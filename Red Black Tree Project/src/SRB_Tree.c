#include "SRB_Tree.h"
#include "Circulo.h"
#include "Retangulo.h"
#include "Texto.h"
#include "Linha.h"

struct SRB_Tree
{
    struct StNode *root;
    struct StNode *nil;
    double epsilon;
}typedef STree;


typedef struct StNode
{
    double x,y;
    double mx1, mx2, my1, my2,mxs1,mxs2,mys1,mys2;
    Info info;
    struct StNode *right; 
    struct StNode *left;
    struct StNode *father;
    char color;
}Tnode;


SRbTree createSRb(double epsilon)
{
    STree *tree = (STree*)malloc(sizeof(STree));
    tree->epsilon = epsilon;
    tree->root = NULL;
    tree->nil = (Tnode*)malloc(sizeof(Tnode));
    tree->nil->color = 'B';
    tree->nil->left = tree->nil;
    tree->nil->right = tree->nil;
    

    return tree;
}

void getMbbSub(SRbTree t,Node p,double *x1,double *y1, double *x2, double *y2){

    STree *tree = (STree*)t;
    Tnode *node = (Tnode*)p;
 // if(node->right == tree->nil && node->left == tree->nil){
    if(node->right == tree->nil && node->left == tree->nil){
     /* atribui mbb da figura */
     *x1 = node->mx1;  
     *y1 = node->my1; 
     *x2 = node->mx2;
     *y2 = node->my2;
  }
  else{ 
     /* atribui mbb da sub-arvore */
     *x1 = node->mxs1;  
     *y1 = node->mys1;  
     *x2 = node->mxs2;   
     *y2 = node->mys2;
  }
}
double minimo(double x1,double x2){
    if(x1<x2)
    return x1;
    else
    return x2;
}

double maximo(double x1,double x2){
    if(x1>x2)
    return x1;
    else
    return x2;
}

void uneMbb(double x11,double y11,double x12,double y12, double x21, double y21, double x22, double y22, double *xr1, double *yr1, double *xr2,double *yr2)
{
  *xr1 = minimo(x11,x21);
  *xr2 = maximo(x12,x22);
  *yr1 = minimo(y11,y21);
  *yr2 = minimo(y12,y22);
}

void corrigeMbbSubArv(SRbTree t,Node p){
    double xe1,xe2,ye1,ye2,xd1,xd2,yd1,yd2,xf1,yf1,xf2,yf2;
    STree *tree = (STree*)t;
    Tnode *node = (Tnode*)p;
    
    //while(node != tree->nil){ 
    while(node != NULL){ 
     /* Calcula MBB da sub-arvore esquerda */
     //if (node->left != tree->nil){
    if(node->left == tree->nil){
        getMbbSub(tree,node, &xe1,&ye1,&xe2,&ye2); 
     }
     else{
        getMbbSub(tree,node->left,&xe1,&ye1,&xe2,&ye2); 
     }        

     /* Calcula MBB da sub-arvore direita */
     //if(node->right != tree->nil){
        if(node->right != tree->nil){
        getMbbSub(tree,node->right,&xd1,&yd1,&xd2,&yd2); 
     } else{
        getMbbSub(tree,node,&xd1,&yd1,&xd2,&yd2); 
     }

    
        
    uneMbb(xe1,ye1,xe2,ye2,xd1,yd1,xd2,yd2,&xf1,&yf1,&xf2,&yf2);
   
     uneMbb(xf1,yf1,xf2,yf2, node->mx1,node->my1,node->mx2,node->my2,  &node->mxs1,&node->mys1,&node->mxs2,&node->mys2);
     
     node = node->father;
        
        }
}
void LeftRotate(STree *tree,Node node_rotate)
{
    
    Tnode *node = (Tnode*)node_rotate;
    Tnode *aux;
	
	aux = node->right;
	node->right = aux->left;
	if(aux->left != tree->nil){
		aux->left->father = node;
	}

	aux->father = node->father;
	if(aux->father == NULL){
		tree->root = aux;
	}
	else if(node == node->father->left){
		node->father->left = aux;
	}
	else{
		node->father->right = aux;
	}
	
	aux->left = node;
	node->father = aux;
}

void RightRotate(STree *tree,Node node_rotate)
{
    Tnode *node = (Tnode*)node_rotate;
    Tnode *aux;

	aux = node->left;
	node->left = aux->right;
	if(aux->right != tree->nil){
		aux->right->father = node;
	}

	aux->father = node->father;
	if(aux->father == NULL){
		tree->root = aux;
	}
	else if(node == node->father->left){
		node->father->left = aux;	
	}
	else{
		node->father->right = aux;
	}

	aux->right = node;
	node->father = aux;
}

int discover_case(Node node_insert)
{
    Tnode *node = (Tnode*)node_insert;
    if(node->father->father != NULL){

    if(node->father == node->father->father->left){
        return 1;
    }else if(node->father == node->father->father->right){
        return 2;
    }
    }else 
    {
        return 3;
    }
}

void Insert_Fixed(STree *tree,Node node_insert)
{
    Tnode *node = (Tnode*)node_insert;
    while(node != tree->root && node != tree->root->left && node != tree->root->right && node->father->color == 'R'){

		
		if(node->father == node->father->father->left){

			
			if(node->father->father->right->color == 'R'){
				node->father->color = 'B';
				node->father->father->right->color = 'B';
				node->father->father->color = 'R';
				node = node->father->father;
			}
			else{
				if(node == node->father->right){
					node = node->father;
					LeftRotate(tree,node);
				}

				node->father->color = 'B';
				node->father->father->color = 'R';
				RightRotate(tree,node->father->father);
			}
		}
		else{

			if(node->father->father->left->color == 'R'){
				node->father->color = 'B';
				node->father->father->left->color = 'B';
				node->father->father->color = 'R';
				node = node->father->father;
			}
			else{
				if(node == node->father->left){
					node = node->father;
					RightRotate(tree,node);
				}

				node->father->color = 'B';
				node->father->father->color = 'R';
				LeftRotate(tree,node->father->father);
			}
		}
	}

	tree->root->color = 'B';
}



Node insertSRb(SRbTree t, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, Info info)
{
    STree *tree_aux = (STree*)t;
    Tnode **aux = &tree_aux->root;

    Tnode *node = (Tnode*)malloc(sizeof(Tnode));

    node->info = info;
    node->x= x;
    node->y = y;
    node->mx1 = mbbX1;
    node->mx2= mbbX2;
    node->my1= mbbY1;
    node->my2 = mbbY2;
    node->father = tree_aux->nil;
    node->left = tree_aux->nil;
    node->right = tree_aux->nil;
    node->color = 'R';
      

  if(tree_aux->root == NULL) // inserir na raiz
  {
    node->color = 'B';
    node->father = NULL;
    tree_aux->root = node;
    node->mxs1 = mbbX1;
    node->mxs2= mbbX2;
    node->mys1= mbbY1;
    node->mys2 = mbbY2;
    

  }
  else{
    while(*aux != tree_aux->nil)
    {
      
      node->father = *aux;
    
      if(x < (*aux)->x)
      {
        aux = &(*aux)->left;
       
      }
        else if(x - (*aux)->x < tree_aux->epsilon && (*aux)->x - x < tree_aux->epsilon)
        {
        if(y < (*aux)->y)
        {
            aux = &(*aux)->left;
        }else
            aux = &(*aux)->right;
         
        }else{
        aux = &(*aux)->right;
        }
      }
        *aux = node;
        Insert_Fixed(tree_aux,node);
        corrigeMbbSubArv(tree_aux,node);
     }
    
   
}

Node insertBbSRb(SRbTree t, double mbbX1, double mbbY1, double mbbX2, double mbbY2, Info info){
    STree *tree_aux = (STree*)t;
    Tnode **aux = &tree_aux->root;

    Tnode *node = (Tnode*)malloc(sizeof(Tnode));

    node->info = info;
    node->x= mbbX1;
    node->y = mbbY1;
    node->mx1 = mbbX1;
    node->mx2= mbbX2;
    node->my1= mbbY1;
    node->my2 = mbbY2;
    node->father = tree_aux->nil;
    node->left = tree_aux->nil;
    node->right = tree_aux->nil;
    node->color = 'R';
      

  if(tree_aux->root == NULL) // inserir na raiz
  {
    node->color = 'B';
    node->father = NULL;
    tree_aux->root = node;
    

  }
  else{
    while(*aux != tree_aux->nil)
    {
      
      node->father = *aux;
    
      if(mbbX1 < (*aux)->x)
      {
        aux = &(*aux)->left;
       
      }
        else if(mbbX1 - (*aux)->x < tree_aux->epsilon && (*aux)->x - mbbX1 < tree_aux->epsilon)
        {
        if(mbbY1 < (*aux)->y)
        {
            aux = &(*aux)->left;
        }else
            aux = &(*aux)->right;
         
        }else{
        aux = &(*aux)->right;
        }
      }
        *aux = node;
        Insert_Fixed(tree_aux,node);
        
     }
    
}




int verificarInterseccoes(double Max, double Min, double c, double c2)
{
   
    if(Max < c){
        if(Max <=c && c <= Min)
        {
            return true;
        }else if(c<= Max && Max <= c2)
        {
            return true;
        }
    }else{
        if(Max <=c2 && c2 <= Min)
        {
            return true;
        }else if(c<= Min && Min <= c2)
        {
            return true;
        }
    }

    return false;

  
}

void getPartAuxiliar(STree* tree, Tnode *node, double x, double y, double w, double h, Lista list)
{
    if(node==tree->nil)
    {
        return;
    }

    if(verificarInterseccoes(maximo(node->mx1,node->mx2),minimo(node->mx1,node->mx2),x,x+w)==1 && verificarInterseccoes(maximo(node->my1,node->my2),minimo(node->my1,node->my2),y,y+h)==1){
        //Insere na Lista
        
    }
    if(verificarInterseccoes(maximo(node->left->mx1,node->left->mx2),minimo(node->left->mx1,node->left->mx2),x,x+w)==1 && verificarInterseccoes(maximo(node->left->my1,node->left->my2),minimo(node->left->my1,node->left->my2),y,y+h)==1){
        getPartAuxiliar(tree,node->left,x,y,w,h,list);
    }
    

    if(verificarInterseccoes(maximo(node->right->mx1,node->right->mx2),minimo(node->right->mx1,node->right->mx2),x,x+w)==1 && verificarInterseccoes(maximo(node->right->my1,node->right->my2),minimo(node->right->my1,node->right->my2),y,y+h)==1){
        getPartAuxiliar(tree,node->right,x,y,w,h,list);
    }
   
    return;
}

void insertListGetPart(STree *tree,Tnode *node,double x, double y, double w, double h, Lista list)
{

    if(node->x > x && node->x < x+w && node->y > y && node->y < y+h)
    {
        insert(list,node);
       
    }
    
}

void getPartAux( STree *tree,Tnode *node,double x, double y, double w, double h, Lista list)
{
     if(node==tree->nil)
    {
        return;
    }

    insertListGetPart(tree,node,x,y,w,h,list);
    getPartAux(tree,node->left,x,y,w,h,list);
    getPartAux(tree,node->right,x,y,w,h,list);
    
   
}

void getBbPartSRb(SRbTree t, double x, double y, double w, double h, Lista resultado){
    
    STree *tree = (STree*)t;
    Tnode *node = tree->root;

    //getPartAuxiliar(tree,node,x,y,w,h,resultado);
    getPartAux(tree,node,x,y,w,h,resultado);

}

Info getInfoSRb(SRbTree t, Node n, double *xa, double *ya, double *mbbX1, double *mbbY1, double *mbbX2, double *mbbY2)
{
    Tnode *node = (Tnode*)n;
    STree *tree = (STree*)t; 
    
    if(node==NULL || node==tree->nil)
    {
        return NULL;
    }

    return node->info;
}



bool isInside(Tnode *node,double x,double y,double w,double h){

    if(node->mx1>x && node->mx1 < x+w)
    {
        if(node->mx2 >=x && node->mx2 <= x+w)
        {
            if(node->my1>=y && node->my1 <= y+h)
            {
              if(node->my2>=y && node->my2 <= y+h){
                
                return true;
              }  
            }
        }
    }
    return false;
}

void getBbSRb(SRbTree t, double x, double y, double w, double h, Lista resultado)
{
    //Lista list = createlista();
    if(confereEmpty(resultado)==0)
    {
    Node *aux = getBegin(resultado);
    while(aux != NULL)
    {
        Info info = getInfo(resultado,aux); 

        if(!isInside(info,x,y,w,h))
        {   
            Node *aux2 = aux;
            aux = getNext(resultado,aux);
            Removenode_list(resultado,aux2);
        }
        else{
        aux = getNext(resultado,aux);
        }
    }
    }
}

Node auxiliar_getNode(SRbTree t,Node pnode, double x, double y)
{
    Tnode *node = (Tnode*)pnode;
    STree *tree = (STree*)t; 

    if((node->x - x < tree->epsilon && node->y - y < tree->epsilon && y - node->y < tree->epsilon && x - node->x < tree->epsilon )|| node == tree->nil)
    {
        return node;
    }

    else if(x < node->x)
    {
        auxiliar_getNode(tree,node->left,x,y);
    }
    else if(x - node->x < tree->epsilon && node->x - x < tree->epsilon)
    {
        if(y < node->y)
        {
            auxiliar_getNode(tree,node->left,x,y);
        }else{
        auxiliar_getNode(tree,node->right,x,y);
        }
    }else{
        auxiliar_getNode(tree,node->right,x,y);
    }

}


Node getNodeSRb(SRbTree t, double xa, double ya, double *mbbX1, double *mbbY1, double *mbbX2, double *mbbY2)
{
    STree *tree = (STree*)t;  
    Tnode *aux = tree->root;

    if(aux != NULL)
    {
        Node node = auxiliar_getNode(tree,aux,xa,ya);
        return node;
    }

  return NULL;
  
}

Tnode* minValueNode(STree *tree,Tnode* node)          
{
    Tnode *aux = node;
  
    while (aux->left != tree->nil)
        aux = aux->left;
  
    return aux;
}

void RBTransplant(STree *tree,Tnode *u, Tnode *v)
{
   
  
	if(u->father == NULL){
		tree->root = v;
	}
	else if(u == u->father->left){
		u->father->left = v;
	}
	else{
		u->father->right = v;
	}

	v->father = u->father;
}


void RemoveFixUp(SRbTree t,Node Node) 
{
    
    STree *tree = (STree*)t; 
    Tnode *node = (Tnode*)Node;
    Tnode *aux;	

	while(node != tree->root && node->color == 'B'){
		
		if(node == node->father->left){
			aux = node->father->right;

			if(aux->color == 'R'){
				aux->color = 'B';
				node->father->color = 'R';
				LeftRotate(tree,node->father);
				aux = node->father->right;
			}

			if(aux->left->color == 'B' && aux->right->color == 'B'){
				aux->color = 'R';
            
				node = node->father;
			}
			else{

				if(aux->right->color == 'B'){
					aux->color = 'R';
					aux->left->color = 'B';
					RightRotate(tree,aux);
					aux = node->father->right;
				}
            
				aux->color = node->father->color;
				node->father->color = 'B';
               
			    aux->right->color = 'B';
				LeftRotate(tree,node->father);
				node = tree->root;	

			}

		}
		else{
			aux = node->father->left;

			if(aux->color == 'R'){
				aux->color = 'B';
				node->father->color = 'B';
				RightRotate(tree,node->father);
				aux = node->father->left;
			}

			if(aux->left->color == 'B' && aux->right->color == 'B'){
				aux->color = 'R';
				
				node = node->father;
			}
			else{

				if(aux->left->color == 'B'){
					aux->color = 'R';
					aux->right->color = 'B';
					LeftRotate(tree,aux);
					aux = node->father->left;
				}

				aux->color = node->father->color;
				node->father->color = 'B';
				aux->left->color = 'B';
				RightRotate(tree,node->father);
				node = tree->root;

			}
		}

	}

	node->color = 'B';
}

Info RemoveElement(SRbTree t,Node Node)
{
  
    STree *tree = (STree*)t; 
    Tnode *node = (Tnode*)Node;
    Tnode *aux = node;
    Tnode *nodetoFix;

	char auxcolor;

	aux = node;
	auxcolor = aux->color;

	if(node->left == tree->nil){
		nodetoFix = node->right;
		RBTransplant(tree,node, node->right);
        free(node->info);
        free(node);
	}
	else if(node->right == tree->nil){
		nodetoFix = node->left;
		RBTransplant(tree,node, node->left);
        free(node->info);
        free(node);
	}
	else{
		aux = minValueNode(tree,node->right);
		auxcolor = aux->color;

		nodetoFix = aux->right;

		if(aux->father == node){
			nodetoFix->father = aux;
		}
		else{
			RBTransplant(tree,aux, aux->right);
			aux->right = node->right;
			aux->right->father = aux;
		}

		RBTransplant(tree,node, aux);
		aux->left = node->left;
		aux->left->father = aux;
		aux->color = node->color;
        free(node->info);
        free(node);
	}

	if(auxcolor == 'B'){
		RemoveFixUp(tree,nodetoFix);
	}
    
}

Info removeSRb(SRbTree t,double xa, double ya, double *mbbX1, double *mbbY1, double *mbbX2, double *mbbY2){

    STree *tree = (STree*)t; 

    if(tree->root == NULL)
    {
        return NULL;
    }  
    else
    {
        RemoveElement(tree,getNodeSRb(t,xa,ya,mbbX1,mbbY1,mbbX2,mbbY2));
    }

}



// ------------------------------DOT

typedef struct makeDot
{
    STree *tree;
    FILE *dot;
}dt;

int findTypeofFigureTree(Tnode *node){
    
    
    if(confereLine(node->info))
    {
        return 3;

   
    }else if(confereRectangle(node->info))
    {
        return 2;
    }
    else if(confereText(node->info))
    {
        return 4;
    } 
    else if(confereCircle(node->info)){
        return 1;
    }
}

double getIdFigureT(Tnode *node){
    int type = findTypeofFigureTree(node);
     switch (type)
    {
    case 1:
        return getIcircle(node->info);
        break;
    case 2:
        return getIrectangle(node->info);
        break;
    case 3:
        return getIline(node->info);
        break;
    case 4:
        return getItext(node->info);
        break;
    default:
        break;
    }

}

void imprimeFinalDot(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux){
    dt* dd = (dt*)aux;
    STree *tree = dd->tree;
    FILE *dot = dd->dot;
    Tnode *node = (Tnode*)i;

    if(node->right == tree->nil)
    {
        fprintf(dot,"%.0lf -> nil\n",getIdFigureT(node));
    }else
    {   
        fprintf(dot,"%.0lf -> %.0lf\n",getIdFigureT(node),getIdFigureT(node->right));
    }

    if(node->left== tree->nil)
    {
        fprintf(dot,"%.0lf -> nil\n",getIdFigureT(node));
    }else
    {   
        fprintf(dot,"%.0lf -> %.0lf\n",getIdFigureT(node),getIdFigureT(node->left));
    }

}


void imprimeNameDot(Tnode *node, FILE *dot)
{
    if(node->color == 'B'){
    fprintf(dot,"%.0lf [fillcolor=black fixedsize=shape label=\"id:%.0lf x=%.2lf y= %.2lf\" width=2]\n",getIdFigureT(node),getIdFigureT(node),node->x,node->y);
    }
    else{
        fprintf(dot,"%.0lf [fillcolor=red fixedsize=shape label=\"id:%.0lf x=%.2lf y= %.2lf\" width=2]\n",getIdFigureT(node),getIdFigureT(node),node->x,node->y);
    }
}



void makeDot(STree *tree,Tnode *node,FILE *dot){
    if(node == tree->nil)
    {
        return;
    }
   
    imprimeNameDot(node,dot);
    makeDot(tree,node->left,dot);
    makeDot(tree,node->right,dot);
}

void openDot(FILE* dot){
    fprintf(dot,"digraph G {\n");
    fprintf(dot,"node [margin=0 fontcolor=white fontsize=14 width=0.5 shape=box style=filled]\n");
    fprintf(dot,"edge [fontcolor=grey fontsize=12]\n");
    fprintf(dot,"nil [fillcolor=black shape=point]\n");
    
}

void closeDot(FILE *dot){
    fprintf(dot,"}");
}

void printSRb(SRbTree t, char *nomeArq){
    STree *tree= (STree*)t;
    Tnode *node = tree->root;
    printf("%s",nomeArq);
    FILE *dot = fopen(nomeArq,"w");
    openDot(dot);
    makeDot(tree,node,dot);
    dt *d = (dt*)malloc(sizeof(dt));
    d->tree = tree;
    d->dot = dot;
    percursoLargura(tree,imprimeFinalDot,d);
    closeDot(dot);
    fclose(dot);
    free(d);

}
// ----------------------------------------------------------------------------

void auxiliarLargura(STree *tree,Tnode *node,FvisitaNo f,void *aux){

    int ind;
    for(ind=0;ind<2;ind++){
    if(ind==0 && node->left!=tree->nil){
      f(node->left,node->left->x,node->left->y,node->left->mx1,node->left->my1,node->left->mx2,node->left->my1,aux);
  
    }

    if(ind==1 && node->right!=tree->nil){
      f(node->right,node->right->x,node->right->y,node->right->mx1,node->right->my1,node->right->mx2,node->right->my1,aux);
 
    }
    }
   
}

void auxiliarLargura2(STree *tree,Tnode *node,FvisitaNo f,void *aux){
   if(node->left!=tree->nil){
   
    auxiliarLargura(tree,node->left,f,aux);
   
  }
 
  if(node->right!=tree->nil){
  
    auxiliarLargura(tree,node->right,f,aux);
  }
  
  if(node->left!=tree->nil){
  
    auxiliarLargura2(tree,node->left,f,aux);
    
  }
  if(node->right!=tree->nil){
    auxiliarLargura2(tree,node->right,f,aux); 
  }
  
}

void percursoLargura(SRbTree t, FvisitaNo f, void *aux){

    STree *tree= (STree*)t;
    Tnode *node = tree->root;

    f(node,node->x,node->y,node->mx1,node->my1,node->mx2,node->my1,aux);
    
    auxiliarLargura(tree,node,f,aux);
    auxiliarLargura2(tree,node,f,aux);
}

void auxiliarSimetrico(STree *tree,Tnode *node, FvisitaNo f, void *aux){

  if(node == tree->nil)
  {
    return;
  }
  else{
    auxiliarSimetrico(tree,node->left,f,aux);
    auxiliarSimetrico(tree,node->right,f,aux);
    f(node->info,node->x,node->y,node->mx1,node->my1,node->mx2,node->my1,aux);
    
  }
}

void percursoSimetrico(SRbTree t, FvisitaNo fVisita, void *aux){
     
    STree *tree= (STree*)t;
    Tnode *auxNode = tree->root;
    auxiliarSimetrico(tree,auxNode,fVisita,aux);

}

void auxiliarProfundidade(STree *tree,Tnode *node, FvisitaNo f, void *aux){

  if(node == tree->nil)
  {
    return;
  }

  else{

    f(node->info,node->x,node->y,node->mx1,node->my1,node->mx2,node->my1,aux);
    auxiliarProfundidade(tree,node->left,f,aux);
    auxiliarProfundidade(tree,node->right,f,aux);
    
  }
}

void percursoProfundidade(SRbTree t, FvisitaNo fVisita, void *aux){

    STree *tree= (STree*)t;
    Tnode *auxNode = tree->root;
    auxiliarProfundidade(tree,auxNode,fVisita,aux);
}


void updateInfoSRb(SRbTree t, Node n, Info i){
    Tnode *node = (Tnode*)n;
    node->info = i;
}


void percorreRemoveAUX(STree *t,Tnode *node, FvisitaNo f, void *aux){
  if(node ==t->nil)
  {
    return;
  }

  else{
    
    percorreRemoveAUX(t,node->left,f,aux);

    percorreRemoveAUX(t,node->right,f,aux);
    
    destroiNOtree(node,node->x, node->y,aux);

  }
}

void percorrePraRemover(SRbTree  t, FvisitaNo f, void *aux)
{

  STree *tree= (STree*)t;
  Tnode *auxNode = tree->root;
  percorreRemoveAUX(tree,auxNode,f,aux);

}

void destroiNOtree (Info i,double x,double y,void *aux){
  Tnode *auxx = (Tnode*)i;
  free(auxx->info);
  free(auxx);
}

void killSRb(SRbTree t){
  void *aux;

  percorrePraRemover(t,destroiNOtree,aux);
  STree *tree= (STree*)t;
  free(tree->nil);
  free(t);
}