//
// Created by aysegul on 4/6/18.
//
#include <iostream>
#include <fstream>
#include <vector>
#include "genenamelength.h"


using namespace std;


int genenamelength(int argc, char **argv)
{
    cout<< "GeneNameLength"<<endl;
    string line;
    char path[100]="/home/aysegull/Dropbox/clion/ResearchC++/database/megares_database_v1.01.fasta";

    if(argc<=1)
    {
        cout<<"Sample number is missing in genenamelength.cpp"<<endl;
        return -1;
    }


    char path2[70] = "/home/aysegull/Dropbox/clion/ResearchC++/genesname_length.txt";

    ifstream myfile (path);
    ofstream genenames;
    genenames.open (path2);
    string newline;

    int count=0;
    if (myfile.is_open())
    {

        while ( getline (myfile,line) )
        {

            count=count+1;
            if(count==1)
            {
                newline=line.substr(line.find('>') + 1);
            }
            if(count==2)
            {
                count=0;
                newline=newline+"\t";
                newline=newline+to_string(line.length());
                newline=newline+"\n";
                genenames<<newline;
            }



        }
        myfile.close();
        genenames.close();

    }

    else cout << "Unable to open file";

    return 0;
}



