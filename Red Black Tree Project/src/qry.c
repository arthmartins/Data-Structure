#include "SRB_Tree.h"
#include "Circulo.h"
#include "Retangulo.h"
#include "Texto.h"
#include "Linha.h"
#include "qry.h"
#include "Svg.h"
#include "path.h"

typedef struct IdAuxiliar
{
    Info info;
    int flag;
    double id;
    FILE *txt;

}Id;

bool hasEnergytoLaunch(Info i,double d,FILE *txt)
{
    double energy;
    energy = (getArea(i)/25) * (d/5);
    if(energy < getEnergia(i))
    {
        fprintf(txt,"\nEnergia antes de lançar = %d",getEnergia(i));

        setEnergia(i,getEnergia(i)-energy);

        fprintf(txt,"\nEnergia depois de lançar = %d\n",getEnergia(i));
        return true;
    }else{
        fprintf(txt,"\nNão tem energia o suficiente para lançar\n");
        return false;
    }
}

bool hasEnergytoShoot(Info i,double d)
{
    double energy;
    energy = d;
    if(energy < getEnergia(i))
    {
        setEnergia(i,getEnergia(i)-energy);
        return true;
    }else{
        return false;
    }
}

//--- Função e------------------------------------------------
void printTxtFunctionE(FILE *txt,Info i)
{   
    fprintf(txt,"\n[*] e\n");
    printTxtRectangle(txt,i);

}

void energizarAuxiliar(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux)
{
    Id *auxiliar = (Id*)aux;
    int v = auxiliar->flag;
    if(confereRectangle(i)==1)
    {
        setEnergia(i,v);
        printTxtFunctionE(auxiliar->txt,i);
    }
    
}

void energizaNaus(SRbTree tree, Info identificador)
{
    percursoProfundidade(tree,energizarAuxiliar,identificador);
}
//-------------------------------------------------------------

int findTypeofFigure(Info info)
{
    
    if(confereRectangle(info))
    {
        return 2;
    }
    else if(confereLine(info))
    {
        return 3;
    }
    else if(confereText(info))
    {
        return 4;

    }else if(confereCircle(info)){
        return 1;
    }
}
double getIdFigure(Info info)
{
    int type = findTypeofFigure(info);
     switch (type)
    {
    case 1:
        return getIcircle(info);
        break;
    case 2:
        return getIrectangle(info);
        break;
    case 3:
        return getIline(info);
        break;
    case 4:
        return getItext(info);
        break;
   
    }

}


void auxiliarFunctions(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux)
{
    Id *aux2 = (Id*)aux;
    if(getIdFigure(i) - aux2->id < 0.00001 && aux2->id - getIdFigure(i) < 0.00001)
    {
        aux2->info = i;
        aux2->flag = 1;
    }
    
}

void printTxtPosicoes(FILE *txt, double xi, double yi, double xf,double yf)
{
    fprintf(txt,"\nPosição Inicial: x = %lf y = %lf",xi,yi);
    fprintf(txt,"\nPosição Final: x = %lf y = %lf",xf,yf);

}

