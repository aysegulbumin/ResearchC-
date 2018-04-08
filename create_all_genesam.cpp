// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <sstream> 
#include <map> 
using namespace std;


vector<string> convert_to_vector(string input)
{
	vector<char> v;

	istringstream ss(input);
	string token;
	vector<string> line_vector;
	while(std::getline(ss, token, '\t')) 
	{
		line_vector.push_back(token);
		//cout << token << '\n';
	}
	return line_vector;
}

int main (int argc, char** argv) 
{
	string line;
	string line2;
	int len=0;
	char path[60] = "/home/aysegull/Dropbox/clion/ResearchC++++/genesname_length.txt";

	if(argc<=1)
	{
		cout<<"Sample number is missing"<<endl;
	}
	for (int i = 1; i < argc; ++i)
	{
        cout << "Sample " <<argv[i] << "\n";
	}
	char path2[100]= "/home/aysegull/Dropbox/clion/ResearchC++++/runthis";
	char *sample_number=argv[1];
	char endpath2[5]=".sh";

	char path3[50] = "/home/aysegull/Dropbox/clion/ResearchC++++/all";
	char endpath3[5]=".sam";

	strcat(path2,sample_number);	
	strcat(path2,endpath2);
	strcat(path3,sample_number);	
	strcat(path3,endpath3);

  	ifstream myfile (path);
  	
  	ofstream runthis;
  	runthis.open (path2);

	runthis<<"#!/bin/bash\n";
	runthis<<"#SBATCH --job-name=runthis\n";
	runthis<<"#SBATCH --mail-type=ALL\n";
	runthis<<"#SBATCH --qos=boucher-b\n";
	runthis<<"#SBATCH --mail-user=aysegul.bumin@ufl.edu\n";
	runthis<<"#SBATCH --ntasks=1\n";
	runthis<<"#SBATCH --cpus-per-task=1\n";
	runthis<<"#SBATCH --mem=10gb\n";
	runthis<<"#SBATCH --time=90:00:00\n";
	runthis<<"#SBATCH --output=%j.out\n";
	runthis<<"date;hostname;pwd\n";

  	map <string, vector<string> > mymap;
  	map<string, int> map_length;

  	int count=0;
  	if (myfile.is_open())
  	{	

	    	while ( getline (myfile,line) )
	    	{
	    		
	    		vector<string> genesnameslength_line=convert_to_vector(line);
	    		map_length[genesnameslength_line[0]]=stoi(genesnameslength_line[1]);

	    		ifstream allsamfile(path3);
	    		if (allsamfile.is_open())
  				{	

	    			while ( getline (allsamfile,line2) )
				    {
				    	if (line2.find(genesnameslength_line[0]) != std::string::npos) //if the gene is found in allsamfile
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
  	for(auto elem : mymap)
	{
		count0++;
		char path_[100]= "/home/aysegull/Dropbox/clion/ResearchC++++/genesams";
		char slash[6]="/gene";
		char const *gene_number=to_string(count0).c_str();
		char endpath_[5]=".sam";
		strcat(path_,sample_number);
		strcat(path_,slash);
		strcat(path_,gene_number);
		strcat(path_,endpath_);	
		char runthisline[100]="python array.py gene";
		char runthisline2[100]="python postprocess.py gene";
		strcat(runthisline,gene_number);
		strcat(runthisline,endpath_);
		char tab[5]="\t";
		char endofline[5]="\n";
		strcat(runthisline,tab);
		strcat(runthisline,sample_number);
		strcat(runthisline,endofline);
		strcat(runthisline2,gene_number);
		strcat(runthisline2,endpath_);
		strcat(runthisline2,tab);
		strcat(runthisline2,sample_number);
		strcat(runthisline2,endofline);
		runthis<<runthisline;
		runthis<<runthisline2;
		ofstream eachgenesam;
  		eachgenesam.open(path_);

		//if(count==1)
		//{
			//std::cout << elem.first << " " << endl;
	   		for(auto e: elem.second)
	   		{
	   			eachgenesam<<e<<'\n';
	   		}
		//}
	   	eachgenesam.close();
   		
   		
	}
	count0=0;
	for(auto elem : mymap)
	{  	
		count0++;
		char path_[100]= "/home/aysegull/Dropbox/clion/ResearchC++++/histogram";
		char slash[7]="/array";
		char const *gene_number=to_string(count0).c_str();
		char endpath_[5]=".txt";
		strcat(path_,sample_number);
		strcat(path_,slash);
		strcat(path_,gene_number);
		strcat(path_,endpath_);	
		ofstream arrayfile;
  		arrayfile.open(path_);

		string name=elem.first;
	//	cout<<" name : "+elem.first<<endl;
		len=map_length[elem.first];
	//	cout<<len<<endl;
		vector<int> my_vec;
	
		for(int i=0;i<len;i++)
		{
			my_vec.push_back(0);
		}
		
		for(auto e: elem.second)
		{
		//	cout<<e<<endl;
			vector<string> genesam_line=convert_to_vector(e);
			int start=stoi(genesam_line[3]);
			int end=start+genesam_line[9].length();
		//		cout<<start<<endl;
		//			cout<<end<<endl;
			for(int k=start;k<end;k++)
			{
				my_vec[k]=my_vec[k]+1;
			}
				
	   	}
	   	//cout<<name<<endl;
	  	for (int i = 0; i < my_vec.size(); ++i)
		{
	   		//cout<<my_vec[i]<<" ";
	   		arrayfile<<my_vec[i];
	   		arrayfile<<" ";
		}	
	  //	cout<<"\n"<<endl;
	  	arrayfile<<"\n";
	  	arrayfile<<name;
	  	arrayfile<<"\n";
	  	arrayfile.close();
		 		
	}
	
	//cout<<"\n"<<endl;
	string str1="python genelistcreate.py ";
	string str2="\n";
	string str3(sample_number);
	str1=str1+str3;
	str1=str1+str2;
	runthis<<str1;
	runthis<<"date\n";
	runthis.close();
  	return 0;
}

