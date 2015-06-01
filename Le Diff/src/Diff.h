/*
 * LCS.h
 *
 *  Created on: 25/05/2015
 *      Author: Guilherme
 */

#ifndef LCS_H_
#define LCS_H_

#include <list>
#include <string>
#include <utility>
#include <vector>

typedef bool (*StringCompare)(const std::string &, const std::string &);
typedef void (*OutputDiff) (const std::string &, const std::string &, std::vector<std::string> &X, std::vector<std::string> &Y, std::list<std::pair<int, int> > pairs);


void diff(const std::string &file1, const std::string &file2, StringCompare compare, OutputDiff output);

std::list<std::pair<int,int> > lcs(const std::vector<std::string> & X, const std::vector<std::string> & Y, StringCompare compare);

/**
 * 	Funcao de comparacao das linhas dos dois ficheiros.
 */
bool standardCompare(const std::string &X, const std::string &Y);

bool ICompare(const std::string &X, const std::string &Y);

bool WCompare(const std::string &X, const std::string &Y);

bool IWCompare(const std::string &X, const std::string &Y);


/**
 * 	Apresentacao da informacao adicionada, apagada e substituida entre os dois ficheiros.
 */
void standardOutput(const std::string &file1, const std::string &file2, std::vector<std::string> &X, std::vector<std::string> &Y, std::list<std::pair<int, int> > pairs);

void QOutput(const std::string &file1, const std::string &file2, std::vector<std::string> &X, std::vector<std::string> &Y, std::list<std::pair<int, int> > pairs);

void BOutput(const std::string &file1, const std::string &file2, std::vector<std::string> &X, std::vector<std::string> &Y, std::list<std::pair<int, int> > pairs);

void QBOutput(const std::string &file1, const std::string &file2, std::vector<std::string> &X, std::vector<std::string> &Y, std::list<std::pair<int, int> > pairs);


#endif /* LCS_H_ */