void transladeFigure(SRbTree tree,Info i, double id, double dx, double dy,FILE *txt)
{
    fprintf(txt,"\n[*]mv\n");
    double mx1,mx2,my1,my2,mbbX1,mbbX2,mbbY1,mbbY2;
    switch (findTypeofFigure(i))
    {
        case 2: ;

            Info infor = createElementor();
            setrectangle(infor,id,getXrectangle(i)+dx,getYrectangle(i)+dy,getWrectangle(i),getHrectangle(i),getCorbrectangle(i),getCorprectangle(i));
            setEnergia(infor,getEnergia(i));
            printTxtRectangle(txt,i);

            removeSRb(tree,getXrectangle(i),getYrectangle(i),&mbbX1,&mbbY1,&mbbX2,&mbbY2);
            makeRMBB(infor,&mx1,&mx2,&my1,&my2);
            insertSRb(tree,getXrectangle(infor),getYrectangle(infor), mx1, my1, mx2, my2, infor);
            
            printTxtPosicoes(txt, getXrectangle(infor)-dx,getYrectangle(infor)-dy, getXrectangle(infor),getYrectangle(infor));

        break;

        case 3: ;

            Info infol = createline(getIline(i),getX1line(i)+dx,getY1line(i)+dy, getX2line(i) + dx ,getY2line(i)+dy,getCorline(i));
            printTxtLine(txt,i);

            removeSRb(tree,getX1line(i),getY1line(i),&mbbX1,&mbbY1,&mbbX2,&mbbY2);
            makeLMBB(infol,&mx1,&mx2,&my1,&my2);
            insertSRb(tree,getX1line(infol),getY1line(infol), mx1, my1, mx2, my2, infol);

            printTxtPosicoes(txt, getX1line(infol)-dx,getY1line(infol)-dy, getX1line(infol),getY1line(infol));

        break;

        case 4: ;

            Info infot = createElementot();
            settext(infot,getItext(i),getXtext(i)+dx,getYtext(i)+dy,getCorbtext(i),getCorptext(i),getTextotext(i),getAtext(i));
            printTxtText(txt,i);

            removeSRb(tree,getXtext(i),getYtext(i),&mbbX1,&mbbY1,&mbbX2,&mbbY2);
            makeTMBB(infot,&mx1,&mx2,&my1,&my2);
            insertSRb(tree,getXtext(infot),getYtext(infot), mx1, my1, mx2, my2, infot);

            printTxtPosicoes(txt, getXtext(infot)-dx,getYtext(infot)-dy, getXtext(infot),getYtext(infot));

        break;

        case 1: ;

            Info info = createElementoc();
            setcircle(info,getXcircle(i)+dx,getYcircle(i)+dy,id,getRcircle(i),getCorbcircle(i),getCorpcircle(i));
            printTxtCircle(txt,i);

            removeSRb(tree,getXcircle(i),getYcircle(i),&mbbX1,&mbbY1,&mbbX2,&mbbY2);
            makeCMBB(info,&mx1,&mx2,&my1,&my2);
            insertSRb(tree,getXcircle(info),getYcircle(info), mx1, my1, mx2, my2, info);
            
            printTxtPosicoes(txt, getXcircle(info)-dx, getYcircle(info)-dy, getXcircle(info),getYcircle(info));

        break;

        default:
        break;
    }
}

void FunctionMv(SRbTree tree, double id, double dx, double dy, Info idstruc)
{
    Id *figure = (Id*)idstruc;
    percursoProfundidade(tree,auxiliarFunctions,figure);
    if(figure->flag == 1)
    {
        transladeFigure(tree,figure->info,id,dx,dy,figure->txt);
    }

}
//----------------------------------------------------------------------------------------------
bool isNau(Info i)
{
    if(confereRectangle(i)==1)
    {
        return true;
    }
    else
    return false;
}

int contarMoedaseRiqueza(SRbTree tree,Info i,Lista list,FILE *txt)
{
    int moedas = 0;
    int riqueza = 0;
    if(confereEmpty(list)!=1){

    void *node =getBegin(list);
    while(node!=NULL){
        Node* in = getInfo(list,node);
        Info info = getInfoSRb(tree,in,0,0,0,0,0,0);
        switch (findTypeofFigure(info))
        {
            case 1:
                printTxtCircle(txt,info);
                fprintf(txt,"Valor monetario = M$ 5,00\n");
                riqueza +=5;
                removeSRb(tree,getXcircle(info),getYcircle(info),0,0,0,0);
            break;
           
            case 3:
                 printTxtLine(txt,info);
                 fprintf(txt,"Valor monetario = M$ 1,00\n");
                 riqueza += 1;
                 removeSRb(tree,getX1line(info),getY1line(info),0,0,0,0);

            break;
            case 4:
                
                printTxtText(txt,info);
                if(strcmp(getTextotext(info),">-|-<")==0)
                {
                    fprintf(txt,"Valor monetario = M$ 20,00");
                    riqueza+=20;
                    removeSRb(tree,getXtext(info),getYtext(info),0,0,0,0);
                }else if(strcmp(getTextotext(info),"$")==0)
                {
                    moedas+=1;
                    removeSRb(tree,getXtext(info),getYtext(info),0,0,0,0);
                }else{
                    fprintf(txt,"Valor monetario = M$ 0,00\n");
                    removeSRb(tree,getXtext(info),getYtext(info),0,0,0,0);
                }
                
                
            break;

        }
        node = getNext(list,node);
    }
   
    destroylista(list);

    }
    fprintf(txt,"\nTotal de riqueza da captura = M$ %d\n",riqueza);
    setRiqueza(i,riqueza);

    return moedas;
}

