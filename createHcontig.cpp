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

static  vector< vector<int> > mymatrix2;

 int mymatrix[4][4000];

void add_to_matrix(int start_here, int end_here, string filepath)
{

    ifstream mysamfile (filepath);

    string line_;

    /*
    cout<<  "Print MATRIX"<<endl;
    for (int j=0;j<4;j++)
    {
        for(int i=0;i<=4000;i++)
        {
            cout<<mymatrix[j][i]<<" ";
        }

        cout<<endl;
        cout<<endl;

    }*/
    if (mysamfile.is_open())
    {

        while ( getline (mysamfile,line_) )
        {
           // cout<<"File is read-*********************"<<endl;
           // cout<<line_;
            vector<string> stringvec=convertbytab(line_);
           /* cout<<"Sam file line"<<endl;
            for(int k=0;k<stringvec.size();k++)
            {
                cout<<stringvec[k]<<"\t";
            }
            cout<<endl;
            cout<<"Stoi"<<endl;*/
            try {
                int num = std::stoi(stringvec[3]) ;
                //std::cout << "Converted \"" << stringvec[3] << "\" to " << num << '\n' ;
            }
            catch( std::exception& ex)
            {
                std::cout << "ERROR: " << ex.what() << '\n' ;
                std::cout << "\tUnable to convert \"" << stringvec[3] << "\" to a number.\n" ;
            }
           // cout<<stoi(stringvec[3])<<endl;
            if(start_here<= stoi(stringvec[3]) && stringvec[9].size()+stoi(stringvec[3])<=int(end_here))
            {
                //cout<<"Ever enters here"<<endl;
                //cout<<stoi(stringvec[3])<<endl;
                int start2=stoi(stringvec[3]);
                int end2=start2+stringvec[9].size();


                for(int i=start2;i<end2;i++)
                {


                    if(stringvec[9][i-start2]=='A')
                    {
                        mymatrix[0][i]=mymatrix[0][i]+1;
                    }
                    else if(stringvec[9][i-start2]=='C')
                    {
                        mymatrix[1][i]=mymatrix[1][i]+1;
                    }
                    else if(stringvec[9][i-start2]=='G')
                    {
                        mymatrix[2][i]=mymatrix[2][i]+1;
                    }
                    else if(stringvec[9][i-start2]=='T')
                    {
                        mymatrix[3][i]=mymatrix[3][i]+1;
                    }
                    else
                    {
                        cout<<"A,C,G,T not recognized"<<endl;
                    }


                }

            }

        }


    }
    mysamfile.clear();
    mysamfile.close();


}

string create_contig()
{
    string temp_contig="";
    int max=0;
    int max_base=-10;//0 denotes A , 1 denotes C , 2 denotes G and 3 denotes T
    for (int i=0;i<4000;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(mymatrix[j][i]>max)
            {
                max=mymatrix[j][i];
                if(max!=0)
                {
                    max_base=j;
                }

            }

        }
        max=0;
        switch(max_base)
        {
            case 0:
            {
                temp_contig+="A";
                max_base=-10;
                break;
            }
            case 1:
            {
                temp_contig+="C";
                max_base=-10;
                break;
            }

            case 2:
            {
                temp_contig+="G";
                max_base=-10;
                break;
            }
            case 3:
            {
                temp_contig+="T";
                max_base=-10;
                break;
            }

        }



    }

    return temp_contig;

}


