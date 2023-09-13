#include "qry.h"
#include "svg.h"
#include "fila.h"
#include "Circulo.h"
#include "Retangulo.h"
#include "Linha.h"
#include "Texto.h"
#include "path.h"


char* txtname;

void settxtname(Path pathh)
{
    int i = strlen(gettxtname(pathh));
    txtname = (char*)malloc((i+1)*sizeof(char));
    strcpy(txtname,gettxtname(pathh));
    printf("%s",txtname);
}

char *gettxtuniversalname()
{
    return txtname;
}

void opentxt(Path pathh)
{
    FILE *txtnam = fopen(gettxtuniversalname(),"w");
}
//-----------------------------FUNCTION POL---------------------------------------
typedef struct polygon_stuct
{
    double x,y;

}polygon;

double maiorYpol(Lista poglist)
{
    void *node_p = getBegin(poglist);
    polygon *p = getInfo(poglist,node_p);
    double maior = p->y;
    node_p = getNext(poglist,node_p);

    while(node_p!=NULL){
        p = getInfo(poglist,node_p);
        if(maior < p->y)
        {
            maior = p->y;
        }
        node_p = getNext(poglist,node_p);
   }
   return maior;
}

double menorYpol(Lista poglist)
{
    void *node_p = getBegin(poglist);
    polygon *p = getInfo(poglist,node_p);
    double menor = p->y;
    node_p = getNext(poglist,node_p);
    
    while(node_p!=NULL){
        p = getInfo(poglist,node_p);
        if(menor > p->y)
        {
            menor = p->y;
        }
        node_p = getNext(poglist,node_p);
   }
   return menor;
}

double Mlineequation(double x1, double x2, double y1, double y2){
    double m;
    if((x2-x1)<0.00001 && (x1-x2)< 0.00001){
     m =0;
    }else{
    m = (y2 - y1)/(x2-x1);
    }
    return m;
}
double Nlineequation(double x,double y, double m)
{
    double n = y - m*x;
    return n;
}

void interceptations(Lista poglist,double ymen, double ymaior,double d, Lista linespog)
{
    void *node_p;
    polygon *p;
    double x;
    double y1;
    double x1;
    double y2;
    double m;
    double x2;
    double n;
    while(ymen <= ymaior)
    {
    node_p = getBegin(poglist);
    p = getInfo(poglist,node_p);
    y1 = p->y;
    x1 = p->x;
        while(node_p!=NULL)
        {
        if(getNext(poglist,node_p)!=NULL){
        node_p = getNext(poglist,node_p);
        p = getInfo(poglist,node_p);
        y2 = p->y;
        x2 = p->x;
        if((ymen <= y1 && ymen >= y2)||(ymen>=y1 && ymen <= y2)){
            m = Mlineequation(x1,x2,y1,y2);
             n = Nlineequation(x1,y1,m);
            if(m==0){
                x = p->x;
                printf(" %lf ", x);
            }else{
             x = (ymen - n)/m;
            }
            polygon *line = (polygon*)malloc(sizeof(polygon));
            line->x = x;
            line->y = ymen;
            insert(linespog,line);
    
        }
        }else{
             node_p = getBegin(poglist);
             p = getInfo(poglist,node_p);
             y2 = p->y;
             x2 = p->x;
               // printf("\nYMEN = %lf y1 = %lf y2 = %lf", ymen,y1,y2);
            if((ymen <= y1 && ymen >= y2)||(ymen>=y1 && ymen <= y2)){
            m = Mlineequation(x1,x2,y1,y2);
            n = Nlineequation(x1,y1,m);
            if( m == 0){
             x = p->x;
            
            }else{
             x = (ymen - n)/m;
            }
            polygon *line = (polygon*)malloc(sizeof(polygon));
            line->x = x;
            line->y = ymen;
            insert(linespog,line);
            }
        break;
        }
        y1 = y2;
        x1 = x2;
        }
        
        ymen = ymen +d;
    }
}

void makesvgpreenchimento(XyyTree tree,Lista linespog,char corp[10],FILE *svg,double i)
{
    void *node_p = getBegin(linespog);
    polygon *p = getInfo(linespog,node_p);
    double x = p->x;
    double y = p->y;
    
    while(node_p!= NULL)
    {
        if(getNext(linespog,node_p)!=NULL)
        {
            node_p = getNext(linespog,node_p);
            p = getInfo(linespog,node_p);
             if(p->y - y < 0.00001 && y - p->y < 0.00001){
                 
                void *li = createline(i,x,y,p->x,p->y,corp);
                setTypel(li,'l');
                insertXyyT(tree,x,y,li);
                i++;
               
             }
           }
        else
        {
           break;
        }
        x = p->x;
        y = p->y;

    }
}

