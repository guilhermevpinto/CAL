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
	unsigned int i = 0;
	unsigned int j = 0;

	for(size_t k = 0; k < pairs.size(); ++k)
	{
		int diffI = pairs[k].first - i;
		int diffJ = pairs[k].second - j;

		if(diffI > diffJ)
		{
			if(diffJ == 1) //means that lines from X were deleted
			{
				if(diffI > 2)
					cout << i << "d" << i+1 << "," << pairs[k].first << endl;
				else
					cout << i << "d" << pairs[k].first << endl;

				for(int p = i; p < pairs[k].first; ++p)
					cout << "< " << X[p] << endl;
			}
			else //means that lines on X were swapped for other lines of Y
			{
				if(diffI > 2)
					cout << i+2 << "," << pairs[k].first;
				else
					cout << i+2;

				cout << "c";

				if(diffJ > 2)
					cout << j+2 << "," << pairs[k].second+2 << endl;
				else
					cout << j+2 << endl;

				for(int p = i+1; p < pairs[k].first; ++p)
					cout << "< " << X[p] << endl;

				cout << "---" << endl;

				for(int p = j+1; p < pairs[k].second; ++p)
					cout << "> " << Y[p] << endl;
			}
		}
		else if(diffI < diffJ)
		{
			if(diffI == 0) //means that lines of Y were added
			{
				if(diffJ > 2)
					cout << i << "a" << j+1 << "," << pairs[k].second << endl;
				else
					cout << i << "a" << j+1 << endl;

				for(int p = j; p < pairs[k].second; ++p)
					cout << "> " << Y[p] << endl;
			}
			else
			{
				if(diffI > 2)
					cout << i+2 << "," << pairs[k].first;
				else
					cout << i+2;

				cout << "c";

				if(diffJ > 2)
					cout << j+2 << "," << pairs[k].second+2 << endl;
				else
					cout << j+2 << endl;

				for(int p = i+1; p < pairs[k].first; ++p)
					cout << "< " << X[p] << endl;

				cout << "---" << endl;

				for(int p = j+1; p < pairs[k].second; ++p)
					cout << "> " << Y[p] << endl;
			}
		}
		else if(diffI == diffJ && diffI > 1)
		{
			if(diffI > 2)
				cout << i+2 << "," << pairs[k].first;
			else
				cout << i+2;

			cout << "c";

			if(diffJ > 2)
				cout << j+2 << "," << pairs[k].second+2 << endl;
			else
				cout << j+2 << endl;

			for(int p = i+1; p < pairs[k].first; ++p)
				cout << "< " << X[p] << endl;

			cout << "---" << endl;

			for(int p = j+1; p < pairs[k].second; ++p)
				cout << "> " << Y[p] << endl;
		}


		i += diffI;
		j += diffJ;

	}

	if(i < X.size()-1)
	{
		cout << i+1 << "d" << i+2 << "," << X.size() << endl;

		for(size_t p = i+1; p < X.size(); ++p)
			cout << "< " << X[p] << endl;
	}
	else if(j < Y.size()-1)
	{
		cout << i+1 << "a" << j+2 << "," << Y.size() << endl;

		for(size_t p = j+1; p < Y.size(); ++p)
			cout << "> " << Y[p] << endl;
	}
}

int main()
{
	LCS lcs;
	vector<string> X = loadFile("test1.txt");
	vector<string> Y = loadFile("test2.txt");
	vector<string> result;

	lcs.findLCS(X, Y, result);

	displayDiff(X, Y, result, lcs.pairs);

	for(size_t k = 0; k < lcs.pairs.size(); k++)
		cout << lcs.pairs[k].first << ", " << lcs.pairs[k].second << endl;

	return 0;
}



