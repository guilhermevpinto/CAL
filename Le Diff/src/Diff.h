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

/**
 *	Algoritmo de comparacao e respetiva analise de dois ficheiros de texto.
 */
void diff(const std::string &file1, const std::string &file2, StringCompare compare, OutputDiff output);

/**
 * Algoritmo de procura do maior conjunto ordenado de linhas igual entre os dois textos.
 */
std::list<std::pair<int,int> > lcs(const std::vector<std::string> & X, const std::vector<std::string> & Y, StringCompare compare);

/**
 * 	Comparacao de linhas de texto.
 */

// mesmo numero de caracteres e caracteres na mesma posicao iguais
bool standardCompare(const std::string &X, const std::string &Y);

// mesmo numero de caracteres e caracteres na mesma posicao iguais se ignorada a diferenca entre maiusculas e minusculas
bool ICompare(const std::string &X, const std::string &Y);

// mesmo numero de caracteres e caracteres na mesma posicao iguais se ignorados os espacos
bool WCompare(const std::string &X, const std::string &Y);

// mesmo numero de caracteres e caracteres na mesma posicao iguais se ignorada a diferenca entre maiusculas e minusculas e os espacos
bool IWCompare(const std::string &X, const std::string &Y);


/**
 * 	Apresentacao da informacao adicionada, apagada e substituida entre os dois textos.
 */
// apresenta todas as diferencas entre os textos
void standardOutput(const std::string &file1, const std::string &file2, std::vector<std::string> &X, std::vector<std::string> &Y, std::list<std::pair<int, int> > pairs);

// apenas informa se existe alguma diferenca entre os textos
void QOutput(const std::string &file1, const std::string &file2, std::vector<std::string> &X, std::vector<std::string> &Y, std::list<std::pair<int, int> > pairs);

// apresenta as diferencas entre os textos, mas ignora a adicao e remocao de linhas vazias
void BOutput(const std::string &file1, const std::string &file2, std::vector<std::string> &X, std::vector<std::string> &Y, std::list<std::pair<int, int> > pairs);

// apenas informa se existe alguma diferenca entre os textos se ignoradas a adicao e remocao de linhas vazias
void QBOutput(const std::string &file1, const std::string &file2, std::vector<std::string> &X, std::vector<std::string> &Y, std::list<std::pair<int, int> > pairs);


#endif /* LCS_H_ */
