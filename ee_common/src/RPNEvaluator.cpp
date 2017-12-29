/** @file: RPNEvaluator.cpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@version 0.0.1
	@date 2012-11-13
	@note Compiles under Visual C++ v110

	@brief RPN Evaluator class implementation.
	*/

#include "../inc/RPNEvaluator.hpp"

#include "../inc/tokenizer.hpp"
#include "../inc/boolean.hpp"
#include "../inc/function.hpp"
#include "../inc/integer.hpp"
#include "../inc/operator.hpp"
#include "../inc/pseudo_operation.hpp"
#include "../inc/real.hpp"
#include "../inc/variable.hpp"

#include <stack>
#include <cmath>
using namespace std;

// function declaration
Operand::pointer_type get_result(stack<Token::pointer_type> & operandStack, Token::pointer_type const& operation);

using FunctionPointer = Operand::pointer_type(*)(Integer::value_type, Integer::value_type);

// Operation functions
Operand::pointer_type identityFunc(Integer::value_type intOperand1, Integer::value_type intOperand2) { return convert<Operand>(make<Integer>(intOperand1)); }

Operand::pointer_type negationFunc(Integer::value_type intOperand1, Integer::value_type intOperand2) { return convert<Operand>(make<Integer>(intOperand1 * -1)); }

Operand::pointer_type factorialFunc(Integer::value_type intOperand1, Integer::value_type intOperand2) {
	Integer::value_type ans = 1;
	while (intOperand1 > 1) {
		ans *= intOperand1;
		intOperand1--;
	}
	return convert<Operand>(make<Integer>(ans)); 
}

Operand::pointer_type multiplicationFunc(Integer::value_type intOperand1, Integer::value_type intOperand2) { return convert<Operand>(make<Integer>(intOperand1 * intOperand2)); }

Operand::pointer_type divisionFunc(Integer::value_type intOperand1, Integer::value_type intOperand2) { return convert<Operand>(make<Integer>(intOperand1 / intOperand2)); }

Operand::pointer_type additionFunc(Integer::value_type intOperand1, Integer::value_type intOperand2) { return convert<Operand>(make<Integer>(intOperand1 + intOperand2)); }

Operand::pointer_type subtractionFunc(Integer::value_type intOperand1, Integer::value_type intOperand2) { return convert<Operand>(make<Integer>(intOperand1 - intOperand2)); }

Operand::pointer_type modulusFunc(Integer::value_type intOperand1, Integer::value_type intOperand2) { return convert<Operand>(make<Integer>(intOperand1 % intOperand2)); }

Operand::pointer_type powerFunc(Integer::value_type intOperand1, Integer::value_type intOperand2) { 
	Integer::value_type ans = intOperand1;
	while (intOperand2 > 1) {
		ans *= intOperand1;
		intOperand2--;
	}

	return convert<Operand>(make<Integer>(ans)); 
}


Operand::pointer_type RPNEvaluator::evaluate(TokenList const& rpnExpression) {

	stack<Token::pointer_type> operandStack;		 // operand stack
	stack<Token::pointer_type> calcStack;
	int argCounter = 0;

	for each (auto token in rpnExpression) {
		if (is<Operand>(token)) {
			operandStack.push(token);
		}
		else if (is<Operation>(token)) {
			Token::pointer_type operation = token;
			if (convert<Operation>(operation)->number_of_args() > operandStack.size()) {
				throw exception("Insufficient # of operands for operation");
			}

			argCounter = convert<Operation>(operation)->number_of_args();
			while (argCounter > 0) {
				calcStack.push(convert<Operand>(operandStack.top()));
				operandStack.pop();
				argCounter--;
			}
			
			// lookup table to find result
			Operand::pointer_type result = get_result(calcStack, operation);
			return result;
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

Operand::pointer_type get_result(stack<Token::pointer_type> & operandStack, Token::pointer_type const& operation) {

	// LOOKUP TABLE CODE

	// 3d array ?? 
	// 1 - first operand 
	// 2 - second operand (if applicable, if not, set to some value (0)??)
	// 3 - operation

	int x = 0;
	int y = 0;
	int z = 0;

	Integer::value_type intOperand1;
	Real::value_type realOperand1;

	Integer::value_type intOperand2;
	Real::value_type realOperand2;

	if (is<Integer>(operandStack.top())) {
		x = 0;
		intOperand1 = (convert<Integer>(operandStack.top()))->get_value();
	}
	else if (is<Real>(operandStack.top())) {
		x = 1;
		realOperand1 = (convert<Real>(operandStack.top()))->get_value();
	}

	operandStack.pop();
	if (operandStack.size() == 0) {
		y = 0;
	}
	else if (is<Integer>(operandStack.top())) {
		x = 0;
		intOperand2 = (convert<Integer>(operandStack.top()))->get_value();
	}
	else if (is<Real>(operandStack.top())) {
		x = 1;
		realOperand2 = (convert<Real>(operandStack.top()))->get_value();
	}

	if (is<Identity>(operation)) {
		z = 0;
	}
	else if (is<Negation>(operation)) {
		z = 1;
	}
	else if (is<Factorial>(operation)) {
		z = 2;
	}
	else if (is<Multiplication>(operation)) {
		z = 3;
	}
	else if (is<Division>(operation)) {
		z = 4;
	}
	else if (is<Addition>(operation)) {
		z = 5;
	}
	else if (is<Subtraction>(operation)) {
		z = 6;
	}
	else if (is<Modulus>(operation)) {
		z = 7;
	}
	else if (is<Power>(operation)) {
		z = 8;
	}

	
	FunctionPointer lookupTable[2][2][9] =
	{
		/*x = 0*/{
			/*y = 0*/{
				/*z = 0*/identityFunc,
				/*z = 1*/negationFunc,
				/*z = 2*/factorialFunc,
				/*z = 3*/multiplicationFunc,
				/*z = 4*/divisionFunc,
				/*z = 5*/additionFunc,
				/*z = 6*/subtractionFunc,
				/*z = 7*/modulusFunc,
				/*z = 8*/powerFunc },
			/*y = 1*/{ /*Binary Operators Here*/ } },
		/*x = 1*/{
			/*y = 0*/{
				/*z = 0*/ /*Put REAL identityFunc here ,*/
				/*z = 1*/ /*Put REAL negationFunc here ,*/
				/*z = 2*/ /*No Factorial for Real Numbers*/ },
			/*y = 1*/{ /*Binary Operators Here*/ } }
	};

	return lookupTable[x][y][z](intOperand1, intOperand2);
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