void lancarRede(SRbTree tree,Info i,double d,double w,double h,char lado[4],Lista list,FILE *svg,FILE *txt)
{
    double cy,cx;
    if(isNau(i)){
     if(strcmp(lado,"BB")==0)
        {
            cx =  getXrectangle(i)+ getWrectangle(i)+d;
            cy = getYrectangle(i);
        }

        else if(strcmp(lado,"EB")==0)
        {
            
            cx = getXrectangle(i) - d; 
            cy = getYrectangle(i);
                          
        }
        else if(strcmp(lado,"PP")== 0)
        {
          
            cy = getYrectangle(i) - d;
            cx = getXrectangle(i);

        }
        else if(strcmp(lado,"PR")==0)
        {
            cx = getXrectangle(i);
            cy =  getYrectangle(i) + getHrectangle(i) + d;
            
        }
        getBbPartSRb(tree,cx,cy,w,h,list);
        getBbSRb(tree,cx,cy,w,h,list);
        int moedas = contarMoedaseRiqueza(tree,i,list,txt);
        setEnergia(i,getEnergia(i)+moedas*0.5);

        fprintf(svg, "\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"red\" fill=\"none\" stroke-width=\"1\"/>\n",  cx, cy, w,h);
       
    }
    else
    {
        printf("Erro: Nao e uma Nau");
    }
}
void FunctionLr(SRbTree tree, double id, double w, double h,double d,char lado[4], Info idstruc,FILE *svg,FILE *txt)
{
    Id *figure = (Id*)idstruc;
    Lista list = createlista();
    percursoProfundidade(tree,auxiliarFunctions,figure);
     if(figure->flag == 1)
    {
        fprintf(txt,"\n[*]lr");
        if(hasEnergytoLaunch(figure->info,d,txt))
        {
            lancarRede(tree,figure->info,d,w,h,lado,list,svg,txt);
        }
    }
    if(confereEmpty(list)==0){
        destroylista(list);
    }
    free(list);

}
//-------------------------------------------------------------------------------------------

void darTiro(Info i,double *xt,double *yt,char lado[4],double d)
{
    if(isNau(i)){
     if(strcmp(lado,"BB")==0)
        {
            *xt = getXrectangle(i)+ getWrectangle(i) + d;
            *yt = getYrectangle(i)+ (getHrectangle(i)/2);
        }

        else if(strcmp(lado,"EB")==0)
        {
            *xt = getXrectangle(i)-d;
            *yt = getYrectangle(i)+ (getHrectangle(i)/2);
        }
        else if(strcmp(lado,"PP")== 0)
        {
            *xt = getXrectangle(i)+ (getWrectangle(i)/2);
            *yt = getYrectangle(i)-d;
        }
        else if(strcmp(lado,"PR")==0)
        {
            *xt = getXrectangle(i)+ (getWrectangle(i)/2);
            *yt = getYrectangle(i) + getHrectangle(i)+d;
        }
    }
    else
    {
        printf("Erro: Nao e uma Nau");
    }
}

void insertNauLista(Info i, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, void *aux)
{
    Lista *list = aux;
    if(isNau(i))
    {
        insert(list,i);
    }

}

void localizarNauDestruida(SRbTree tree, Lista list, double xt, double yt,FILE *svg,Info i,FILE *txt)
{
    fprintf(txt,"\n[*]d\n");
    fprintf(txt,"Pontos de impacto: x = %lf y = %lf\n",xt,yt);

    if(confereEmpty(list)!=1){
     
    void *node =getBegin(list);
    while(node!=NULL){
        Info info = getInfo(list,node);
        if(isNauAtigido(info, xt, yt))
        {
            //Removenode_list(list,node);
            fprintf(txt,"Dados da Nau destruida:\n");
            printTxtRectangle(txt,info);
            setRiqueza(i,getRiqueza(info));
            removeSRb(tree,getXrectangle(info),getYrectangle(info),0,0,0,0);
        }
        node = getNext(list,node);
    }
    destroylista(list);
    fprintf(svg, "\n\t<text x=\"%lf\" y=\"%lf\" fill=\"red\" fill-opacity=\"3\"   stroke=\"red\"> * </text>", xt,yt);
    }
    
}

void functionD(SRbTree tree, Info idstruc, char lado[4],double d, double i,FILE *svg,FILE *txt)
{
    Id *figure = (Id*)idstruc;
    double xt, yt;
    Lista list = createlista();
    percursoProfundidade(tree,auxiliarFunctions,figure);
    if(figure->flag == 1)
    {
        if(hasEnergytoShoot(figure->info,d))
        {
            darTiro(figure->info,&xt,&yt,lado,d);
            percursoProfundidade(tree,insertNauLista, list);
            localizarNauDestruida(tree,list,xt,yt,svg,figure->info,txt);
        }
    }
    free(list);
}
// ------------------------------------------------------------------------------

