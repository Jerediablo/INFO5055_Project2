/** @file: RPNEvaluator.cpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@version 0.0.1
	@date 2012-11-13
	@note Compiles under Visual C++ v110

	@brief RPN Evaluator class implementation.
	*/

#include "../inc/RPNEvaluator.hpp"
#include <stack>
using namespace std;

Operand::pointer_type RPNEvaluator::evaluate(TokenList const& rpnExpression) {

	stack<Token::pointer_type> operandStack;		 // operand stack

	for each (auto token in rpnExpression) {
		if (is<Operand>(token)) {
			operandStack.push(token);
		}
		else if (is<Operation>(token)) {
			if (convert<Operation>(token)->number_of_args() > operandStack.size()) {
				throw exception("Insufficient # of operands for operation");
			}

			// DO STUFF HERE :X 
		}
	}
	
	if (operandStack.size() > 1) {
		throw exception("Error: too many operands");
	}

	if (operandStack.size() == 0) {
		throw exception("Error: insufficient operands");
	}

	Operand::pointer_type answer = convert<Operand>(operandStack.top());
	operandStack.pop();

	return answer; 
}

/*=============================================================

Revision History

Version 0.0.1: 2012-11-13
C++ 11 cleanup

Version 0.0.0: 2009-12-10
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
