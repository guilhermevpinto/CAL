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
void displayDiff(std::vector<string> & X, std::vector<string> & Y, list<pair<int, int> > pairs)
{
	unsigned int i = 0; //index of X
	unsigned int j = 0;	//index of Y

	unsigned int diffI;
	unsigned int diffJ;

	list<pair<int,int> >::iterator it = pairs.begin();

	for(it; it != pairs.end(); it++, i += diffI, j += diffJ)
	{
		diffI = it->first - i;
		diffJ = it->second - j;

		if(diffI == 1)
		{
			if(diffJ == 1)
				continue;

			cout << i << "a" << j + 1;

			if(diffJ > 2)
				cout << "," << it->second - 1;
			cout << endl;

			for(size_t p = j; p < it->second - 1; ++p)
				cout << "> " << Y[p] << endl;
		}
		else if(diffJ == 1)
		{
			cout << i + 1;
			if(diffI > 2)
				cout << "," << it->first - 1;
			cout << "d" << j << endl;

			for(size_t p = i; p < it->first - 1; ++p)
				cout << "< " << X[p] << endl;
		}
		else
		{
			cout << i+1;
			if(diffI > 2)
				cout << "," << it->first -1;
			cout << "c" << j+1;
			if(diffJ > 2)
				cout << "," << it->second - 1;
			cout << endl;

			for(size_t p = i; p < it->first - 1; ++p)
				cout << "< " << X[p] << endl;

			cout << "---" << endl;

			for(size_t p = j; p < it->second - 1; ++p)
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

	list<pair<int,int> >::iterator it = pairs.begin();
	for(it; it != pairs.end(); it++)
		cout << it->first << ", " << it->second << endl;*/
}

bool compare(const string &X, const string &Y)
{
	if (X.compare(Y) == 0)
		return true;
	else return false;
}

bool Icompare(const string &X, const string &Y)
{
	if (Y.size() != X.size())
		return false;

	for (unsigned int i = 0; i < X.size(); ++i)
		if (tolower(X[i]) != tolower(Y[i]))
			return false;

	return true;
}

int main()
{
	vector<string> X = loadFile("test1.txt");
	vector<string> Y = loadFile("test2.txt");
	StringCompare comp = &Icompare;
	list<pair<int,int> > pairs = lcs(X, Y, comp);

	displayDiff(X, Y, pairs);

	/*for(size_t k = 0; k < result.size(); k++)
		cout << result[k] << endl;
*/
	return 0;
}



