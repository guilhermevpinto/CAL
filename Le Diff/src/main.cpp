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
void standardOutput(const string &file1, const string &file2, vector<string> &X, vector<string> &Y, list<pair<int, int> > pairs)
{
	unsigned int i = 0; //index of X
	unsigned int j = 0;	//index of Y

	unsigned int diffI;
	unsigned int diffJ;

	for(list<pair<int,int> >::iterator it = pairs.begin();
			it != pairs.end();
			it++, i += diffI, j += diffJ)
	{
		diffI = it->first - i;
		diffJ = it->second - j;

		if (diffI > 1)
		{
			if (diffJ > 1)
				standardChange(i, j, diffI, diffJ, it->first,it->second, X, Y);
			else
				standardDelete(i, j, diffI, it->first, X);
		}
		else if (diffJ > 1)
			standardAdd(i, j, diffJ, it->second, Y);
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
}

void QOutput(const string &file1, const string &file2, vector<string> &X, vector<string> &Y, list<pair<int, int> > pairs)
{
	if(pairs.size() != X.size() || pairs.size() != Y.size())
		cout << "Files " + file1 + " and " + file2 + " differ\n";
}

void BOutput(const string &file1, const string &file2, vector<string> &X, vector<string> &Y, list<pair<int, int> > pairs)
{
	unsigned int i = 0; //index of X
	unsigned int j = 0;	//index of Y

	unsigned int diffI;
	unsigned int diffJ;

	for(list<pair<int,int> >::iterator it = pairs.begin();
			it != pairs.end();
			it++, i += diffI, j += diffJ)
	{
		diffI = it->first - i;
		diffJ = it->second - j;

		if (diffI > 1)
		{
			if (diffJ > 1)
				standardChange(i, j, diffI, diffJ, it->first,it->second, X, Y);
			else
			{
				size_t total_line_size = 0;
				for (size_t k = it->first - 1; k > i; --k)
					total_line_size += X.at(k - 1).length();
				if (total_line_size > 0)
					standardDelete(i, j, diffI, it->first, X);
			}
		}
		else if (diffJ > 1)
		{
			size_t total_line_size = 0;
			for (size_t k = it->second - 1; k > j; --k)
				total_line_size += Y.at(k - 1).length();
			if (total_line_size > 0)
				standardAdd(i, j, diffJ, it->second, Y);
		}
	}


	diffI = X.size() - i;
	diffJ = Y.size() - j;

	if(diffI > 0)
	{
		if(diffJ > 0)
			standardChange(i, j, diffI, diffJ, X.size(), Y.size(), X, Y);
		else
		{
			size_t total_line_size = 0;
			for (size_t k = X.size(); k > i; --k)
				total_line_size += X.at(k - 1).length();
			if (total_line_size > 0)
				standardDelete(i, j, diffI, X.size(), X);
		}
	}
	else if(diffJ > 0)
	{
		size_t total_line_size = 0;
		for (size_t k = Y.size(); k > j; --k)
			total_line_size += Y.at(k - 1).length();
		if (total_line_size > 0)
			standardAdd(i, j, diffJ, Y.size() + 1, Y);
	}
}

void QBOutput(const string &file1, const string &file2, vector<string> &X, vector<string> &Y, list<pair<int, int> > pairs)
{
	unsigned int i = 0; //index of X
	unsigned int j = 0;	//index of Y

	unsigned int diffI;
	unsigned int diffJ;

	for(list<pair<int,int> >::iterator it = pairs.begin();
			it != pairs.end();
			it++, i += diffI, j += diffJ)
	{
		diffI = it->first - i;
		diffJ = it->second - j;

		if (diffI > 1)
		{
			if (diffJ > 1)
			{
				cout << "Files " + file1 + " and " + file2 + " differ\n";
				return;
			}
			else
			{
				size_t total_line_size = 0;
				for (size_t k = it->first - 1; k > i; --k)
					total_line_size += X.at(k - 1).length();
				if (total_line_size > 0)
				{
					cout << "Files " + file1 + " and " + file2 + " differ\n";
					return;
				}
			}
		}
		else if (diffJ > 1)
		{
			size_t total_line_size = 0;
			for (size_t k = it->second - 1; k > j; --k)
				total_line_size += Y.at(k - 1).length();
			if (total_line_size > 0)
			{
				cout << "Files " + file1 + " and " + file2 + " differ\n";
				return;
			}
		}
	}


	diffI = X.size() - i;
	diffJ = Y.size() - j;

	if(diffI > 0)
	{
		if(diffJ > 0)
		{
			cout << "Files " + file1 + " and " + file2 + " differ\n";
			return;
		}
		else
		{
			size_t total_line_size = 0;
			for (size_t k = X.size(); k > i; --k)
				total_line_size += X.at(k - 1).length();
			if (total_line_size > 0)
			{
				cout << "Files " + file1 + " and " + file2 + " differ\n";
				return;
			}
		}
	}
	else if(diffJ > 0)
	{
		size_t total_line_size = 0;
		for (size_t k = Y.size(); k > j; --k)
			total_line_size += Y.at(k - 1).length();
		if (total_line_size > 0)
		{
			cout << "Files " + file1 + " and " + file2 + " differ\n";
			return;
		}
	}
}

bool standardCompare(const string &X, const string &Y)
{
	return X == Y;
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
			++i;
		else if(isspace(Y[j]))
			++j;
		else if (tolower(X[i]) != tolower(Y[j]))
			return false;
		else
		{	++i;
			++j;
		}
	}

	return i == X.size() && j == Y.size();
}

