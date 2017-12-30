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

using FunctionPointer = Operand::pointer_type(*)(Operand::pointer_type, Operand::pointer_type);

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


	// Boolean Functions
Operand::pointer_type boolNotFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type boolAndFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type boolNandFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type boolNorFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type boolOrFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type boolXorFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type boolEqualityFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type boolInequalityFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type boolGreaterFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type boolGreaterEqualFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type boolLessFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type boolLessEqualFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);


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

	int x = 0;	// first operand
	int y = 0;	// second operand
	int z = 0;	// operation

	Operand::pointer_type operand1 = convert<Operand>(operandStack.top());
	Operand::pointer_type operand2;

	if (is<Integer>(operandStack.top())) {
		x = 0;
	}
	else if (is<Real>(operandStack.top())) {
		x = 1;
	}
	else if (is<Boolean>(operandStack.top())) {
		x = 2;
	}

	operandStack.pop();

	if (operandStack.size() != 0) {
		operand2 = convert<Operand>(operandStack.top());
		if (is<Integer>(operandStack.top())) {
			y = 0;
		}
		else if (is<Real>(operandStack.top())) {
			y = 1;
		}
		else if (is<Boolean>(operandStack.top())) {
			y = 2;
		}
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
	else if (is<Not>(operation)) {
		z = 9;
	}
	else if (is<And>(operation)) {
		z = 10;
	}
	else if (is<Nand>(operation)) {
		z = 11;
	}
	else if (is<Nor>(operation)) {
		z = 12;
	}
	else if (is<Or>(operation)) {
		z = 13;
	}
	else if (is<Xor>(operation)) {
		z = 14;
	}
	else if (is<Equality>(operation)) {
		z = 15;
	}
	else if (is<Inequality>(operation)) {
		z = 16;
	}
	else if (is<Greater>(operation)) {
		z = 17;
	}
	else if (is<GreaterEqual>(operation)) {
		z = 18;
	}
	else if (is<Less>(operation)) {
		z = 19;
	}
	else if (is<LessEqual>(operation)) {
		z = 20;
	}
	else if (is<Abs>(operation)) {
		z = 21;
	}
	else if (is<Arccos>(operation)) {
		z = 22;
	}
	else if (is<Arcsin>(operation)) {
		z = 23;
	}
	else if (is<Arctan>(operation)) {
		z = 24;
	}
	else if (is<Ceil>(operation)) {
		z = 25;
	}
	else if (is<Cos>(operation)) {
		z = 26;
	}
	else if (is<Exp>(operation)) {
		z = 27;
	}
	else if (is<Floor>(operation)) {
		z = 28;
	}
	else if (is<Lb>(operation)) {
		z = 29;
	}
	else if (is<Ln>(operation)) {
		z = 30;
	}
	else if (is<Sin>(operation)) {
		z = 31;
	}
	else if (is<Sqrt>(operation)) {
		z = 32;
	}
	else if (is<Tan>(operation)) {
		z = 33;
	}


	
	FunctionPointer lookupTable[3][3][34] =
	{
		/*Operand 1 is Int*/{
			/*Operand 2 is Int (or nothing)*/{
				/*z = 0*/	intIdentityFunc,
				/*z = 1*/	intNegationFunc,
				/*z = 2*/	intFactorialFunc,
				/*z = 3*/	intMultiplicationFunc,
				/*z = 4*/	intDivisionFunc,
				/*z = 5*/	intAdditionFunc,
				/*z = 6*/	intSubtractionFunc,
				/*z = 7*/	intModulusFunc,
				/*z = 8*/	intPowerFunc,
				/*z = 9*/	boolNotFunc,
				/*z = 10*/	boolAndFunc,
				/*z = 11*/	boolNandFunc,
				/*z = 12*/	boolNorFunc,
				/*z = 13*/	boolOrFunc,
				/*z = 14*/	boolXorFunc,
				/*z = 15*/	intEqualityFunc,
				/*z = 16*/	intInequalityFunc,
				/*z = 17*/	intGreaterFunc,
				/*z = 18*/	intGreaterEqualFunc,
				/*z = 19*/	intLessFunc,
				/*z = 20*/	intLessEqualFunc,
				/*z = 21*/	intAbsoluteFunc },
			/*Operand 2 is Real*/{  },
			/*Operand 2 is Bool*/{  }
		},
		/*Operand 1 is Real*/{
			/*Operand 2 is Int (or nothing)*/{
				/*z = 0*/	realIdentityFunc,
				/*z = 1*/	realNegationFunc,
				/*z = 2*/	realFactorialFunc,
				/*z = 3*/	realMultiplicationFunc,
				/*z = 4*/	realDivisionFunc,
				/*z = 5*/	realAdditionFunc,
				/*z = 6*/	realSubtractionFunc,
				/*z = 7*/	realModulusFunc,
				/*z = 8*/	realPowerFunc,
				/*z = 9*/	boolNotFunc,
				/*z = 10*/	boolAndFunc,
				/*z = 11*/	boolNandFunc,
				/*z = 12*/	boolNorFunc,
				/*z = 13*/	boolOrFunc,
				/*z = 14*/	boolXorFunc,
				/*z = 15*/	realEqualityFunc,
				/*z = 16*/	realInequalityFunc,
				/*z = 17*/	realGreaterFunc,
				/*z = 18*/	realGreaterEqualFunc,
				/*z = 19*/	realLessFunc,
				/*z = 20*/	realLessEqualFunc,
				/*z = 21*/	realAbsoluteFunc, 
				/*z = 22*/	realArccosFunc, 
				/*z = 23*/	realArcsinFunc, 
				/*z = 24*/	realArctanFunc, 
				/*z = 25*/	realCeilFunc,
				/*z = 26*/	realCosFunc,
				/*z = 27*/	realExpFunc,
				/*z = 28*/	realFloorFunc,
				/*z = 29*/	realLbFunc,
				/*z = 30*/	realLnFunc,
				/*z = 31*/	realSinFunc,
				/*z = 32*/	realSqrtFunc,
				/*z = 33*/	realTanFunc },
			/*Operand 2 is Real*/{ 
				/*z = 0*/	realIdentityFunc,
				/*z = 1*/	realNegationFunc,
				/*z = 2*/	realFactorialFunc,
				/*z = 3*/	realMultiplicationFunc,
				/*z = 4*/	realDivisionFunc,
				/*z = 5*/	realAdditionFunc,
				/*z = 6*/	realSubtractionFunc,
				/*z = 7*/	realModulusFunc,
				/*z = 8*/	realPowerFunc,
				/*z = 9*/	boolNotFunc,
				/*z = 10*/	boolAndFunc,
				/*z = 11*/	boolNandFunc,
				/*z = 12*/	boolNorFunc,
				/*z = 13*/	boolOrFunc,
				/*z = 14*/	boolXorFunc,
				/*z = 15*/	realEqualityFunc,
				/*z = 16*/	realInequalityFunc,
				/*z = 17*/	realGreaterFunc,
				/*z = 18*/	realGreaterEqualFunc,
				/*z = 19*/	realLessFunc,
				/*z = 20*/	realLessEqualFunc },
			/*Operand 2 is Bool*/{}
		},
		/*Operand 1 is Bool*/{
			/*Operand 2 is Int*/{
				/*z = 0*/	intIdentityFunc,
				/*z = 1*/	intNegationFunc,
				/*z = 2*/	intFactorialFunc,
				/*z = 3*/	intMultiplicationFunc,
				/*z = 4*/	intDivisionFunc,
				/*z = 5*/	intAdditionFunc,
				/*z = 6*/	intSubtractionFunc,
				/*z = 7*/	intModulusFunc,
				/*z = 8*/	intPowerFunc,
				/*z = 9*/	boolNotFunc },
			/*Operand 2 is Real*/{},
			/*Operand 2 is Bool*/{
				/*z = 0*/	intIdentityFunc,
				/*z = 1*/	intNegationFunc,
				/*z = 2*/	intFactorialFunc,
				/*z = 3*/	intMultiplicationFunc,
				/*z = 4*/	intDivisionFunc,
				/*z = 5*/	intAdditionFunc,
				/*z = 6*/	intSubtractionFunc,
				/*z = 7*/	intModulusFunc,
				/*z = 8*/	intPowerFunc,
				/*z = 9*/	boolNotFunc,
				/*z = 10*/	boolAndFunc,
				/*z = 11*/	boolNandFunc,
				/*z = 12*/	boolNorFunc,
				/*z = 13*/	boolOrFunc,
				/*z = 14*/	boolXorFunc, 
				/*z = 15*/	boolEqualityFunc,
				/*z = 16*/	boolInequalityFunc,
				/*z = 17*/	boolGreaterFunc,
				/*z = 18*/	boolGreaterEqualFunc,
				/*z = 19*/	boolLessFunc,
				/*z = 20*/	boolLessEqualFunc}
		}
	};

	return lookupTable[x][y][z](operand1, operand2);
}

