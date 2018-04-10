//
// Created by aysegul on 4/6/18.
//

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <map>
#include "common.h"
using namespace std;




int array(int argc, char **argv)
{
    cout<< "Array"<<endl;
    string line;
    string line2;
    int len=0;
    char path[100] = "/home/aysegul/Dropbox/clion/ResearchC++/genesname_length.txt";
    char patharray[100] = "/home/aysegul/Dropbox/clion/ResearchC++/arraylist.txt";
    if(argc<=1)
    {
        cout<<"Sample number is missing in array"<<endl;
        return -1;
    }


    char *sample_number=argv[1];


    char path3[100] = "/home/aysegul/Dropbox/clion/ResearchC++/all";
    char endpath3[5]=".sam";


    strcat(path3,sample_number);
    strcat(path3,endpath3);

    ifstream myfile (path);

    map <string, vector<string> > mymap;
    map<string, int> map_length;

    int count=0;
    if (myfile.is_open())
    {

        while ( getline (myfile,line) )
        {

            vector<string> genesnameslength_line=convertbytab(line);
            map_length[genesnameslength_line[0]]=stoi(genesnameslength_line[1]);

            ifstream allsamfile(path3);
            if (allsamfile.is_open())
            {

                while ( getline (allsamfile,line2) )
                {
                    vector<string> lin=convertbytab(line2);
                    string look= lin[2];
                    if (look.find(genesnameslength_line[0]) != std::string::npos) //if the gene is found in allsamfile
                    {
                        mymap[genesnameslength_line[0]];
                        mymap[genesnameslength_line[0]].push_back(line2);
                    }


                }
                allsamfile.close();


            }


        }
        myfile.close();



    }



    else cout << "Unable to open file";
    //cout<<	"Printing Map"<<endl;
    int count0=0;
    ofstream arraylistfile;
    arraylistfile.open(patharray);
    for(auto elem : mymap)
    {
        count0++;

        char path_[100]= "/home/aysegul/Dropbox/clion/ResearchC++/genesams";
        char slash[6]="/gene";
        char const *gene_number=to_string(count0).c_str();
        char endpath_[5]=".sam";
        strcat(path_,sample_number);
        strcat(path_,slash);
        strcat(path_,gene_number);
        strcat(path_,endpath_);
        ofstream eachgenesam;
        eachgenesam.open(path_);




        char path_2[100]= "/home/aysegul/Dropbox/clion/ResearchC++/histogram";
        char slash2[7]="/array";
        char endpath_2[5]=".txt";
        strcat(path_2,sample_number);
        strcat(path_2,slash2);
        strcat(path_2,gene_number);
        strcat(path_2,endpath_2);
        ofstream arrayfile;
        arrayfile.open(path_2);
        string name=elem.first;
        arraylistfile<<"array"+to_string(count0)+".txt\n";
        len=map_length[elem.first];
        int my_vec[4000] = {0};

        //vector<int> my_vec;




        for(auto e: elem.second)
        {
            eachgenesam<<e<<'\n';
            vector<string> genesam_line=convertbytab(e);
            int start=stoi(genesam_line[3]);
            int end=start+genesam_line[9].length();
            for(int k=start;k<end;k++)
            {
                my_vec[k]=my_vec[k]+1;
            }
        }
        for(int i=0;i<len;i++)
        {
            arrayfile<<my_vec[i];
            arrayfile<< " ";
        }
        /*
        for (int i : my_vec)
        {
            arrayfile<< i;
            arrayfile<<" ";
        }*/

        arrayfile<<"\n";
        arrayfile<<name;
        arrayfile<<"\n";
        arrayfile.close();
        eachgenesam.close();


    }
    arraylistfile.close();


    return 0;
}

