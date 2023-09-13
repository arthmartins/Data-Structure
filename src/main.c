#include "SRB_Tree.h"
#include "geo.h"
#include "qry.h"
#include "path.h"

int main(int argc,char *argv[])
{
    void *path = createPaths();
    readpaths(path,argc,argv);

    SRbTree tree = createSRb(0.00001);
    readGeo(tree,path);
    readqry(tree,path);

    killSRb(tree);
    freepaths(path);
}