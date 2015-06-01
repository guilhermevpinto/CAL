#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>
#include <utility>

#include "Diff.h"

using namespace std;

static vector<string> loadFile(const string &filename)
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
	{
		cout << "Failed to open " << filename << endl;
		exit(EXIT_FAILURE);
	}

	return result;
}

void diff(const string &file1, const string &file2, StringCompare compare, OutputDiff output)
{
	vector<string> X = loadFile(file1);
	vector<string> Y = loadFile(file2);

	list<pair<int, int> > pairs = lcs(X, Y, compare);

	output(file1, file2, X, Y, pairs);
}

static vector<vector<int> > init(const vector<string> & X, const vector<string> & Y, StringCompare compare)
{
	vector<vector<int> > table(X.size() + 1, vector<int>(Y.size()+1, 0));

	for(size_t i = 1; i <= X.size(); ++i)
	{
		for(size_t j = 1; j <= Y.size(); ++j)
		{
			if(compare(X[i-1], Y[j-1]))
				table[i][j] = table[i-1][j-1] + 1;
			else
				table[i][j] = std::max(table[i-1][j], table[i][j-1]);
		}
	}
	return table;
}

static list<pair<int, int> > backTrack(const vector<vector<int> > & table, const vector<string> & X, const vector<string> & Y, StringCompare compare)
{
	list<pair<int, int> > pairs;

	size_t i = X.size();
	size_t j = Y.size();

	while (i > 0 && j > 0)
	{
		if(compare(X[i-1], Y[j-1]))
		{
			pairs.push_front(std::make_pair(i, j));
			--i;
			--j;
		}
		else if(table.at(i).at(j - 1) > table.at(i - 1).at(j))
			--j;
		else
			--i;
	}

	return pairs;
}

list<pair<int,int> > lcs(const vector<string> & X, const vector<string> & Y, StringCompare compare)
{
	vector<vector<int> > table = init(X, Y, compare);

	return backTrack(table, X, Y, compare);
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
			++i;
		else if(isspace(Y[j]))
			++j;
		else if(X[i] != Y[j])
			return false;
		else
		{
			++i;
			++j;
		}
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
		{
			++i;
			++j;
		}
	}

	return i == X.size() && j == Y.size();
}


static void standardAdd(unsigned int i, unsigned int j, int diffJ, unsigned int final_line, vector<string> &Y)
{
	cout << i << "a" << j + 1;

	if(diffJ > 2)
		cout << "," << final_line - 1;
	cout << endl;

	for(size_t p = j; p < final_line - 1; ++p)
		cout << "> " << Y[p] << endl;
}

static void standardDelete(unsigned int i, unsigned int j, int diffI, unsigned int final_line, vector<string> &X)
{
	cout << i + 1;
	if(diffI > 2)
		cout << "," << final_line - 1;
	cout << "d" << j << endl;

	for(size_t p = i; p < final_line - 1; ++p)
		cout << "< " << X[p] << endl;
}

static void standardChange(unsigned int i, unsigned int j, int diffI, int diffJ, unsigned int final_lineI, unsigned int final_lineJ, vector<string> &X, vector<string> &Y)
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