void preenchepolygon(XyyTree tree,Lista poglist,double d,double esp,double i, char corp[10],FILE *svg){

    double ymen = menorYpol(poglist);
    double ymaior = maiorYpol(poglist);
    Lista linespog = createlista();
    interceptations(poglist,ymen,ymaior,d,linespog);
    makesvgpreenchimento(tree,linespog,corp,svg,i);
    destroylistacomplete(linespog);
}

void insertpoglist(Lista poglist,Fila f)
{
    int i = getFinic(f);
    double x = getXini(f);
    double y = getYini(f);
    polygon *p = (polygon*)malloc(sizeof(polygon));
    p->x =x;
    p->y =y;
    insert(poglist,p);
    while(thereisnext(f,i)==1){
        polygon *p = (polygon*)malloc(sizeof(polygon));

        p->x = getXsucessor(f,i);
        p->y = getYsucessor(f,i);
        insert(poglist,p);
        i++;       
   }
}

void createbordasvg(XyyTree tree,Lista poglist,FILE *svg, char corb[10],double i)
{
     void *node_p = getBegin(poglist);
    polygon *p = getInfo(poglist,node_p);
    double y1 = p->y;
    double x1 = p->x;
    double y2;
    double x2;
    while(node_p!=NULL)
        {
        if(getNext(poglist,node_p)!=NULL){
        node_p = getNext(poglist,node_p);
        p = getInfo(poglist,node_p);
        y2 = p->y;
        x2 = p->x;
        void *li = createline(i,x1,y1,x2,y2,corb);
        insertXyyT(tree,x1,y1,li);
        i++;
        }else{
             node_p = getBegin(poglist);
             p = getInfo(poglist,node_p);
             y2 = p->y;
             x2 = p->x;
        void *li = createline(i,x1,y1,x2,y2,corb);
        insertXyyT(tree,x1,y1,li);
        i++; 
        break;
        }
        y1 = y2;
        x1 = x2;
        }
        
}

void funqPOL(XyyTree tree,Fila f,FILE *svg,char corb[10],char corp[10],double d, double e,double i)
{
   
   Lista poglist = createlista();
   insertpoglist(poglist,f);
   createbordasvg(tree,poglist,svg,corb,i);
   i = i+listasize(poglist);
   
   preenchepolygon(tree,poglist,d,e,i,corp,svg);
    destroylistacomplete(poglist);

}

// --------------------------------FUNCTION INP -------------------------------------------
typedef struct inp_struc
{
    double i;
    Fila fi;
}inp;

int whichline(double x,double y,double x2,double y2)
{
    if(x - x2 < 0.00001 && x2 - x < 0.00001)
    {
        if(y<y2)
        {
            return 3;
        }else {
            return 4;
        }
    }
    else if(x < x2)
    {
        return 1;
    }else
    {
        return 2;
    }
}
void confereI(Info i,double x, double y,void *aux)
{
    //void *i = getInfoXyyT(aux,ix);
    inp *idstruc = (inp*)aux;

     if(confereCircle(i)==1)
        {
            if(getIcircle(i) - idstruc->i < 0.0001 &&  idstruc->i - getIcircle(i) < 0.0001)
            {
                insertfila(idstruc->fi,x,y);
                buildtxtcirc(i,getIcircle(i),0);
            }
        }
        else if(confereRectangle(i)==1)
        {
            if(getIrectangle(i) - idstruc->i < 0.0001 &&  idstruc->i - getIrectangle(i) < 0.0001)
            {
                insertfila(idstruc->fi,x,y);
                buildtxtret(i,getIrectangle(i),0);
            }
        }
        else if(confereLine(i)==1)
        {
            if(getIline(i) - idstruc->i < 0.0001 && idstruc->i - getIline(i) < 0.0001)
            {
                switch (whichline(x,y,getX2line(i),getY2line(i)))
                {
                case 2 :
                    x = getX2line(i);
                    y = getY2line(i);
                    buildtxtlin(i,x,y,getX1line(i),getY1line(i),getIline(i),0);
                    break;

                case 4 :
                    x = getX2line(i);
                    y = getY2line(i);
                    buildtxtlin(i,x,y,getX1line(i),getY1line(i),getIline(i),0);
                break;
                default:
                    buildtxtlin(i,x,y,getX2line(i),getY2line(i),getIline(i),0);
                break;
                }
                insertfila(idstruc->fi,x,y); 
            }
        } 
        else if (confereText(i)==1)
        {
           if(getItext(i) - idstruc->i < 0.0001 &&  idstruc->i - getItext(i) < 0.0001)
           {
                insertfila(idstruc->fi,x,y);
                buildtxttex(i,getItext(i),0);
           }
        }

}

