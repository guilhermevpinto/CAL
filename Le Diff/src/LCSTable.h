/*
 * LCSTable.h
 *
 *  Created on: 25/05/2015
 *      Author: Guilherme
 */

#ifndef LCSTABLE_H_
#define LCSTABLE_H_

#include <string>
#include <vector>

class LCSTable
{
	int m;
	int n;
	int* data;

public:

	~LCSTable()
	{
		delete [] data;
	}

	int getValue(int i, int j) const
	{
		return data[i + (m + 1) * j];
	}

	void setValue(int i, int j, int value)
	{
		data[i + (m + 1) * j] = value;
	}

	void init(std::vector<std::string> X, std::vector<std::string> Y)
	{
		m = X.size();
		n = Y.size();
		data = new int[(m + 1) * (n + 1)];


		for(int i = 0; i <= m; ++i)
			setValue(i, 0, 0);

		for(int j = 0; j < n; ++j)
			setValue(0, j, 0);

		for(int i = 0; i < m; ++i)
			for(int j = 0; j < n; ++j)
			{
				if(X[i].compare(Y[j]) == 0)
					setValue(i + 1, j + 1, getValue(i, j) + 1);
				else
					setValue(i + 1, j + 1, std::max(getValue(i+1,j), getValue(i,j+1)));
			}
	}
};



#endif /* LCSTABLE_H_ */
