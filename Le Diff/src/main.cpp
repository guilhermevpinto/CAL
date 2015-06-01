/*
 * main.cpp
 *
 *  Created on: 25/05/2015
 *      Author: Guilherme
 */

#include <iostream>
#include <cstdlib>

#include "Diff.h"

using namespace std;

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


	diff(file1, file2, compare, output);
	return 0;
}



