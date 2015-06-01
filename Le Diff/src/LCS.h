/*
 * LCS.h
 *
 *  Created on: 25/05/2015
 *      Author: Guilherme
 */

#ifndef LCS_H_
#define LCS_H_

#include <vector>
#include <list>
#include <utility>
#include <algorithm>
#include <iostream>

typedef bool (*StringCompare)(const std::string &, const std::string &);
typedef void (*OutputDiff) (const std::string &, const std::string &, std::vector<std::string> &X, std::vector<std::string> &Y, std::list<std::pair<int, int> > pairs);

std::vector<std::vector<int> > init(const std::vector<std::string> & X, const std::vector<std::string> & Y, StringCompare compare)
{
	std::vector<std::vector<int> > table(X.size() + 1, std::vector<int>(Y.size()+1, 0));

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

std::list<std::pair<int, int> > backTrack(const std::vector<std::vector<int> > & table, const std::vector<std::string> & X, const std::vector<std::string> & Y, StringCompare compare)
{
	std::list<std::pair<int, int> > pairs;

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

std::list<std::pair<int,int> > lcs(const std::vector<std::string> & X, const std::vector<std::string> & Y, StringCompare compare)
{
	std::vector<std::vector<int> > table = init(X, Y, compare);

	return backTrack(table, X, Y, compare);
}



#endif /* LCS_H_ */
