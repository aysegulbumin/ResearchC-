//
// Created by aysegul on 4/6/18.
//

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <sstream>
#include <map>
#include "common.h"

using namespace std;

bool isUnique1(int argc, char** argv)
{
    string line;
    string line2;
    char path[100] = "/home/aysegul/Dropbox/clion/ResearchC++/histogram";
    if(argc<=1)
    {
        cout<<"Sample number is missing"<<endl;
        return false;
    }
    char endofpath[20]="/blat1_list.txt";
    char *sample_number=argv[1];
    strcat(path,sample_number);
    strcat(path,endofpath);
    ifstream uniquefile(path);
    if (uniquefile.is_open())
    {

        while (getline(uniquefile, line))
        {
            char path2[100] = "/home/aysegul/Dropbox/clion/ResearchC++/histogram";
            strcat(path2,sample_number);
            char constant[5]="/";
            strcat(path2,constant);
            strcat(path2,line.c_str());
            ifstream blatfile(path2);

            if (blatfile.is_open())
            {
                int count=0;
                while (getline(blatfile, line2))
                {

                    count++;
                    if(count>5)
                    {

                        vector<string> myvec=convertbytab(line2);
                        if(stoi(myvec[0]) <= 0.8* stoi(myvec[10]))
                        {
                            blatfile.close();
                            uniquefile.close();
                            return true;
                        }

                    }

                }
                blatfile.close();

            }

        }
        uniquefile.close();
    }


    return false;
}

vector<string> convertbytab(string input)
{
    vector<char> v;

    istringstream ss(input);
    string token;
    vector<string> line_vector;
    while(std::getline(ss, token, '\t'))
    {
        line_vector.push_back(token);
    }
    return line_vector;
}
vector<string> convertbyspace(string input)
{
    vector<char> v;

    istringstream ss(input);
    string token;
    vector<string> line_vector;
    while(std::getline(ss, token, ' '))
    {
        line_vector.push_back(token);
    }
    return line_vector;
}
vector<int> convertbyspace_int(string input)
{
    vector<char> v;

    istringstream ss(input);
    string token;
    vector<int> line_vector;
    while(std::getline(ss, token, ' '))
    {
        line_vector.push_back(stoi(token));
    }
    return line_vector;
}

vector<long long int> convertbyspace_longlongint(string input)
{
    vector<char> v;

    istringstream ss(input);
    string token;
    vector<long long int> line_vector;
    while(std::getline(ss, token, ' '))
    {
        line_vector.push_back(stoi(token));
    }
    return line_vector;
}