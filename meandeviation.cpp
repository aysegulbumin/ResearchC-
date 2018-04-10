//
// Created by aysegul on 4/6/18.
//

//Calculate mean and deviation
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <random>
#include <cmath>
#include "common.h"

using namespace std;


double computeMean(vector<int> numbers)
{
    if(numbers.empty())
    {
        return 0;
    }

    double total = 0;
    for ( int number : numbers)
    {
        total += number;
    }

    return (total / numbers.size());
}

double computeVariance(double mean, vector< int> numbers)
{
    double result = 0;
    for(int number : numbers)
    {
        result += (number - mean)*(number - mean);
    }

    return result / (numbers.size() - 1);
}


int meandeviation (int argc, char** argv)
{
    cout<<"MeanDeviation"<<endl;
    string line;
    string line2;
    int flag=0;
    char path[60]="/home/aysegul/Dropbox/clion/ResearchC++/arraylist.txt";
    char path3[60]="/home/aysegul/Dropbox/clion/ResearchC++/histogram";
    char path4[60]="/home/aysegul/Dropbox/clion/ResearchC++/histogram";

    char endpath3[5]="/";

    if(argc<7)
    {
        cout<<"Parameters missing"<<endl;
        return -1;
    }
    for (int i = 1; i < argc; ++i)
    {
        switch(i)
        {
            case 1:
                cout << "\tSample Number "<<" : " <<argv[i] << "\n";
                break;
            case 2:
                cout << "\tCoefficient "<<" : " <<argv[i] << "\n";
                break;
            case 3:
                cout << "\tLow threshold "<<" : " <<argv[i] << "\n";
                break;
            case 4:
                cout << "\tHigh Threshold "<<" : " <<argv[i] << "\n";
                break;
            case 5:
                cout << "\tHigh Threshold 2 "<<" : " <<argv[i] << "\n";
                break;
            case 6:
                cout << "\tN many times "<<" : " <<argv[i] << "\n";
                break;
        }

    }
    char *n_manytimes=argv[6];
    char *coefficient=argv[2];
    char *lthreshold=argv[3];
    char *fl=argv[4];
    char *fr=argv[5];
    char *sample_number=argv[1];
    strcat(path3,sample_number);
    strcat(path3,endpath3);
    strcat(path3,"highlows.txt");
    ofstream highlow;
    highlow.open (path3);

    strcat(path4,sample_number);
    strcat(path4,endpath3);
    strcat(path4,"all_mean_dev.txt");
    //cout<<path4<<endl;
    ofstream means;
    means.open(path4);

    char path5[60]="/home/aysegul/Dropbox/clion/ResearchC++/histogram";
    strcat(path5,sample_number);
    strcat(path5,endpath3);
    strcat(path5,"HLs.txt");
    ofstream hls;
    hls.open (path5);

    //cout<<path5<<endl;

    ifstream myfile (path);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            char path2[70] = "/home/aysegul/Dropbox/clion/ResearchC++/histogram";
            char endpath2[5]="/";

            strcat(path2,sample_number);
            strcat(path2,endpath2);
            strcat(path2,line.c_str());
            ifstream arrayfile(path2);
            if (arrayfile.is_open())
            {
                int count=0;
                while ( getline (arrayfile,line2) )
                {
                    count++;
                    if(count==1)
                    {
                        vector<int> myvec=convertbyspace_int(line2);
                        vector<int> zeros_ones;
                        float bigmean=0;
                        int count_bigmean=0;
                        for(int j=0;j<=stoi(n_manytimes);j++)
                        {
                            int max=myvec.size()-(myvec.size()* 0.1)-1;
                            int min=100;
                            std::default_random_engine generator;
                            std::uniform_int_distribution<int> distribution(min,max);
                            int randomstart = distribution(generator);
                            int randomend = randomstart+myvec.size()* 0.1;
                            if(randomstart<=myvec.size() && randomend<=myvec.size() )
                            {
                                count_bigmean++;
                                vector<int >::const_iterator first = myvec.begin() + randomstart ;
                                vector< int>::const_iterator last = myvec.begin() + randomend;
                                vector< int> newVec(first, last);
                                double mean = computeMean(myvec);
                                double variance = computeVariance(mean, myvec);
                                double standardDeviation = sqrt(variance);
                                bigmean=bigmean+mean;

                            }
                        }
                        bigmean=bigmean/count_bigmean;
                        means<<"Mean: "<<bigmean<<"\t";
                        // cout<<"Big mean"<<bigmean<<endl;
                        long double bigvariance = computeVariance(bigmean, myvec);
                        long double  bigstandardDeviation = sqrt(bigvariance);
                        means<<"StdDev: "<<bigstandardDeviation<<"\t";
                        // cout<<"Big standardDeviation"<<bigstandardDeviation<<endl;
                        long double coverage=bigmean+ stoi(coefficient)*bigstandardDeviation;
                        means<<"Cov: "<<coverage<<"\t";
                        // cout<<"Coverage"<<coverage<<endl;

                        for(int i=0;i<myvec.size();i++)
                        {
                            if(myvec[i]>=coverage)
                            {
                                zeros_ones.push_back(1);
                            }
                            else
                            {
                                zeros_ones.push_back(0);
                            }
                        }
                        int previous=0;
                        int count_zeros=0;
                        int count_ones=0;
                        int countie=0;
                        vector<char> letter_vector;
                        vector<int> index_vector;
                        for(int i=0; i<zeros_ones.size();i++)
                        {
                            int current=zeros_ones[i];
                            if(previous==current && current==0)
                            {
                                count_zeros++;
                                previous=current;
                            }
                            else if(previous==current && current==1)
                            {
                                count_ones++;
                                previous=current;
                            }
                            else if(previous!=current && current==1)
                            {
                                count_ones++;
                                if(count_zeros>=stoi(lthreshold))//if there are enough zeros to be considered as low region
                                {
                                    letter_vector.push_back('L');// low and long enough to be L region
                                    index_vector.push_back(countie);
                                }
                                else
                                {
                                    letter_vector.push_back('X');//not long enough but low
                                    index_vector.push_back(countie);
                                }
                                previous=current;
                                count_ones=1;
                                count_zeros=0;
                            }
                            else if(previous!=current && current==0)
                            {
                                count_zeros++;
                                if(count_ones>=stoi(fl))//if there are enough ones to be considered as low region
                                {
                                    letter_vector.push_back('H');// high and long enough to be H region
                                    index_vector.push_back(countie);
                                }
                                else
                                {
                                    letter_vector.push_back('Y');//not long enough but high
                                    index_vector.push_back(countie);
                                }
                                previous=current;
                                count_zeros=1;
                                count_ones=0;
                            }
                            else
                            {
                                letter_vector.push_back('N');//not known, this case is expected not to be visited
                                index_vector.push_back(countie);
                            }

                            countie=countie+1;
                        }
                        highlow<< "Letters\n";

                        //cout<<  "Letters "<<endl;
                        string myletters="";
                        for (int i = 0; i < letter_vector.size(); ++i)
                        {
                            highlow<<letter_vector[i];
                            myletters+=letter_vector[i];
                            highlow<<" ";
                            //cout<< letter_vector[i];
                        }
                        if (myletters.find("HL") != std::string::npos || myletters.find("LH") != std::string::npos)
                        {
                            flag=1;
                            hls<< "Letters\n";
                            for (int i = 0; i < letter_vector.size(); ++i)
                            {
                                hls<<letter_vector[i];
                                hls<<" ";
                            }
                            hls<<"\n";
                            hls<<"Indices\n";
                            for (int i = 0; i < index_vector.size(); ++i)
                            {
                                hls<<index_vector[i];
                                hls<<" ";

                            }
                            hls<<"\n";

                        }
                        highlow<<"\n";

                        //cout<<"\n";
                        highlow<<"Indices\n";

                        //cout<<  "Indices "<<endl;
                        for (int i = 0; i < index_vector.size(); ++i)
                        {
                            highlow<<index_vector[i];
                            highlow<<" ";
                            //cout<< index_vector[i]<<" ";
                        }
                        highlow<<"\n";
                        //cout<<"\n";

                    }
                    if(count==2)
                    {
                        means<<"Name: "+line2+"\t";
                        highlow<<"Name\n"+line2+"\n";
                        if(flag==1)
                        {
                            hls<<"Name\n"+line2+"\n";
                            flag=0;
                        }

                        count=0;


                    }

                    // cout<<line2<<endl;
                }
                means<<"\n\n";

                arrayfile.close();
            }


        }
        myfile.close();

    }
    else cout << "Unable to open file";
    highlow.close();
    means.close();
    hls.close();
    return 0;
}