// Operation function definitions
//Integer Functions
Operand::pointer_type intIdentityFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Integer>((convert<Integer>(operand1)->get_value())));
}

Operand::pointer_type intNegationFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Integer>((convert<Integer>(operand1)->get_value()) * -1));
}

Operand::pointer_type intFactorialFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Integer::value_type ans = 1;
	Integer::value_type count = (convert<Integer>(operand1)->get_value());
	while (count > 1) {
		ans *= count;
		count--;
	}
	return convert<Operand>(make<Integer>(ans));
}

Operand::pointer_type intMultiplicationFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Integer>((convert<Integer>(operand1)->get_value()) * (convert<Integer>(operand2)->get_value())));
}

Operand::pointer_type intDivisionFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Integer>((convert<Integer>(operand1)->get_value()) / (convert<Integer>(operand2)->get_value())));
}

Operand::pointer_type intAdditionFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Integer>((convert<Integer>(operand1)->get_value()) + (convert<Integer>(operand2)->get_value())));
}

Operand::pointer_type intSubtractionFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Integer>((convert<Integer>(operand1)->get_value()) - (convert<Integer>(operand2)->get_value())));
}

Operand::pointer_type intModulusFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Integer>((convert<Integer>(operand1)->get_value()) % (convert<Integer>(operand2)->get_value())));
}