int main(int argc, char **argv)
{
	bool Qflag = false;
	bool Iflag = false;
	bool Wflag = false;
	bool Bflag = false;
	string file1 = "";
	string file2 = "";

	for (int i = 1; i < argc; ++i) {

		string arg(argv[i]);

		if (arg.at(0) == '-')
		{
			if (arg.length() == 1)
			{
				cout << "Expected option after '" << arg << "'" << endl;
				exit(EXIT_FAILURE);
			}

			if (arg.at(1) == '-')
			{
				if (arg == "--ignore-case")
					Iflag = true;
				else if (arg == "--ignore-all-space")
					Wflag = true;
				else if (arg == "--ignore_blank_lines")
					Bflag = true;
				else if (arg == "--brief")
					Qflag = true;
				else
				{
					cout << "Unknown option: " << arg << endl;
					exit(EXIT_FAILURE);
				}
			}
			else
				for (size_t j = 1; j < arg.length(); ++j)
					switch (arg.at(j))
					{
					case 'i':
						Iflag = true;
						break;
					case 'w':
						Wflag = true;
						break;
					case 'B':
						Bflag = true;
						break;
					case 'q':
						Qflag = true;
						break;
					default:
						cout << "Unknown option: -" << arg.at(j) << endl;
						exit(EXIT_FAILURE);
					}
		}
		else if (file1 == "")
			file1 = argv[i];
		else if (file2 == "")
			file2 = argv[i];
		else
		{
			cout << "Too many input files" << endl;
			exit(EXIT_FAILURE);
		}
	}

	if (file1 == "" || file2 == "")
	{
		cout << "Two files required for comparison\n" << endl;
		exit(EXIT_FAILURE);
	}

	StringCompare compare = standardCompare;
	OutputDiff output = standardOutput;

	if(Qflag && Bflag)
		output = QBOutput;
	else if(Qflag)
		output = QOutput;
	else if (Bflag)
		output = BOutput;

	if(Wflag && Iflag)
		compare = IWCompare;
	else if (Wflag)
		compare = WCompare;
	else if (Iflag)
		compare = ICompare;


	vector<string> X = loadFile(file1);
	vector<string> Y = loadFile(file2);

	list<pair<int,int> > pairs = lcs(X, Y, compare);

	output(file1, file2, X, Y, pairs);
	return 0;
}



