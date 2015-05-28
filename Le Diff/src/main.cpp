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
	unsigned int i = 0; //index of X
	unsigned int j = 0;	//index of Y

	unsigned int diffI;
	unsigned int diffJ;

	for(size_t k = 0; k < pairs.size(); ++k, i += diffI, j += diffJ)
	{
		diffI = pairs[k].first - i;
		diffJ = pairs[k].second - j;

		if(diffI == 1)
		{
			if(diffJ == 1)
				continue;

			cout << i << "a" << j + 1;

			if(diffJ > 2)
				cout << "," << pairs[k].second - 1;
			cout << endl;

			for(size_t p = j; p < pairs[k].second - 1; ++p)
				cout << "> " << Y[p] << endl;
		}
		else if(diffJ == 1)
		{
			cout << i + 1;
			if(diffI > 2)
				cout << "," << pairs[k].first - 1;
			cout << "d" << j << endl;

			for(size_t p = i; p < pairs[k].first - 1; ++p)
				cout << "< " << X[p] << endl;
		}
		else
		{
			cout << i+1;
			if(diffI > 2)
				cout << "," << pairs[k].first -1;
			cout << "c" << j+1;
			if(diffJ > 2)
				cout << "," << pairs[k].second - 1;
			cout << endl;

			for(size_t p = i; p < pairs[k].first - 1; ++p)
				cout << "< " << X[p] << endl;

			cout << "---" << endl;

			for(size_t p = j; p < pairs[k].second - 1; ++p)
				cout << "> " << Y[p] << endl;

		}
	}


	diffI = X.size() - i;
	diffJ = Y.size() - j;

	if(diffI > 0)
	{
		if(diffJ > 0)
		{
			cout << i+1;
			if(diffI > 2)
				cout << "," << X.size();
			cout << "c" << j+1;
			if(diffJ > 2)
				cout << "," << Y.size();
			cout << endl;

			for(size_t p = i; p < X.size(); ++p)
				cout << "< " << X[p] << endl;

			cout << "---" << endl;

			for(size_t p = j; p < Y.size(); ++p)
				cout << "> " << Y[p] << endl;
		}
		else
		{
			cout << i + 1;
			if(diffI > 2)
				cout << "," << X.size();
			cout << "d" << j << endl;

			for(size_t p = i; p < X.size(); ++p)
				cout << "< " << X[p] << endl;
		}
	}
	else if(diffJ > 0)
	{
		cout << i << "a" << j + 1;

		if(diffJ > 2)
			cout << "," << Y.size();
		cout << endl;

		for(size_t p = j; p < Y.size(); ++p)
			cout << "> " << Y[p] << endl;
	}
/*
	for(size_t k = 0; k < pairs.size(); ++k)
		cout << pairs[k].first << ", " << pairs[k].second << endl;*/
}

int main()
{
	LCS lcs;
	vector<string> X = loadFile("test1.txt");
	vector<string> Y = loadFile("test2.txt");
	vector<string> result;

	lcs.findLCS(X, Y, result);

	displayDiff(X, Y, result, lcs.pairs);

	/*for(size_t k = 0; k < result.size(); k++)
		cout << result[k] << endl;
*/
	return 0;
}