Operand::pointer_type intPowerFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Integer::value_type ans = (convert<Integer>(operand1)->get_value());
	Integer::value_type initVal = (convert<Integer>(operand1)->get_value());
	Integer::value_type count = (convert<Integer>(operand2)->get_value());
	while (count > 1) {
		ans *= initVal;
		count--;
	}
	return convert<Operand>(make<Integer>(ans));
}

Operand::pointer_type intEqualityFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Integer::value_type op1 = convert<Integer>(operand1)->get_value();
	Integer::value_type op2 = convert<Integer>(operand2)->get_value();
		
	if (op1 == op2) {
		return convert<Operand>(make<Boolean>(true));
	}
	else {
		return convert<Operand>(make<Boolean>(false));
	}
}

Operand::pointer_type intInequalityFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Integer::value_type op1 = convert<Integer>(operand1)->get_value();
	Integer::value_type op2 = convert<Integer>(operand2)->get_value();

	if (op1 != op2) {
		return convert<Operand>(make<Boolean>(true));
	}
	else {
		return convert<Operand>(make<Boolean>(false));
	}
}
Operand::pointer_type intGreaterFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Integer::value_type op1 = convert<Integer>(operand1)->get_value();
	Integer::value_type op2 = convert<Integer>(operand2)->get_value();

	if (op1 > op2) {
		return convert<Operand>(make<Boolean>(true));
	}
	else {
		return convert<Operand>(make<Boolean>(false));
	}
}

Operand::pointer_type intGreaterEqualFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Integer::value_type op1 = convert<Integer>(operand1)->get_value();
	Integer::value_type op2 = convert<Integer>(operand2)->get_value();

	if (op1 >= op2) {
		return convert<Operand>(make<Boolean>(true));
	}
	else {
		return convert<Operand>(make<Boolean>(false));
	}
}

Operand::pointer_type intLessFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Integer::value_type op1 = convert<Integer>(operand1)->get_value();
	Integer::value_type op2 = convert<Integer>(operand2)->get_value();

	if (op1 < op2) {
		return convert<Operand>(make<Boolean>(true));
	}
	else {
		return convert<Operand>(make<Boolean>(false));
	}
}

Operand::pointer_type intLessEqualFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Integer::value_type op1 = convert<Integer>(operand1)->get_value();
	Integer::value_type op2 = convert<Integer>(operand2)->get_value();

	if (op1 <= op2) {
		return convert<Operand>(make<Boolean>(true));
	}
	else {
		return convert<Operand>(make<Boolean>(false));
	}
}

Operand::pointer_type intAbsoluteFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Integer::value_type op1 = convert<Integer>(operand1)->get_value();
	if (op1 > 0)
		return convert<Operand>(make<Integer>((convert<Integer>(operand1)->get_value())));
	else
		return convert<Operand>(make<Integer>((convert<Integer>(operand1)->get_value()) * -1));
}

// Real Functions
Operand::pointer_type realIdentityFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Real>((convert<Real>(operand1)->get_value())));
}

Operand::pointer_type realNegationFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Real>((convert<Real>(operand1)->get_value()) * -1));
}

Operand::pointer_type realFactorialFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	throw "Error: Cannot perform: <Factorial>";
}

