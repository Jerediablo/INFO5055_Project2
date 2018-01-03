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
Operand::pointer_type intMaxFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);
Operand::pointer_type intMinFunc(Operand::pointer_type operand1, Operand::pointer_type operand2);


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
			operandStack.push(result);
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

	// These get passed as the parameters for the functions in the lookup table
	Operand::pointer_type operand1 = convert<Operand>(operandStack.top());
	Operand::pointer_type operand2;

	// Determine the type of the first operand, and use it as the first index in the lookup table
	x = convert<Operand>(operandStack.top())->operandIndex();

	// Remove the first operand from the operand stack
	operandStack.pop();

	// If there is still something in the operand stack, it means the operation takes a second operand
	if (operandStack.size() != 0) {

		// Determine the type of the second operand, and use it as the second index in the lookup table
		operand2 = convert<Operand>(operandStack.top());
		y = operand2->operandIndex();
	}

	// Determine the type of the operatino, and use it as the third index in the lookup table
	z = convert<Operation>(operation)->operationIndex();

	// Lookup Table
	FunctionPointer lookupTable[NUMBER_OF_OPERANDS][NUMBER_OF_OPERANDS][NUMBER_OF_OPERATIONS] =
	{
		/* x = 0 Operand 1 is Int*/{
			/* y = 0 Operand 2 is Int (or nothing)*/{
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
				/*z = 21*/	intAbsoluteFunc,
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
				/*z = 33*/	realTanFunc, 
				/*z = 34*/	intMaxFunc, 
				/*z = 35*/	intMinFunc, },
			/* y = 1 Operand 2 is Real*/{  },
			/* y = 2 Operand 2 is Bool*/{  }
		},
		/* x = 1 Operand 1 is Real*/{
			/* y = 0 Operand 2 is Int (or nothing)*/{
				/*z = 0*/	realIdentityFunc,
				/*z = 1*/	realNegationFunc,
				/*z = 2*/	realFactorialFunc,
				/*z = 3*/	realMultiplicationFunc,
				/*z = 4*/	realDivisionFunc,
				/*z = 5*/	realAdditionFunc,
				/*z = 6*/	realSubtractionFunc,
				/*z = 7*/	realModulusFunc,
				/*z = 8*/	realIntPowerFunc,
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
			/* y = 1 Operand 2 is Real*/{ 
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
				/*z = 21*/	intAbsoluteFunc,
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
				/*z = 33*/	realTanFunc,
				/*z = 34*/	realMaxFunc,
				/*z = 35*/	realMinFunc, 
				/*z = 36*/	realArctan2Func },
			/* y= 2 Operand 2 is Bool*/{}
		},
		/* x = 2 Operand 1 is Bool*/{
			/* y = 0 Operand 2 is Int*/{
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
			/*y = 1 Operand 2 is Real*/{},
			/*y = 2 Operand 2 is Bool*/{
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
				/*z = 20*/	boolLessEqualFunc,
				/*z = 21*/	intAbsoluteFunc,
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
				/*z = 33*/	realTanFunc,
				/*z = 34*/	realMaxFunc,
				/*z = 35*/	realMinFunc,
				/*z = 36*/	realArctan2Func,
				/*z = 37*/	boolXnorFunc }
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


Operand::pointer_type intMaxFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Integer>(max((convert<Integer>(operand1)->get_value()), (convert<Integer>(operand2)->get_value()))));
}
Operand::pointer_type intMinFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Integer>(min((convert<Integer>(operand1)->get_value()), (convert<Integer>(operand2)->get_value()))));
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

	return convert<Operand>(make<Real>(pow((convert<Real>(operand1)->get_value()), (convert<Real>(operand2)->get_value()))));
}

Operand::pointer_type realIntPowerFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Real::value_type ans = (convert<Real>(operand1)->get_value());
	Real::value_type initVal = (convert<Real>(operand1)->get_value());
	Integer::value_type count = (convert<Integer>(operand2)->get_value());
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

Operand::pointer_type realMaxFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Real>(max((convert<Real>(operand1)->get_value()), (convert<Real>(operand2)->get_value()))));
}
Operand::pointer_type realMinFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Real>(min((convert<Real>(operand1)->get_value()), (convert<Real>(operand2)->get_value()))));
}

Operand::pointer_type realArctan2Func(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Real>(atan2((convert<Real>(operand1)->get_value()), (convert<Real>(operand2)->get_value()))));
}

// Boolean Functions
Operand::pointer_type boolNotFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	return convert<Operand>(make<Boolean>(!(convert<Boolean>(operand1)->get_value())));
}

Operand::pointer_type boolAndFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Boolean::value_type op1;
	Boolean::value_type op2;

	op1 = convert<Boolean>(operand1)->get_value();
	op2 = convert<Boolean>(operand2)->get_value();

	if (is<True>(operand1))
		op1 = true;
	else if (is<False>(operand1))
		op1 = false;

	if (is<True>(operand2))
		op2= true;
	else if (is<False>(operand2))
		op2 = false;


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

	op1 = convert<Boolean>(operand1)->get_value();
	op2 = convert<Boolean>(operand2)->get_value();

	if (is<True>(operand1))
		op1 = true;
	else if (is<False>(operand1))
		op1 = false;

	if (is<True>(operand2))
		op2 = true;
	else if (is<False>(operand2))
		op2 = false;

	if (op1 == true && op2 == true)
		return convert<Operand>(make<Boolean>(false));
	else
		return convert<Operand>(make<Boolean>(true));
}

