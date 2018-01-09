#ifndef GUARD_rpnevaluator_hpp20091210_
#define GUARD_rpnevaluator_hpp20091210_

/** @file: RPNEvaluator.hpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@version 0.0.1
	@date 2012-11-13
	@note Compiles under Visual C++ v110

	@brief RPN Evaluator class declaration.

	@implemented by Jeremy Peterson-Katz
	@date 2018-01-12
	*/

#include "operation.hpp"
#include "integer.hpp"
#include <stack>
using namespace std;



class RPNEvaluator {
public:
	Operand::pointer_type evaluate(TokenList const& container);

	Operand::pointer_type get_result(stack<Token::pointer_type> & operandStack, Token::pointer_type const& operation);
};


// Constants
constexpr int NUMBER_OF_OPERANDS = 3;
constexpr int NUMBER_OF_OPERATIONS = 39;



// Operation functions declarations
// Integer Functions
Operand::pointer_type intIdentityFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type intNegationFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type intFactorialFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type intMultiplicationFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type intDivisionFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type intAdditionFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type intSubtractionFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type intModulusFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type intPowerFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type intEqualityFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type intInequalityFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type intGreaterFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type intGreaterEqualFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type intLessFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type intLessEqualFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type intAbsoluteFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type intMaxFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type intMinFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type intAssignFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);

// Real Functions
Operand::pointer_type realIdentityFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realNegationFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realFactorialFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realMultiplicationFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realDivisionFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realAdditionFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realSubtractionFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realModulusFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realPowerFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realIntPowerFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realEqualityFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realInequalityFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realGreaterFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realGreaterEqualFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realLessFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realLessEqualFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realAbsoluteFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realArccosFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realArcsinFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realArctanFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realCeilFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realCosFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realExpFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realFloorFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realLbFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realLnFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realSinFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realSqrtFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realTanFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realMaxFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realMinFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realArctan2Func(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type realAssignFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);


// Boolean Functions
Operand::pointer_type boolNotFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type boolAndFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type boolNandFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type boolNorFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type boolOrFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type boolXorFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type boolXnorFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type boolEqualityFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type boolInequalityFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type boolGreaterFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type boolGreaterEqualFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type boolLessFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type boolLessEqualFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type boolAssignFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);

// error function 
Operand::pointer_type errorFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
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
#endif // GUARD_rpnevaluator_hpp20091210_
