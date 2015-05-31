/*
 * main.cpp
 *
 *  Created on: 25/05/2015
 *      Author: Guilherme
 */

#include <iostream>
#include "LCS.h"
#include <fstream>

#define FILE_EXTENSION ".txt"

using namespace std;

string file1 = "test1";
string file2 = "test2";

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

void standardAdd(unsigned int i, unsigned int j, int diffJ, unsigned int final_line, vector<string> &Y)
{
	cout << i << "a" << j + 1;

	if(diffJ > 2)
		cout << "," << final_line - 1;
	cout << endl;

	for(size_t p = j; p < final_line - 1; ++p)
		cout << "> " << Y[p] << endl;
}

void standardDelete(unsigned int i, unsigned int j, int diffI, unsigned int final_line, vector<string> &X)
{
	cout << i + 1;
	if(diffI > 2)
		cout << "," << final_line - 1;
	cout << "d" << j << endl;

	for(size_t p = i; p < final_line - 1; ++p)
		cout << "< " << X[p] << endl;
}

void standardChange(unsigned int i, unsigned int j, int diffI, int diffJ, unsigned int final_lineI, unsigned int final_lineJ, vector<string> &X, vector<string> &Y)
{
	cout << i+1;
	if(diffI > 2)
		cout << "," << final_lineI -1;
	cout << "c" << j+1;
	if(diffJ > 2)
		cout << "," << final_lineJ - 1;
	cout << endl;

	for(size_t p = i; p < final_lineI - 1; ++p)
		cout << "< " << X[p] << endl;

	cout << "---" << endl;

	for(size_t p = j; p < final_lineJ - 1; ++p)
		cout << "> " << Y[p] << endl;
}

/**
 * 	@brief Apresentacao da informacao adicionada, apagada e substituida entre os dois ficheiros.
 */
void standardOutput(vector<string> &X, vector<string> &Y, list<pair<int, int> > pairs)
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

			standardAdd(i, j, diffJ, it->second, Y);
		}
		else if(diffJ == 1)
			standardDelete(i, j, diffI, it->first, X);
		else
			standardChange(i, j, diffI, diffJ, it->first,it->second, X, Y);
	}


	diffI = X.size() - i;
	diffJ = Y.size() - j;

	if(diffI > 0)
	{
		if(diffJ > 0)
			standardChange(i, j, diffI, diffJ, X.size(), Y.size(), X, Y);
		else
			standardDelete(i, j, diffI, X.size(), X);
	}
	else if(diffJ > 0)
		standardAdd(i, j, diffJ, Y.size() +1, Y);
	/*

	list<pair<int,int> >::iterator it = pairs.begin();
	for(it; it != pairs.end(); it++)
		cout << it->first << ", " << it->second << endl;*/
}

void QOutput(vector<string> &X, vector<string> &Y, list<pair<int, int> > pairs)
{
	if(pairs.size() != 0)
		cout << "Files " + file1 + " and " + file2 + " differ\n";
}

void BOutput(vector<string> &X, vector<string> &Y, list<pair<int, int> > pairs)
{
}

bool standardCompare(const string &X, const string &Y)
{
	if (X.compare(Y) == 0)
		return true;
	else return false;
}

bool ICompare(const string &X, const string &Y)
{
	if (Y.size() != X.size())
		return false;

	for (unsigned int i = 0; i < X.size(); ++i)
		if (tolower(X[i]) != tolower(Y[i]))
			return false;

	return true;
}

bool WCompare(const string &X, const string &Y)
{
	unsigned int i = 0;
	unsigned int j = 0;

	while(i < X.size() || j < Y.size())
	{
		if(isspace(X[i]))
		{
			++i;
			continue;
		}

		if(isspace(Y[j]))
		{
			++j;
			continue;
		}

		if(X[i] != Y[j])
			return false;

		++i;
		++j;
	}

	return i == X.size() && j == Y.size();
}

bool IWCompare(const string &X, const string &Y)
{
	unsigned int i = 0;
	unsigned int j = 0;

	while(i < X.size() || j < Y.size())
	{
		if(isspace(X[i]))
		{
			++i;
			continue;
		}

		if(isspace(Y[j]))
		{
			++j;
			continue;
		}

		if (tolower(X[i]) != tolower(Y[j]))
			return false;

		++i;
		++j;
	}

	return i == X.size() && j == Y.size();
}

int main()
{
	bool Qflag = false;
	bool Iflag = false;
	bool Wflag = false;
	bool Bflag = false;
	string flags = "-wi";

	StringCompare compare = &standardCompare;
	OutputDiff output = &standardOutput;

	for(size_t i = 1; i < flags.size(); ++i)
	{
		if(flags[i] == 'q' || flags[i] == 'Q')
			Qflag = true;
		else if (flags[i] == 'i' || flags[i] == 'I')
			Iflag = true;
		else if(flags[i] == 'w' || flags[i] == 'W')
			Wflag = true;
		else if (flags[i] == 'b' || flags[i] == 'B')
			Bflag = true;
	}


	if(Qflag)
		output = &QOutput;
	else if (Bflag)
		output = &BOutput;

	if(Wflag && Iflag)
		compare = &IWCompare;
	else if (Wflag)
		compare = &WCompare;
	else if (Iflag)
		compare = &ICompare;


	vector<string> X = loadFile(file1 + FILE_EXTENSION);
	vector<string> Y = loadFile(file2 + FILE_EXTENSION);

	list<pair<int,int> > pairs = lcs(X, Y, compare);

	output(X, Y, pairs);
	return 0;
}