void funcINP(XyyTree tree,void * inpp)
{
    visitaProfundidadeXyyT(tree,confereI,inpp);
}

//  ----------------------------- FUNCTION UPS ------------------------------------ 

void UPSinfugures(XyyTree tree,Info i,double dx,double dy, char corb[10],char corp[10])
{
    
        if(confereCircle(i)==1)
        {
            setcircle(i,dx+getXcircle(i),dy+getYcircle(i),getIcircle(i),getRcircle(i),corb,corp);
        }
        else if(confereRectangle(i)==1)
        {   
            setrectangle(i,getIrectangle(i),dx+getXrectangle(i),dy+getYrectangle(i),getWrectangle(i),getHrectangle(i),corb,corp);
        }
        else if(confereLine(i)==1)
        {
            setline(i,getIline(i),dx+getX1line(i),dy+getY1line(i),dx+getX2line(i),dy+getY2line(i),corp);          
        } 
        else if (confereText(i)==1)
        {
            settext(i,getItext(i),dx+getXtext(i),dy+getYtext(i),corb,corp,getTexttext(i),getAtext(i));
        }
}

void upsneg(XyyTree tree,Lista aux,nodep node, int n,double dx,double dy, char corb[10],char corp[10])
{
    node = getPrev(aux,node);

    while(n<0&&node!=NULL)
    {
        void* nodetree = getInfo(aux,node);
        void *figure = getInfoXyyT(tree,nodetree);
        UPSinfugures(tree,figure,dx,dy,corb,corp);
        n++;
        node = getPrev(aux,node);
    }
}

void funqUPS(XyyTree tree, Lista listsel, int n, double dx, double dy, char corb[10], char corp[10])
{
    void* node = getLast(listsel);
    upsneg(tree,listsel,node,n,dx,dy,corb,corp);
}
// ------------------------------FUNCTION DELS ---------------------------------------------------------------------

void funcDELS(XyyTree tree,Lista list)
{
    void* node_list = getBegin(list);
    void* info_node;
    while(node_list!=NULL)
    {   
        void * nodetree = getInfo(list,node_list);
        info_node = getInfoXyyT(tree,nodetree);
        //void* noderemove = node_list;
        if(confereCircle(info_node)==1)
        {
          removeNoXyyT(tree,nodetree);
          
        }
        else if(confereRectangle(info_node)==1)
        {
            removeNoXyyT(tree,nodetree);
        }
        else if(confereLine(info_node)==1)
        {
    
             removeNoXyyT(tree,nodetree);
            
        } 
        else if (confereText(info_node)==1)
        {
            removeNoXyyT(tree,nodetree);
        }
        node_list = getNext(list,node_list);
       

    }   
   destroylista(list);
}

// ------------------------------FUNCTION DPS ----------------------------------------------------------------------
void funqDPS(XyyTree tree, Lista list,double i, double dx, double dy, char corb[10],char corp[10])
{
    void *node = getBegin(list);
    while(node!=NULL)
    {
        void* nodetree = getInfo(list,node);
        void* data = getInfoXyyT(tree,nodetree);

        if(confereCircle(data)==1)
        {
            void *circle = createElementoc();
            double x = getXcircle(data)+dx;
            double y = getYcircle(data)+dy;
            setcircle(circle,x,y,i,getRcircle(data),corb,corp);
            insertXyyT(tree,x,y,circle);

        }
        else if(confereRectangle(data)==1)
        {
            void* retangulo = createElementor();
            double x = getXrectangle(data)+dx;
            double y = getYrectangle(data)+dy;
            setrectangle(retangulo,i,x,y,getWrectangle(data),getHrectangle(data),corb,corp);
            insertXyyT(tree,x,y,retangulo);

        }
        else if(confereLine(data)==1)
        {
            double x = getX1line(data)+dx;
            double y = getY1line(data)+dy;
            double x2 = getX2line(data)+dx;
            double y2 = getY2line(data)+dy;
            void *line = createline(i,x,y,x2,y2,corp);
            setline(line,i,x,y,x2,y2,corp);
            insertXyyT(tree,x,y,line);
            
        } 
        else if (confereText(data)==1)
        {
            void *text = createElementot();
            double x = getXtext(data)+dx;
            double y = getYtext(data)+dy;
            settext(text,i,x,y,corb,corp,getTexttext(data),getAtext(data));
            insertXyyT(tree,x,y,text);
        }
        node= getNext(list,node);
        i++;
    }
}

