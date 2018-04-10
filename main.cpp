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
#include "common.h"
using namespace std;


int main (int argc, char** argv)
{
    clock_t start = clock();


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

    if(isUnique1(argc,argv))
    {
        createHcontig(argc,argv);

        char catthis[80]="cat frontname_oea";
        strcat(catthis,sample_number);
        char catthis2[50]=".txt  >> frontname";
        char end_cat[5]=".txt";
        strcat(catthis,catthis2);
        strcat(catthis,sample_number);
        strcat(catthis,end_cat);

        char catthis_reverse[80]="cat reversename_oea";
        strcat(catthis_reverse,sample_number);
        char catthis_reverse2[50]=".txt  >> reversename";
        char end_cat_reverse[5]=".txt";
        strcat(catthis_reverse,catthis_reverse2);
        strcat(catthis_reverse,sample_number);
        strcat(catthis_reverse,end_cat_reverse);

        system(catthis);
        system(catthis_reverse);
        system("rm -rf *_oea*.txt");
    }

    clock_t stop = clock();
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;


    int time = 0;
    int hour = 0;
    int min = 0;
    int sec = 0;
    time=elapsed;
    // using the time from ^ above, convert
    // secs to HH:MM:SS format using division
    // and modulus
    hour = time/3600;
    time = time%3600;
    min = time/60;
    time = time%60;
    sec = time;

    // display data to user
    cout<<"The time in HH:MM:SS format is: "<<hour<<" hours, "
        <<min<<" minutes, and "<<sec<<" seconds!";


    printf("\nTime elapsed: %.5f\n", elapsed);

    return 0;
}

