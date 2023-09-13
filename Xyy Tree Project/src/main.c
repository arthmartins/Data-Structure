#include "Tree.h"
#include "Lista.h"
#include "geo.h"
#include "qry.h"
#include "path.h"


int main(int argc,char *argv[]){

     void *pathh = createPaths();

     readpaths(pathh,argc,argv);
    
     void *tree = newXyyTree(0.5); 
     readgeo(tree,pathh);

     readqry(tree,pathh);
  
     FreeXyyT(tree);
     freepaths(pathh);
     
}