// -----------------------------------------FUNQTIONS SEL ---------------------------------------------------------------

void printaancora(XyyTree tree,Lista list,FILE *svg,int flag)
{
    if(flag==2||flag==3){
    void *node = getBegin(list);
    while(node!=NULL)
    {
        void* node_tree = getInfo(list,node);
        void* data = getInfoXyyT(tree,node_tree);

        if(confereRectangle(data)==1)
        {
            
            fprintf(svg,"\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"1\" stroke=\"red\" stroke-width=\"1\" fill=\"red\" />\n",getXrectangle(data),getYrectangle(data));
        }
        else if(confereLine(data)==1)
        {
            fprintf(svg,"\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"1\" stroke=\"red\" stroke-width=\"1\" fill=\"red\" />\n",getX1line(data),getY1line(data));
            fprintf(svg,"\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"1\" stroke=\"red\" stroke-width=\"1\" fill=\"red\" />\n",getX2line(data),getY2line(data));
        } 
        else if (confereText(data)==1)
        {
            fprintf(svg,"\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"1\" stroke=\"red\" stroke-width=\"1\" fill=\"red\" />\n",getXtext(data),getYtext(data));          
        }
        else if(confereCircle(data)==1)
        {
           fprintf(svg,"\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"1\" stroke=\"red\" stroke-width=\"1\" fill=\"red\" />\n",getXcircle(data),getYcircle(data));
        }
        node= getNext(list,node);
       
    }
   }
    return;
}

bool figureRegiao (Info i, double x1, double y1,double x2, double y2)
{
    
    if(confereCircle(i) == 1)
    {
      return circleRegiao(i,x1,y1,x2,y2);
       
    }
    else if(confereRectangle(i) == 1)
    {
      return rectangleRegiao(i,x1,y1,x2,y2);
    }
    else if(confereLine(i) == 1)
    {   
      return lineRegiao(i,x1,y1,x2,y2);
    }
    else if(confereText(i) == 1)
    {
        return textRegiao(i,x1,y1,x2,y2);
    }
   
}

Lista funqSELplus(XyyTree tree,Lista list,double x, double y, double w,double h) 
{
    Lista cominfo = getInfosDentroRegiaoXyyT(tree, x, y, w, h, figureRegiao);
    Lista aux = createlista();
    void *nodeaux = getBegin(cominfo);

    while(nodeaux!=NULL)
    {
        void *i = getInfo(cominfo,nodeaux);

    if(confereRectangle(i) == 1)
    {
        insert(aux,getNodeXyyT(tree,getXrectangle(i),getYrectangle(i),0.0001));
    }
    else if(confereLine(i) == 1)
    {   
        insert(aux,getNodeXyyT(tree,getX1line(i),getY1line(i),0.0001));
    }
    else if(confereCircle(i) == 1)
    {
        insert(aux,getNodeXyyT(tree,getXcircle(i),getYcircle(i),0.0001));
       
    }
      else if(confereText(i) == 1)
    {
        insert(aux,getNodeXyyT(tree,getXtext(i),getYtext(i),0.0001));
    }
        nodeaux= getNext(cominfo,nodeaux);
    }

    void *node =getBegin(aux);
    while(node!=NULL){
        void * info = getInfo(aux,node);
        insert(list,info);
        node = getNext(aux,node);
    }
    destroylista(aux);
    destroylista(cominfo);
    return list;
}
Lista funqSEL(XyyTree tree,Lista list,double x, double y, double w,double h)
{
     if(confereEmpty(list)==0)
    {   
        destroylista(list);  
        list = createlista();           
    } 

    Lista cominfo = getInfosDentroRegiaoXyyT(tree, x, y, w, h, figureRegiao);
    void *nodeaux = getBegin(cominfo);
    void *i;
    while(nodeaux!=NULL)
    {
        i = getInfo(cominfo,nodeaux);
       
    if(confereRectangle(i) == 1)
    {
    
        insert(list,getNodeXyyT(tree,getXrectangle(i),getYrectangle(i),0.0001));
    }
    else if(confereLine(i) == 1)
    {   
        insert(list,getNodeXyyT(tree,getX1line(i),getY1line(i),0.0001));
        
    }
    else if(confereCircle(i) == 1)
    { 
        insert(list,getNodeXyyT(tree,getXcircle(i),getYcircle(i),0.0001));
       
    }
       else if(confereText(i) == 1)
     {
         insert(list,getNodeXyyT(tree,getXtext(i),getYtext(i),0.0001));
     }
        nodeaux= getNext(cominfo,nodeaux);
    }
    destroylista(cominfo);

    return list;
}


