
/*
File:		parser.cpp
Author:		Jeremy Peterson-Katz
Date:		December 14, 2017
*/

#include "../inc/parser.hpp"
#include "../inc/operand.hpp"
#include "../inc/function.hpp"
#include "../inc/pseudo_operation.hpp"
#include "../inc/operator.hpp"
#include <stack>
#include <iostream>
using namespace std;


TokenList Parser::parse(TokenList const& infixTokens) {


	// Shunting yard algorithm 

	TokenList postfixTokens;				 // output queue
	stack<Token::pointer_type> stack;		 // operation stack

	// Go through every token in the input queue
	for each (auto token in infixTokens) {
		if (is<Operand>(token)) {
			postfixTokens.push_back(token);
		}
		else if (is<Function>(token)) {
			stack.push(token);
		}
		else if (is<ArgumentSeparator>(token)) {
			while (!is<LeftParenthesis>(stack.top())) {
				postfixTokens.push_back(stack.top());
				stack.pop();
			}
		}
		else if (is<LeftParenthesis>(token)) {
			stack.push(token);
		}
		else if (is<RightParenthesis>(token)) {
			while (!is<LeftParenthesis>(stack.top())) {
				postfixTokens.push_back(stack.top());
				stack.pop();
			}
			if (stack.empty()) {
				throw exception("Right parenthesis, has no matching left parenthesis");
			}
			stack.pop();
			if (!stack.empty()) {
				if (is<Function>(stack.top())) {
					postfixTokens.push_back(stack.top());
					stack.pop();
				}
			}
		}
		else if (is<Operator>(token)) {
			while (!stack.empty()) {
				if (!is<Operator>(stack.top())) {
					break;
				}
				if (is<NonAssociative>(token)) {
					break;
				}
				if (is<LAssocOperator>(token) && 
					convert<Operator>(token)->get_precedence() > convert<Operator>(stack.top())->get_precedence()) {		 
					break;
				}
				if (is<RAssocOperator>(token) && 
					convert<Operator>(token)->get_precedence() >= convert<Operator>(stack.top())->get_precedence()) {
					break;
				}
					
				postfixTokens.push_back(stack.top());
				stack.pop();

			} // end while loop 
			stack.push(token);
		} 
		else {
			throw exception("Unknown Token");
		}
	} // end for each

	while (!stack.empty()) {
		if (is<LeftParenthesis>(stack.top())) {
			throw exception("Missing right-parenthesis");
		}
		postfixTokens.push_back(stack.top());
		stack.pop();
	}
	return postfixTokens; // return output queue
}


/*=============================================================

Revision History
Version 1.0.0: 2014-10-31
Visual C++ 2013

Version 0.0.1: 2012-11-13
C++ 11 cleanup

Version 0.0.0: 2009-12-02
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