int createHcontig (int argc, char** argv)
{
    string line;
    string line2;
    string line_matrix;
    cout<<"createHcontig"<<endl;
    //Initialize the matrix

    int len=0;
    char path[100] = "/home/aysegull/Dropbox/clion/ResearchC++/histogram";
    char endpath[20]="/aboutH.txt";
    char endpath2[20]=".sam";

    char path3[100] = "/home/aysegull/Dropbox/clion/ResearchC++/all";


    if(argc<=1)
    {
        cout<<"Sample number is missing"<<endl;
        return -1;
    }


    char *sample_number=argv[1];

    strcat(path3,sample_number);
    strcat(path3,endpath2);

    strcat(path,sample_number);
    strcat(path,endpath);

    ifstream myfile (path);
    //cout<<path<<endl;
    //cout<<path3<<endl;
    map <string, vector<int> > name_starts;
    map <string, vector<int> > name_ends;
    map<string, string> name_sam;

    vector<int> starts;
    vector<int> ends;
    vector<string> genenames;
    string genename;
    int count=0;
    int c=0;

    char front_oea_path[70] = "/home/aysegull/Dropbox/clion/ResearchC++/frontname_oea";
    char front_oea_pathend[5]=".txt";
    char reverse_oea_path[60] = "/home/aysegull/Dropbox/clion/ResearchC++/reversename_oea";
    char reverse_oea_pathend[5]=".txt";
    strcat(front_oea_path,sample_number);
    strcat(front_oea_path,front_oea_pathend);
    strcat(reverse_oea_path,sample_number);
    strcat(reverse_oea_path,reverse_oea_pathend);
    ofstream oea_front;
    oea_front.open (front_oea_path);
    ofstream oea_reverse;
    oea_reverse.open (reverse_oea_path);


    if (myfile.is_open())
    {

        while ( getline (myfile,line) )
        {
            count++;
            switch(count)
            {
                case 1:
                    break;
                case 2:
                {
                    c++;
                    genename=line;
                    char path2[60] = "/home/aysegull/Dropbox/clion/ResearchC++/histogram";
                    char slash2[5]="/";
                    char endpath_[20]=".sam";
                    strcat(path2,sample_number);
                    strcat(path2,slash2);
                    strcat(path2,to_string(c).c_str());
                    strcat(path2,endpath_);
                    ofstream samfile;
                    samfile.open (path2);
                    name_sam[genename];
                    name_sam[genename]=path2;
                    //cout<<path2<<endl;
                    ifstream allsamfile (path3);
                    if (allsamfile.is_open())
                    {

                        while ( getline (allsamfile,line2) )
                        {
                            vector<string> lin=convertbytab(line2);
                            string look= lin[2];
                            if (look.find(line) != std::string::npos) //if the gene is found in samfile
                            {


                                if(69 == stoi(lin[1]) || 73 == stoi(lin[1]))
                                {
                                    oea_front<<lin[0]<<"/1\n";
                                    oea_reverse<<lin[0]<<"/2\n";

                                }
                                if(137 == stoi(lin[1]) || 133== stoi(lin[1]) )
                                {
                                    oea_front<<lin[0]<<"/1\n";
                                    oea_reverse<<lin[0]<<"/2\n";
                                }
                                samfile<<line2<<"\n";

                            }
                            else
                            {
                             //   cout<< "Not found"<<endl;
                            }
                        }
                        allsamfile.close();
                    }
                    samfile.close();
                    break;
                }
                case 3:
                    break;
                case 4:
                {
                    starts=convertbyspace_int(line);
                    name_starts[genename];
                    name_starts[genename]=starts;

                    break;
                }

                case 5:
                    break;
                case 6:
                {
                    ends=convertbyspace_int(line);
                    name_ends[genename];
                    name_ends[genename]=ends;
                    count=0;
                    break;
                }
                default:
                    break;

            }
        }

        myfile.close();

    }



    else cout << "Unable to open file";

    int start_here=0;
    int end_here=0;
    string filepath;
    int count_Contig=0;
    for(auto elem : name_starts)
    {
        count_Contig++;
        char contigpath[60] = "/home/aysegull/Dropbox/clion/ResearchC++/histogram";
        char contigslash[10]="/contig";
        strcat(contigpath,sample_number);
        strcat(contigpath, contigslash);
        strcat(contigpath,to_string(count_Contig).c_str());
        ofstream contigfile;
        contigfile.open (contigpath);
        for(int k=0;k<name_ends[elem.first].size();k++)
        {
            int num=name_ends[elem.first].size();
            start_here=name_starts[elem.first][k];
            end_here=name_ends[elem.first][k];
            filepath=name_sam[elem.first];
            add_to_matrix(start_here,end_here,filepath);

        }
        string mycon=create_contig( );
        contigfile<<">Contig_"<<count_Contig<<" Length:"<<mycon.size()<<"   GeneName:"<<elem.first<<"\n";
        contigfile<<mycon<<endl;
        contigfile.close();
        /*
        cout<<  "Print MATRIX"<<endl;

        for (int j=0;j<4;j++)
        {
            for(int i=0;i<=4000;i++)
            {

                cout<<mymatrix[j][i]<<" ";
            }

            cout<<endl;
            cout<<endl;

        }*/

        for (int j=0;j<4;j++)
        {
            for(int i=0;i<=4000;i++)
            {
                mymatrix[j][i]=0;
            }


        }

    }

    return 0;
}

