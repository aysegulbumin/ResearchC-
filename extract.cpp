//
// Created by aysegul on 4/6/18.
//
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include "extract.h"
#include "common.h"

using namespace std;


int extract(int argc, char **argv)
{
    cout<< "Extract"<<endl;
    string line;


    char path[60]="/home/aysegul/Dropbox/clion/ResearchC++/sam_files/align";

    if(argc<=1)
    {
        cout<<"Sample number is missing in extract.cpp"<<endl;
        return -1;
    }

    char path2[50] = "/home/aysegul/Dropbox/clion/ResearchC++/all";
    char *sample_number=argv[1];
    char endpath2[5]=".sam";
    char path3[70] = "/home/aysegul/Dropbox/clion/ResearchC++/frontname";
    char endpath3[5]=".txt";
    char path4[60] = "/home/aysegul/Dropbox/clion/ResearchC++/reversename";
    char endpath4[5]=".txt";
    char path5[50] = "/home/aysegul/Dropbox/clion/ResearchC++/flagfour";
    char endpath5[5]=".sam";

    strcat(path,sample_number);
    strcat(path,endpath2);
    strcat(path2,sample_number);
    strcat(path2,endpath2);
    strcat(path3,sample_number);
    strcat(path3,endpath3);
    strcat(path4,sample_number);
    strcat(path4,endpath4);
    strcat(path5,sample_number);
    strcat(path5,endpath5);

    //cout<<"This is the path for all#.sam :	"<<path2<<endl;

    ifstream myfile (path);
    ofstream allsamfile;
    allsamfile.open (path2);
    ofstream frontname;
    frontname.open (path3);
    ofstream reversename;
    reversename.open (path4);
    ofstream flagfour;
    flagfour.open (path5);


    if (myfile.is_open())
    {

        while ( getline (myfile,line) )
        {

            if(line[0]!='@')
            {
                vector<string> myvec=convertbytab(line);
                if(4 == stoi(myvec[1]))
                {
                    flagfour<<line<<'\n';
                }
                else if(77 == stoi(myvec[1]))
                {
                    frontname<<myvec[0]<<"\n";
                }
                else if(141 == stoi(myvec[1]))
                {
                    reversename<<myvec[0]<<"\n";
                }
                else
                {
                    allsamfile <<line<<'\n';
                }

            }

        }
        myfile.close();
        allsamfile.close();
        frontname.close();
        reversename.close();
        flagfour.close();
    }
    else cout << "Unable to open file";

    return 0;
}