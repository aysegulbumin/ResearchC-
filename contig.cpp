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

vector< vector<int> > mymatrix;



vector<int> convert_to_vector(string input)
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

vector<string> convert_to_vector2(string input)
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

void add_to_matrix(int start_here, int end_here, string filepath)
{
	ifstream mysamfile (filepath);
	string line_;
	cout<<filepath<<endl;
	if (mysamfile.is_open())
  	{	

	    	while ( getline (mysamfile,line_) )
	    	{
	    		cout<<"File is read-*********************"<<endl;
	    		cout<<line_;
	    		vector<string> stringvec=convert_to_vector2(line_);
	    		/*cout<<"Start of H"<<endl;
	    		cout<<start_here<<endl;
	    		cout<<"read align start"<<endl;
	    		cout<<stoi(stringvec[3]) <<endl;*/
	    		cout<<"Sam file line"<<endl;
	    		for(int k=0;k<stringvec.size();k++)
	    		{
	    			cout<<stringvec[k]<<"\t";
	    		}
	    		cout<<endl;
	    		cout<<"Stoi"<<endl;
	    		cout<<stoi(stringvec[3])<<endl;
	    		if(start_here<= stoi(stringvec[3]) && stringvec[9].size()+stoi(stringvec[3])<=int(end_here))
	    		{
	    			//cout<<"Ever enters here"<<endl;
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
			switch(max_base)
			{
				case 0:
						{
							temp_contig+="A";
							break;
						}
				case 1:
						{
							temp_contig+="C";
							break;	
						}
						
				case 2:
						{
							temp_contig+="G";
							break;
						}				
				case 3:
						{
							temp_contig+="T";
							break;
						}
						
			}
		}
		
		
	}

	return temp_contig;

}


int main (int argc, char** argv) 
{
	string line;
	string line2;
	string line_matrix;
	cout<<"Contig.cpp"<<endl;
	//Initialize the matrix
	vector<int> v;
	for(int i=0;i<=4000;i++)
	{
		v.push_back(0);
	}
	for (int j=0;j<4;j++)
	{
		mymatrix.push_back(v);

	}
		cout<<	"Printing matrix"<<endl;
	   		for (int j=0;j<4;j++)
			{
				for(int i=0;i<=4000;i++)
				{
					cout<<mymatrix[j][i]<<" ";	
				}
				
				cout<<endl;
				cout<<endl;

			}
	int len=0;
	char path[60] = "/home/aysegull/Dropbox/clion/ResearchC++++/histogram";
	char endpath[20]="/aboutH.txt";

	char path2[60] = "/home/aysegull/Dropbox/clion/ResearchC++++/histogram";
	char slash2[5]="/";
	char endpath2[20]=".sam";

	char path3[50] = "/home/aysegull/Dropbox/clion/ResearchC++++/all";


	if(argc<=1)
	{
		cout<<"Sample number is missing"<<endl;
	}
	for (int i = 1; i < argc; ++i)
	{
        cout << "Sample " <<argv[i] << "\n";
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
			    				char path2[60] = "/home/aysegull/Dropbox/clion/ResearchC++++/histogram";
								char slash2[5]="/";
								char endpath2[20]=".sam";
			    				strcat(path2,sample_number);
			    				strcat(path2,slash2);
			    				strcat(path2,to_string(c).c_str());	
								strcat(path2,endpath2);
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
								    		vector<string> lin=convert_to_vector2(line2);
								    		string look= lin[3];
								    		if (look.find(line) != std::string::npos) //if the gene is found in samfile
									    	{
									    		samfile<<line2<<"\n";

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
	    						starts=convert_to_vector(line);
	    						name_starts[genename];
	    						name_starts[genename]=starts;

	    						break;
	    					}

	    			case 5:
	    					break;
	    			case 6:
	    					{
	    						ends=convert_to_vector(line);	
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
  	for(auto elem : name_starts)
	{
		

	   		for(int k=0;k<name_ends[elem.first].size();k++)
	   		{
	   				start_here=name_starts[elem.first][k];
	   				end_here=name_ends[elem.first][k];
	   				filepath=name_sam[elem.first];
	   				cout<<"Gene name"<<endl;
	   				cout<<elem.first<<endl;
	   				add_to_matrix(start_here,end_here,filepath);
	   				

	   		}
	   		string mycon=create_contig();
			//cout<<"Name"<<endl;
			//cout<<elem.first<<endl;
			//cout<<"Contig"<<endl;
			//cout<<mycon<<endl;
			mymatrix.clear();
							
	   		
			   				

	   		

   		
   		
	}
 
  	return 0;
}

