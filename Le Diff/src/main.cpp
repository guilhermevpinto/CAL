/*
 * main.cpp
 *
 *  Created on: 25/05/2015
 *      Author: Guilherme
 */

#include <iostream>
#include "LCS.h"
#include <fstream>

using namespace std;

vector<string> loadFile(string filename)
{
	vector<string> result;

	ifstream file (filename.c_str());
	string line;

	if(file.is_open())
	{
		while(!file.eof())
		{
			getline(file, line);
			result.push_back(line);
		}
	}
	else
		cout << "Failed to open " << filename << endl;

	return result;
}


/**
 * 	@brief Apresentacao da informacao adicionada, apagada e substituida entre os dois ficheiros.
 */
void displayDiff(std::vector<string> & X, std::vector<string> & Y, std::vector<string> & result, vector<pair<int, int> > pairs)
{

}

int main()
{
	LCS lcs;
	vector<string> X = loadFile("test1.txt");
	vector<string> Y = loadFile("test2.txt");
	vector<string> result;

	lcs.findLCS(X, Y, result);


	displayDiff(X, Y, result, lcs.pairs);

	return 0;
}



