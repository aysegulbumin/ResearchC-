// reading a text file
#include <iostream>
#include <cstring>
#include "array.h"
#include "extract.h"
#include "genenamelength.h"
#include "meandeviation.h"
#include "createHighfasta.h"
#include "runblat1.h"
#include "createHcontig.h"
using namespace std;


int main (int argc, char** argv)
{
    char mkdir[20]="mkdir genesams";
    char *sample_number=argv[1];
    strcat(mkdir,sample_number);

    system("rm -rf genesams*");
    system(mkdir);
    extract(argc, argv);
    genenamelength(argc, argv);
    array(argc, argv);
    meandeviation(argc, argv);
    createHighfasta(argc,argv);
    runblat1(argc,argv);
    createHcontig(argc,argv);
    return 0;
}

