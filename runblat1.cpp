//
// Created by aysegul on 4/6/18.
//

#include <iostream>
#include <cstring>
#include "array.h"
#include "extract.h"
#include "runblat1.h"

#define SHELLSCRIPT "\
#/bin/bash \n\
echo -e \"\" \n\
echo -e \"This is a test shell script inside C code!!\" \n\
read -p \"press <enter> to continue\" \n\
clear\
"
using namespace std;


int runblat1 (int argc, char** argv)
{
    cout<<"RunBlat"<<endl;
    char firstcommand[100]="chmod  755 /home/aysegul/Dropbox/clion/ResearchC++/histogram";
    char secondcommand[100] = "/home/aysegul/Dropbox/clion/ResearchC++/histogram";
    char path[10] = "/blat1.sh";
    char *sample_number=argv[1];

    strcat(firstcommand,sample_number);
    strcat(firstcommand,path);

    strcat(secondcommand,sample_number);
    strcat(secondcommand,path);


    system(firstcommand);
    system(secondcommand);

    return 0;
}