// ------------------- FUNCTION READQRY --------------------------------------------

void readqry(XyyTree tree, Path pathh)
{
   
   if(getArqqry(pathh)!= NULL){

    finalqry(pathh);
    finaloutqry(pathh);
    FILE *arquivo = fopen(getqry(pathh), "r");
    finaltxt(pathh);
    settxtname(pathh);
    opentxt(pathh);
    FILE *txt = fopen(gettxtname(pathh),"a");
    finalsvgqry(pathh);
    FILE *svg = fopen(getsvgqry(pathh), "w");
   
    double selx,sely,selh,selw;
    selx = 0;
    sely =0;
    selh = 0;
    selw=0;
    double i,dx,dy,d,e;
    int n,flag=0,flagfila =0;
    char corb[10];
    char corp[10];
    double incrementy,incrementx,incrementh,incrementw;
    char comando[4];

    openTagSVG(svg);
    Lista list = createlista();
    Fila f = create_fila(f);
    inp *auxid = (inp*)malloc(sizeof(inp));

    while(fscanf(arquivo,"%s", comando)!= -1)
    {
        if(strcmp(comando,"inp")==0)
        {
            double id;
            fscanf(arquivo,"%lf",&id);
            auxid->i=id;
            auxid->fi=f;
            funcINP(tree,auxid);
        }
        else if(strcmp(comando,"rmp")==0){
            removefila(f,txt);
        }
        else if(strcmp(comando,"pol")==0)
        {
            fscanf(arquivo,"%lf %lf %lf %s %s",&i,&d,&e,corb,corp);
            funqPOL(tree,f,svg,corb,corp,d,e,i);      
            
        }
        else if(strcmp(comando,"clp")== 0)
        {
            destroyfila(f);
            flagfila =1;
        }
        else if(strcmp(comando,"sel")==0)
        {
            fscanf(arquivo,"%lf %lf %lf %lf",&selx,&sely,&selw,&selh);
            list = funqSEL(tree,list,selx,sely,selw,selh);
            flag=2;
          
        }
        else if(strcmp(comando,"sel+")== 0){

            fscanf(arquivo,"%lf %lf %lf %lf",&incrementx,&incrementy,&incrementw,&incrementh);
            list = funqSELplus(tree,list,incrementx,incrementy,incrementw,incrementh);
            fprintf(svg,"\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"red\" stroke-width=\"1\" fill=\"none\"/>\n",incrementx,incrementy,incrementw,incrementh);
            flag =3;

        }
        else if(strcmp(comando,"dels")==0)
        {
            funcDELS(tree,list); 
        
            flag =1;
        }
        else if(strcmp(comando,"dps")==0)
        {
           fscanf(arquivo,"%lf %lf %lf %s %s",&i,&dx,&dy,corb,corp); 
           funqDPS(tree,list,i,dx,dy,corb,corp);

        }
        else if(strcmp(comando,"ups")==0)
        {
            fscanf(arquivo,"%s %s %lf %lf %d",corb,corp,&dx,&dy,&n);

             funqUPS(tree,list,n,dx,dy,corb,corp);
            
        }
    
    }
   
    fprintf(svg,"\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"red\" stroke-width=\"1\" fill=\"none\"/>\n",selx,sely,selw,selh);
    
    
    makesvg(tree,svg);
    printaancora(tree,list,svg,flag);
    dumpTree(tree,txt);
    if(flag!=1){
    destroylista(list);}
    if(flagfila!=1){
    destroyfila(f);}
    free(auxid);
    fclose(arquivo);
    closeTagSVG(svg);
    fclose(svg);
    fclose(txt);
  }
}