Operand::pointer_type realMultiplicationFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Real>((convert<Real>(operand1)->get_value()) * (convert<Real>(operand2)->get_value())));
}

Operand::pointer_type realDivisionFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Real>((convert<Real>(operand1)->get_value()) / (convert<Real>(operand2)->get_value())));
}

Operand::pointer_type realAdditionFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Real>((convert<Real>(operand1)->get_value()) + (convert<Real>(operand2)->get_value())));
}

Operand::pointer_type realSubtractionFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Real>((convert<Real>(operand1)->get_value()) - (convert<Real>(operand2)->get_value())));
}

Operand::pointer_type realModulusFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	throw "Error: Cannot perform: <Modulus>";
}

Operand::pointer_type realPowerFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Real::value_type ans = (convert<Real>(operand1)->get_value());
	Real::value_type initVal = (convert<Real>(operand1)->get_value());
	Real::value_type count = (convert<Real>(operand2)->get_value());
	while (count > 1) {
		ans *= initVal;
		count--;
	}
	return convert<Operand>(make<Real>(ans));
}

Operand::pointer_type realEqualityFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Real::value_type op1 = convert<Real>(operand1)->get_value();
	Real::value_type op2 = convert<Real>(operand2)->get_value();

	if (op1 == op2) 
		return convert<Operand>(make<Boolean>(true));
	else 
		return convert<Operand>(make<Boolean>(false));
}

Operand::pointer_type realInequalityFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Real::value_type op1 = convert<Real>(operand1)->get_value();
	Real::value_type op2 = convert<Real>(operand2)->get_value();

	if (op1 != op2)
		return convert<Operand>(make<Boolean>(true));
	else
		return convert<Operand>(make<Boolean>(false));
}

Operand::pointer_type realGreaterFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Real::value_type op1 = convert<Real>(operand1)->get_value();
	Real::value_type op2 = convert<Real>(operand2)->get_value();

	if (op1 > op2)
		return convert<Operand>(make<Boolean>(true));
	else
		return convert<Operand>(make<Boolean>(false));
}

Operand::pointer_type realGreaterEqualFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Real::value_type op1 = convert<Real>(operand1)->get_value();
	Real::value_type op2 = convert<Real>(operand2)->get_value();

	if (op1 >= op2)
		return convert<Operand>(make<Boolean>(true));
	else
		return convert<Operand>(make<Boolean>(false));
}

Operand::pointer_type realLessFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Real::value_type op1 = convert<Real>(operand1)->get_value();
	Real::value_type op2 = convert<Real>(operand2)->get_value();

	if (op1 < op2)
		return convert<Operand>(make<Boolean>(true));
	else
		return convert<Operand>(make<Boolean>(false));
}

Operand::pointer_type realLessEqualFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Real::value_type op1 = convert<Real>(operand1)->get_value();
	Real::value_type op2 = convert<Real>(operand2)->get_value();

	if (op1 <= op2)
		return convert<Operand>(make<Boolean>(true));
	else
		return convert<Operand>(make<Boolean>(false));
}

Operand::pointer_type realAbsoluteFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Real::value_type op1 = convert<Real>(operand1)->get_value();
	if (op1 > 0)
		return convert<Operand>(make<Real>((convert<Real>(operand1)->get_value())));
	else
		return convert<Operand>(make<Real>((convert<Real>(operand1)->get_value()) * -1));
}

Operand::pointer_type realArccosFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Real>(acos(convert<Real>(operand1)->get_value())));
}
Operand::pointer_type realArcsinFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Real>(asin(convert<Real>(operand1)->get_value())));
}
Operand::pointer_type realArctanFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Real>(atan(convert<Real>(operand1)->get_value())));
}
Operand::pointer_type realCeilFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Real>(ceil(convert<Real>(operand1)->get_value())));
}
Operand::pointer_type realCosFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Real>(cos(convert<Real>(operand1)->get_value())));
}
Operand::pointer_type realExpFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Real>(exp(convert<Real>(operand1)->get_value())));
}
Operand::pointer_type realFloorFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Real>(floor(convert<Real>(operand1)->get_value())));
}
Operand::pointer_type realLbFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Real>(log2(convert<Real>(operand1)->get_value())));
}
Operand::pointer_type realLnFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Real>(log(convert<Real>(operand1)->get_value())));
}
Operand::pointer_type realSinFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Real>(sin(convert<Real>(operand1)->get_value())));
}
Operand::pointer_type realSqrtFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Real>(sqrt(convert<Real>(operand1)->get_value())));
}
Operand::pointer_type realTanFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Real>(tan(convert<Real>(operand1)->get_value())));
}

