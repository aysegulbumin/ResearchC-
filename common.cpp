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