Operand::pointer_type boolNorFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Boolean::value_type op1;
	Boolean::value_type op2;

	op1 = convert<Boolean>(operand1)->get_value();
	op2 = convert<Boolean>(operand2)->get_value();

	if (is<True>(operand1))
		op1 = true;
	else if (is<False>(operand1))
		op1 = false;

	if (is<True>(operand2))
		op2 = true;
	else if (is<False>(operand2))
		op2 = false;

	if (op1 == false && op2 == false)
		return convert<Operand>(make<Boolean>(true));
	else
		return convert<Operand>(make<Boolean>(false));
}

Operand::pointer_type boolXnorFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Boolean::value_type op1;
	Boolean::value_type op2;

	op1 = convert<Boolean>(operand1)->get_value();
	op2 = convert<Boolean>(operand2)->get_value();

	if (is<True>(operand1))
		op1 = true;
	else if (is<False>(operand1))
		op1 = false;

	if (is<True>(operand2))
		op2 = true;
	else if (is<False>(operand2))
		op2 = false;

	if ((op1 == false && op2 == false) || (op1 == true && op2 == true))
		return convert<Operand>(make<Boolean>(true));
	else
		return convert<Operand>(make<Boolean>(false));
}

Operand::pointer_type boolOrFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Boolean::value_type op1;
	Boolean::value_type op2;

	op1 = convert<Boolean>(operand1)->get_value();
	op2 = convert<Boolean>(operand2)->get_value();

	if (is<True>(operand1))
		op1 = true;
	else if (is<False>(operand1))
		op1 = false;

	if (is<True>(operand2))
		op2 = true;
	else if (is<False>(operand2))
		op2 = false;

	if (op1 == true || op2 == true)
		return convert<Operand>(make<Boolean>(true));
	else
		return convert<Operand>(make<Boolean>(false));
}

Operand::pointer_type boolXorFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Boolean::value_type op1;
	Boolean::value_type op2;

	op1 = convert<Boolean>(operand1)->get_value();
	op2 = convert<Boolean>(operand2)->get_value();

	if (is<True>(operand1))
		op1 = true;
	else if (is<False>(operand1))
		op1 = false;

	if (is<True>(operand2))
		op2 = true;
	else if (is<False>(operand2))
		op2 = false;

	if ((op1 == true || op2 == true) && (op1 != op2))
		return convert<Operand>(make<Boolean>(true));
	else
		return convert<Operand>(make<Boolean>(false));
}

Operand::pointer_type boolEqualityFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Boolean::value_type op1;
	Boolean::value_type op2;

	op1 = convert<Boolean>(operand1)->get_value();
	op2 = convert<Boolean>(operand2)->get_value();

	if (is<True>(operand1))
		op1 = true;
	else if (is<False>(operand1))
		op1 = false;

	if (is<True>(operand2))
		op2 = true;
	else if (is<False>(operand2))
		op2 = false;

	if (op1 == op2)
		return convert<Operand>(make<Boolean>(true));
	else
		return convert<Operand>(make<Boolean>(false));
}

Operand::pointer_type boolInequalityFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Boolean::value_type op1;
	Boolean::value_type op2;

	op1 = convert<Boolean>(operand1)->get_value();
	op2 = convert<Boolean>(operand2)->get_value();

	if (is<True>(operand1))
		op1 = true;
	else if (is<False>(operand1))
		op1 = false;

	if (is<True>(operand2))
		op2 = true;
	else if (is<False>(operand2))
		op2 = false;

	if (op1 != op2)
		return convert<Operand>(make<Boolean>(true));
	else
		return convert<Operand>(make<Boolean>(false));
}

Operand::pointer_type boolGreaterFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Boolean::value_type op1;
	Boolean::value_type op2;

	op1 = convert<Boolean>(operand1)->get_value();
	op2 = convert<Boolean>(operand2)->get_value();

	if (is<True>(operand1))
		op1 = true;
	else if (is<False>(operand1))
		op1 = false;

	if (is<True>(operand2))
		op2 = true;
	else if (is<False>(operand2))
		op2 = false;

	if (op1 > op2)
		return convert<Operand>(make<Boolean>(true));
	else
		return convert<Operand>(make<Boolean>(false));
}

Operand::pointer_type boolGreaterEqualFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Boolean::value_type op1;
	Boolean::value_type op2;

	op1 = convert<Boolean>(operand1)->get_value();
	op2 = convert<Boolean>(operand2)->get_value();

	if (is<True>(operand1))
		op1 = true;
	else if (is<False>(operand1))
		op1 = false;

	if (is<True>(operand2))
		op2 = true;
	else if (is<False>(operand2))
		op2 = false;

	if (op1 >= op2)
		return convert<Operand>(make<Boolean>(true));
	else
		return convert<Operand>(make<Boolean>(false));
}

Operand::pointer_type boolLessFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Boolean::value_type op1;
	Boolean::value_type op2;

	op1 = convert<Boolean>(operand1)->get_value();
	op2 = convert<Boolean>(operand2)->get_value();

	if (is<True>(operand1))
		op1 = true;
	else if (is<False>(operand1))
		op1 = false;

	if (is<True>(operand2))
		op2 = true;
	else if (is<False>(operand2))
		op2 = false;

	if (op1 < op2)
		return convert<Operand>(make<Boolean>(true));
	else
		return convert<Operand>(make<Boolean>(false));
}

Operand::pointer_type boolLessEqualFunc(Operand::pointer_type operand1, Operand::pointer_type operand2) {
	Boolean::value_type op1;
	Boolean::value_type op2;

	op1 = convert<Boolean>(operand1)->get_value();
	op2 = convert<Boolean>(operand2)->get_value();

	if (is<True>(operand1))
		op1 = true;
	else if (is<False>(operand1))
		op1 = false;

	if (is<True>(operand2))
		op2 = true;
	else if (is<False>(operand2))
		op2 = false;

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