void transladarPeixes(SRbTree tree, Lista list,double dx,double dy,FILE *txt)
{   
    fprintf(txt,"\n[*]mc\n");
    double mx1,mx2,my1,my2,mbbX1,mbbX2,mbbY1,mbbY2;
    if(confereEmpty(list)!=1)
    {
        void *node =getBegin(list);
        while(node!=NULL)
        {
            void* in = getInfo(list,node);
            Info info  = getInfoSRb(tree,in,0,0,0,0,0,0);


            if(confereText(info) == 0 && confereCircle(info)==1){
            Info newCircle = createElementoc();

            setcircle(newCircle,getXcircle(info)+dx,getYcircle(info)+dy,getIcircle(info),getRcircle(info),getCorbcircle(info),getCorpcircle(info));
            removeSRb(tree,getXcircle(info),getYcircle(info),&mbbX1,&mbbY1,&mbbX2,&mbbY2);
            makeCMBB(newCircle,&mx1,&mx2,&my1,&my2);
            insertSRb(tree,getXcircle(newCircle),getYcircle(newCircle), mx1, my1, mx2, my2, newCircle);
            printTxtCircle(txt,newCircle);
            printTxtPosicoes(txt, getXcircle(newCircle)-dx, getYcircle(newCircle)-dy, getXcircle(newCircle),getYcircle(newCircle));
            }

            node = getNext(list,node);
        }
        destroylista(list);
    }else
        fprintf(txt,"Nenhum peixe transladado\n");
}

void FunctionMc(SRbTree tree, double x, double y, double w, double h,double dx,double dy, FILE *txt)
{
    Lista list = createlista();
    getBbPartSRb(tree,x,y,w,h,list);
    getBbSRb(tree,x,y,w,h,list);;
    transladarPeixes(tree,list,dx,dy,txt);
}
//---------------------------------------------------------------------------------------------------

int riquezaTotal(Lista list, FILE *txt)
{
    int rich = 0;
    if(confereEmpty(list)!=1){
     
    void *node =getBegin(list);
    while(node!=NULL){
        Info info = getInfo(list,node);
        fprintf(txt,"\nRiqueza total da Nau de id: %0.lf = M$ %d\n",getIrectangle(info),getRiqueza(info));
        rich += getRiqueza(info);
        node = getNext(list,node);
    }
    destroylista(list);
    
    }
    return rich;
}

void FinalTxt(SRbTree tree, FILE *txt)
{
    Lista list = createlista();
    percursoProfundidade(tree,insertNauLista,list);
    int total = riquezaTotal(list,txt);
    fprintf(txt,"Total da captura de todas as Naus = M$ %d,00",total);
    destroylista(list);
    free(list);

}

void readqry(SRbTree tree,Path path)
{
    if(getArqqry(path)!= NULL){

    finalqry(path);
    finaloutqry(path);
    FILE *arquivo = fopen(getqry(path), "r");
    finaltxt(path);
    FILE *txt = fopen(gettxtname(path),"w");
    finalsvgqry(path);
    FILE *svgqry = fopen(getsvgqry(path), "w");


    int energia;
    double i,dx,dy,d,w,h,x,y;
    char lado[3];

    Id* identificador = (Id*)malloc(sizeof(Id));
    identificador->txt = txt;
    
    openTagSVG(svgqry);
    char comando[2];
    int flagLr =0;

    while(fscanf(arquivo,"%s", comando)!= -1)
    {

        if(strcmp(comando,"e")==0)
        {
            fscanf(arquivo,"%d", &energia);
            identificador->flag = energia;
            energizaNaus(tree,identificador);
        }

        else if(strcmp(comando,"mv")==0)
        {
            identificador->flag = 0;
            fscanf(arquivo,"%lf %lf %lf",&i,&dx,&dy);
            identificador->id = i;
            FunctionMv(tree,identificador->id,dx,dy,identificador);

            
        }
        else if(strcmp(comando,"lr")== 0)
        {
            identificador->flag = 0;
            fscanf(arquivo,"%lf %s %lf %lf %lf", &i,lado,&d,&w,&h);
            identificador->id = i;
            FunctionLr(tree,identificador->id,w,h,d,lado,identificador,svgqry,identificador->txt);
            flagLr =1;
            
        }
        else if(strcmp(comando,"d")==0)
        {
            identificador->flag = 0;
            fscanf(arquivo,"%lf %s %lf ", &i,lado,&d);
            identificador->id = i;
            functionD(tree,identificador,lado,d,identificador->id,svgqry,identificador->txt);
          
        }
        else if(strcmp(comando,"mc")== 0)
        {
            fscanf(arquivo,"%lf %lf %lf %lf %lf %lf",&dx,&dy,&x,&y,&w,&h);
            FunctionMc(tree,x,y,w,h,dx,dy,identificador->txt);
           
            
        }
    
    }

    makesvg(tree,svgqry);
    if(flagLr==1)
        FinalTxt(tree,txt);
    closeTagSVG(svgqry);
    fclose(arquivo); 
    fclose(svgqry);
    finaldotqry(path);
    printSRb(tree,getdotqry(path));
    free(identificador);
    fclose(txt);
    }

}
