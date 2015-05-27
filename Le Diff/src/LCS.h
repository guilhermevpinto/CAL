/*
 * LCS.h
 *
 *  Created on: 25/05/2015
 *      Author: Guilherme
 */

#ifndef LCS_H_
#define LCS_H_

#include "LCSTable.h"
#include <vector>
#include <utility>

class LCS
{

	void backTrack(const LCSTable & table, const std::vector<std::string> & X, const std::vector<std::string> & Y, int i, int j, std::vector<std::string> & result)
	{
		if(i == 0 || j == 0)
			return;

		if(X[i - 1].compare(Y[j - 1]) == 0)
		{
			backTrack(table, X, Y, i-1, j-1, result);
			result.push_back(X[i-1]);
			pairs.push_back(std::make_pair(i-1, j-1));
			return;
		}

		if(table.getValue(i, j-1) > table.getValue(i-1, j))
			backTrack(table, X, Y, i, j-1, result);
		else
			backTrack(table, X, Y, i-1, j, result);
	}

public:

	std::vector<std::pair<int,int> > pairs;

	void findLCS(std::vector<std::string> &X, std::vector<std::string> &Y, std::vector<std::string> &result)
	{
		LCSTable table;
		table.init(X, Y);
		backTrack(table, X, Y, X.size(), Y.size(), result);

	}
};



#endif /* LCS_H_ */
