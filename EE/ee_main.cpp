/** @file: ee_main.cpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@date 2017-11-23
	@version 1.1.0
	@note Compiles under Visual C++ 15.4.4

	@brief Expression Evaluator application.
	*/

#include "../ee_common/inc/expression_evaluator.hpp"

#include <iostream>
#include <string>
using namespace std;



int main() {
	cout << "Expression Evaluator, (c) 1998-2017 Garth Santor\n";

	for (unsigned count = 0; ; ++count) {
		cout << "> ";
		string command;
		if (!getline(cin, command) || command.empty())
			break;

		cout << "[" << count << "] = " << 42 << endl;
	}
}

/*=============================================================

Revision History

Version 1.1.0: 2017-11-23
Added Python-style power operator '**'

Version 1.0.0: 2016-10-29
Added help command.

Version 0.1.0: 2014-11-27
Added: setp to set the real number precision.

Version 0.0.1: 2012-11-13
C++ 11 cleanup

Version 0.0.0: 2010-11-23
Alpha release.

=============================================================

Copyright Garth Santor/Trinh Han

The copyright to the computer program(s) herein
is the property of Garth Santor/Trinh Han of Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor/Trinh Han
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
=============================================================*/