// Boolean Functions
Operand::pointer_type boolNotFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Boolean>(!(convert<Boolean>(operand1)->get_value())));
}

Operand::pointer_type boolAndFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Boolean::value_type op1;
	Boolean::value_type op2;
	
	(is<True>(operand1)) ? op1 = true : op1 = false;
	(is<True>(operand2)) ? op2 = true : op2 = false;

	
	if (op1 == true && op2 == true) {
		return convert<Operand>(make<Boolean>(true));
	}
	else {
		return convert<Operand>(make<Boolean>(false));
	}
}

Operand::pointer_type boolNandFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Boolean::value_type op1;
	Boolean::value_type op2;

	(is<True>(operand1)) ? op1 = true : op1 = false;
	(is<True>(operand2)) ? op2 = true : op2 = false;

	if (op1 == true && op2 == true)
		return convert<Operand>(make<Boolean>(false));
	else
		return convert<Operand>(make<Boolean>(true));
}

Operand::pointer_type boolNorFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Boolean::value_type op1;
	Boolean::value_type op2;

	(is<True>(operand1)) ? op1 = true : op1 = false;
	(is<True>(operand2)) ? op2 = true : op2 = false;

	if (op1 == false && op2 == false)
		return convert<Operand>(make<Boolean>(true));
	else
		return convert<Operand>(make<Boolean>(false));
}

Operand::pointer_type boolOrFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Boolean::value_type op1;
	Boolean::value_type op2;

	(is<True>(operand1)) ? op1 = true : op1 = false;
	(is<True>(operand2)) ? op2 = true : op2 = false;

	if (op1 == true || op2 == true)
		return convert<Operand>(make<Boolean>(true));
	else
		return convert<Operand>(make<Boolean>(false));
}

Operand::pointer_type boolXorFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Boolean::value_type op1;
	Boolean::value_type op2;

	(is<True>(operand1)) ? op1 = true : op1 = false;
	(is<True>(operand2)) ? op2 = true : op2 = false;

	if ((op1 == true || op2 == true) && (op1 != op2))
		return convert<Operand>(make<Boolean>(true));
	else
		return convert<Operand>(make<Boolean>(false));
}

Operand::pointer_type boolEqualityFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Boolean::value_type op1;
	Boolean::value_type op2;

	(is<True>(operand1)) ? op1 = true : op1 = false;
	(is<True>(operand2)) ? op2 = true : op2 = false;

	if (op1 == op2)
		return convert<Operand>(make<Boolean>(true));
	else
		return convert<Operand>(make<Boolean>(false));
}

Operand::pointer_type boolInequalityFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Boolean::value_type op1;
	Boolean::value_type op2;

	(is<True>(operand1)) ? op1 = true : op1 = false;
	(is<True>(operand2)) ? op2 = true : op2 = false;

	if (op1 != op2)
		return convert<Operand>(make<Boolean>(true));
	else
		return convert<Operand>(make<Boolean>(false));
}

Operand::pointer_type boolGreaterFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Boolean::value_type op1;
	Boolean::value_type op2;

	(is<True>(operand1)) ? op1 = true : op1 = false;
	(is<True>(operand2)) ? op2 = true : op2 = false;

	if (op1 > op2)
		return convert<Operand>(make<Boolean>(true));
	else
		return convert<Operand>(make<Boolean>(false));
}

Operand::pointer_type boolGreaterEqualFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Boolean::value_type op1;
	Boolean::value_type op2;

	(is<True>(operand1)) ? op1 = true : op1 = false;
	(is<True>(operand2)) ? op2 = true : op2 = false;

	if (op1 >= op2)
		return convert<Operand>(make<Boolean>(true));
	else
		return convert<Operand>(make<Boolean>(false));
}

Operand::pointer_type boolLessFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Boolean::value_type op1;
	Boolean::value_type op2;

	(is<True>(operand1)) ? op1 = true : op1 = false;
	(is<True>(operand2)) ? op2 = true : op2 = false;

	if (op1 < op2)
		return convert<Operand>(make<Boolean>(true));
	else
		return convert<Operand>(make<Boolean>(false));
}

Operand::pointer_type boolLessEqualFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Boolean::value_type op1;
	Boolean::value_type op2;

	(is<True>(operand1)) ? op1 = true : op1 = false;
	(is<True>(operand2)) ? op2 = true : op2 = false;

	if (op1 <= op2)
		return convert<Operand>(make<Boolean>(true));
	else
		return convert<Operand>(make<Boolean>(false));
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
