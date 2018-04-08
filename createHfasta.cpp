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
	while(std::getline(ss, token, ' ')) 
	{
		line_vector.push_back(token);
		//cout << token << '\n';
	}
	return line_vector;
}

vector<int> convert_to_vector2(string input)
{
	vector<char> v;

	istringstream ss(input);
	string token;
	vector<int> line_vector;
	while(std::getline(ss, token, ' ')) 
	{
		line_vector.push_back(stoi(token));
		//cout << token << '\n';
	}
	return line_vector;
}

int main (int argc, char** argv) 
{
	string line;
	string line2;
	int len=0;
	char path[60] = "/home/aysegull/Dropbox/clion/ResearchC++++/histogram";
	char path2[60] = "/home/aysegull/Dropbox/clion/ResearchC++++/histogram";
	char path3[100] = "/home/aysegull/Dropbox/clion/ResearchC++++/database/megares_database_v1.01.fasta";
	char path6[60]="/home/aysegull/Dropbox/clion/ResearchC++++/histogram";
	
	if(argc<=1)
	{
		cout<<"Sample number is missing"<<endl;
	}
	for (int i = 1; i < argc; ++i)
	{
        cout << "Sample " <<argv[i] << "\n";
	}
	
	char *sample_number=argv[1];

	char endpath[10]="/HLs.txt";
	char endpath2[15]="/aboutH.txt";
	char endpath6[15]="/blat1.sh";

	strcat(path6,sample_number);	
	strcat(path6,endpath6);
	ofstream blatfile;
  	blatfile.open(path6);


	blatfile<<"#!/bin/bash\n";
	blatfile<<"#SBATCH --job-name=blat1\n";
	blatfile<<"#SBATCH --mail-type=ALL\n";
	blatfile<<"#SBATCH --qos=boucher-b\n";
	blatfile<<"#SBATCH --mail-user=aysegul.bumin@ufl.edu\n";
	blatfile<<"#SBATCH --ntasks=1\n";
	blatfile<<"#SBATCH --cpus-per-task=1\n";
	blatfile<<"#SBATCH --mem=10gb\n";
	blatfile<<"#SBATCH --time=90:00:00\n";
	blatfile<<"#SBATCH --output=blat1.out\n";
	blatfile<<"date;hostname;pwd\n";
	//blatfile<<"module load blat\n";

	strcat(path,sample_number);	
	strcat(path,endpath);

	strcat(path2,sample_number);	
	strcat(path2,endpath2);
	ofstream about;
  	about.open(path2);

   	ifstream myfile (path);

  	map <string, vector<int> > starts;
  	map <string, vector<int> > ends;
  	

  	int count=0;
  	vector<int> st;
  	vector<int> en;
	vector<string> my_letters;
	vector<int> my_indices;
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
		    				my_letters=convert_to_vector(line);
		    				break;
	    				}
	    		case 3:

	    				break;
	    		case 4: 
	    				{
		    				my_indices=convert_to_vector2(line);	
		    				break;
	    				}
	    				
	    		case 5:
	    				break;
	    		case 6:
	    				{
		    				string genename=line;
		    				
		    				for (int i=0;i<my_letters.size();i++)
		    				{
		    					
		    					if(my_letters[i]=="H")
		    					{
		    						
		    						if(i==0)
		    						{
		    							st.push_back(0);
		    							en.push_back(my_indices[0]);
		    						}
		    						else
		    						{
		    							st.push_back(my_indices[i-1]);
		    							en.push_back(my_indices[i]);
		    						}
		    					}
		    				}
		    				//cout<<endl;
		    				starts[genename];
		    				starts[genename]=st;
		    				/*cout<<	"Starts...."<<endl;
		    				for (int i = 0; i < st.size(); ++i)
		    				{
		    					
		    					cout<<st[i]<<" ";
		    				}
		    				
		    				cout<<endl;*/
		    				ends[genename];
		    				ends[genename]=en;
		    				/*cout<<	"Ends...."<<endl;
		    				for (int i = 0; i < en.size(); ++i)
		    				{
		    					
		    					cout<<en[i]<<" ";
		    				}
		    				cout<<endl;*/
		    				count=0;
		    				st.clear();
							en.clear();
							my_letters.clear();
							my_indices.clear();
		    				break;

	    				}
	    				
	    		default:
	    				cout<<"Default"<<endl;
	    	
	    	}


	    	
    	}
    		
	}
	


  	else cout << "Unable to open file"; 
  	

  	for(auto elem : starts)
	{
		

		//if(count==1)
		//{
			//cout<<"Name"<<endl;
			about<<"Name\n";
			//std::cout << elem.first << " " << endl;
			about<<elem.first<<"\n";
			//cout<<"Starts"<<endl;
			about<<"Starts\n";
	   		for(auto e: elem.second)
	   		{
	   			//	cout<<e<<" ";
	   				about<<e;
	   				about<<" ";

	   		}
	   		about<<"\n";
	   		about<<"Ends\n";
	   		//cout<<"\n";
	   		//cout<<"Ends"<<endl;
	   		for(int k=0;k<ends[elem.first].size();k++)
	   		{
	   		//		cout<<ends[elem.first][k]<<" ";
	   				about<<ends[elem.first][k]<<" ";

	   		}
		//}	
	   		//cout<<"\n";
	   		about<<"\n";
	   		
   		
   		
	}
	about.close();
	int c=0;
	for(auto elem : starts)
	{
			c++;
			int countt=0;
			int number_of_genes=0;
			int flag=0;
			string to_write="";

			char endpath4[10]="/gene_H";
			char en4[10]="gene_H";
			char endpath5[10]=".fasta";
			char path4[60] = "/home/aysegull/Dropbox/clion/ResearchC++++/histogram";
			strcat(path4,sample_number);	
			strcat(path4,endpath4);
			strcat(path4,to_string(c).c_str());
			strcat(path4,endpath5);

			strcat(en4,to_string(c).c_str());
			strcat(en4,endpath5);

			blatfile<<"./blat 	"<<en4 <<"	"<< path3<<"	res1_"<<to_string(c)<<".psl"<<"\n";

			ifstream thiss (path3);
			ofstream fastas;
			//cout<<path4<<endl;
  			fastas.open(path4);


			if (thiss.is_open())
		  	{	

			    while ( getline (thiss,line) )
			    {
			    	count++;
			    	if(count==1)
			    	{
			    		if (line.find(elem.first) != std::string::npos) //if the gene is found in megares
				    	{
				    		flag=1;

			    		}
			    		else
			    		{
			    			flag=0;
			    		}
			    	}
			    	if(count==2)
			    	{
			    		if(flag==1)//this gene has H regions
			    		{
			    			number_of_genes++;
			    			for(int i=0;i<ends[elem.first].size();i++)
			    			{
			    				to_write=to_write+">H"+to_string(i)+"	"+to_string(ends[elem.first][i]-starts[elem.first][i])+"	"+to_string(starts[elem.first][i])+"_"+to_string(ends[elem.first][i])+"	";
			    				to_write=to_write+elem.first;
				    			to_write+="\n";
			    				to_write+=line.substr(starts[elem.first][i],ends[elem.first][i]-starts[elem.first][i])+"\n";

			    			}

			    		}
			    		count=0;
			    	}

			    }
			    thiss.close();


			}
			//cout<<to_write;
			fastas<<to_write;
			fastas.close();
   		
   		
	}
	blatfile<<"date\n";
	blatfile.close();
  	return 0;
	    	
}