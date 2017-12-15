/*
File:		tokenizer.cpp
Author:		Jeremy Peterson-Katz
Date:		December 14, 2017
*/

#include "../inc/tokenizer.hpp"
#include "../inc/boolean.hpp"
#include "../inc/function.hpp"
#include "../inc/integer.hpp"
#include "../inc/operator.hpp"
#include "../inc/pseudo_operation.hpp"
#include "../inc/real.hpp"
#include "../inc/variable.hpp"

#include <exception>
#include <limits>
#include <sstream>
#include <stack>
#include <string>

using namespace std;

/** Default constructor loads the keyword dictionary. */
Tokenizer::Tokenizer() {
 	keywords_["abs"]     = keywords_["Abs"]		= keywords_["ABS"]		= make<Abs>();
	keywords_["mod"]	 = keywords_["Mod"]		= keywords_["MOD"]		= make<Modulus>();

	keywords_["pi"] = keywords_["Pi"] = keywords_["PI"] = make<Pi>();
	keywords_["e"] = keywords_["E"] = make<E>();

	keywords_["arccos"] = make<Arccos>();
	keywords_["arcsin"] = make<Arcsin>();
	keywords_["arctan"] = make<Arctan>();
	keywords_["ceil"] = make<Ceil>();
	keywords_["cos"] = make<Cos>();
	keywords_["exp"] = make<Exp>();
	keywords_["floor"] = make<Floor>();
	keywords_["lb"] = make<Lb>();
	keywords_["ln"] = make<Ln>();
	keywords_["log"] = make<Log>();
	keywords_["sin"] = make<Sin>();
	keywords_["sqrt"] = make<Sqrt>();
	keywords_["tan"] = make<Tan>();

	keywords_["arctan2"] = make<Arctan2>();
	keywords_["max"] = make<Max>();
	keywords_["min"] = make<Min>();
	keywords_["pow"] = make<Pow>();

	keywords_["true"] = make<Boolean>(true);
	keywords_["false"] = make<Boolean>(false);

	keywords_["not"] = make<Not>();
	keywords_["and"] = make<And>();
	keywords_["or"] = make<Or>();
	keywords_["xor"] = make<Xor>();
	keywords_["nand"] = make<Nand>();
	keywords_["nor"] = make<Nor>();
	keywords_["xnor"] = make<Xnor>();

	keywords_["result"] = make<Result>();
}




/** Get an identifier from the expression.
	Assumes that the currentChar is pointing to a alphabetic.
	*/
Token::pointer_type Tokenizer::_get_identifier(Tokenizer::string_type::const_iterator& currentChar, Tokenizer::string_type const& expression) {
	// accumulate identifier
	string_type ident;
	do
		ident += *currentChar++;
	while (currentChar != end(expression) && isalnum(*currentChar));

	// check for predefined identifier
	dictionary_type::iterator iter = keywords_.find(ident);
	if (iter != end(keywords_))
		return iter->second;
	
	// TO FIX 
	/*dictionary_type::iterator iterVar = variables_.find(ident);
	if (iterVar != end(variables_))
		return iterVar->second;
	else
		variables_[ident] = make<Variable>();
		return make<Variable>();*/
	

	throw XBadCharacter(expression, currentChar - begin(expression));
}




/** Get a number token from the expression.
	@return One of BinaryInteger, Integer, or Real.
	@param currentChar [in,out] an iterator to the current character.  Assumes that the currentChar is pointing to a digit.
	@param expression [in] the expression being scanned.
*/
Token::pointer_type Tokenizer::_get_number(Tokenizer::string_type::const_iterator& currentChar, Tokenizer::string_type const& expression) {
	assert(isdigit(*currentChar) && "currentChar must be a pointer to a digit");

	string_type s;
	bool decimalEntered = false;
	
	while (currentChar != expression.end() && (isdigit(*currentChar) || *currentChar == '.')) {
		if (isdigit(*currentChar)){
			s += *currentChar;
			++currentChar;
		}
		else if (*currentChar == '.' && decimalEntered == false) {
			s += *currentChar;
			decimalEntered = true;
			++currentChar;
			if (!(isdigit(*currentChar))) {
				throw XBadCharacter(expression, currentChar - begin(expression));
			}
		}
		else if (*currentChar == '.' && decimalEntered == true) {
			throw XBadCharacter(expression, currentChar - begin(expression));
		}
	}

	if (decimalEntered == false) {
		Integer::value_type i = static_cast<Integer::value_type>(s);
		return make<Integer>(i);
	}
	else {
		Real::value_type i = static_cast<Real::value_type>(s);
		return make<Real>(i);
	}
}



/** Tokenize the expression.
	@return a TokenList containing the tokens from 'expression'.
	@param expression [in] The expression to tokenize.
	@note Tokenizer dictionary may be updated if expression contains variables.
	@note Will throws 'BadCharacter' if the expression contains an un-tokenizable character.
	*/
TokenList Tokenizer::tokenize( string_type const& expression ) {
	TokenList tokenizedExpression;
	auto currentChar = expression.cbegin();

	for(;;)
	{
		// strip whitespace
		while (currentChar != end(expression) && isspace(*currentChar))
			++currentChar;

		// check of end of expression
		if (currentChar == end(expression)) break;

		// check for a number
		if (isdigit(*currentChar)) {
			tokenizedExpression.push_back(_get_number(currentChar, expression));
			
			continue;
		}

		if (isalpha(*currentChar)) {
			tokenizedExpression.push_back(_get_identifier(currentChar, expression));

			continue;
		}

		// Handle '(' 
		if (*currentChar == '(') {
			++currentChar;
			tokenizedExpression.push_back(make<LeftParenthesis>());
			continue;
		}

		// Handle ')' 
		if (*currentChar == ')') {
			++currentChar;
			tokenizedExpression.push_back(make<RightParenthesis>());
			continue;
		}

		// Handle '#'
		if (*currentChar == '#') {
			tokenizedExpression.push_back(make<Power>());
			++currentChar;
			continue;
		}

		// Handle '*' 
		if (*currentChar == '*') {
			++currentChar;
			if (*currentChar == '*') {
				++currentChar;
				tokenizedExpression.push_back(make<Power>());
			}
			else {
				tokenizedExpression.push_back(make<Multiplication>());
			}
			continue;
		}

		// Handle '/' 
		if (*currentChar == '/') {
			++currentChar;
			tokenizedExpression.push_back(make<Division>());
			continue;
		}

		// Handle '%' 
		if (*currentChar == '%') {
			++currentChar;
			tokenizedExpression.push_back(make<Modulus>());
			continue;
		}

		// Handle '!'
		if (*currentChar == '!') {
			++currentChar;
			
			if (!(currentChar == end(expression))) {

				if (*currentChar == '=') {
					tokenizedExpression.push_back(make<Inequality>());
					++currentChar;
				}
			}
			else if (tokenizedExpression.size() == 0) {
				throw XBadCharacter(expression, currentChar - begin(expression), "Factorial must follow Expression");
			}
			else if (is<RightParenthesis>(tokenizedExpression.back()) || is<Operand>(tokenizedExpression.back())
				|| is<PostfixOperator>(tokenizedExpression.back())) {

				tokenizedExpression.push_back(make<Factorial>());
			}
			else {
				throw XBadCharacter(expression, currentChar - begin(expression), "Factorial must follow Expression");
			}

			continue;
		}


		// Handle '+' 
		if (*currentChar == '+') {
			++currentChar;
			if (tokenizedExpression.size() == 0) {
				tokenizedExpression.push_back(make<Identity>());
			}
			else if (is<RightParenthesis>(tokenizedExpression.back()) || is<Operand>(tokenizedExpression.back())
				|| is<PostfixOperator>(tokenizedExpression.back())) {

				tokenizedExpression.push_back(make<Addition>());
			}
			else {
				tokenizedExpression.push_back(make<Identity>());
			}
			continue;
		}

		// Handle '-'
		if (*currentChar == '-') {
			++currentChar;
			if (tokenizedExpression.size() == 0) {
				tokenizedExpression.push_back(make<Negation>());
			}

			else if (is<RightParenthesis>(tokenizedExpression.back()) || is<Operand>(tokenizedExpression.back())
				|| is<PostfixOperator>(tokenizedExpression.back())) {

				tokenizedExpression.push_back(make<Subtraction>());
			}
			else {
				tokenizedExpression.push_back(make<Negation>());
			}
			continue;
		}

		// Handle ','
		if (*currentChar == ',') {
			++currentChar;
			tokenizedExpression.push_back(make<ArgumentSeparator>());
			
			continue;
		}

		// Handle '>'
		if (*currentChar == '>') {
			++currentChar;
			if (*currentChar == '=') {
				tokenizedExpression.push_back(make<GreaterEqual>());
				++currentChar;
			}
			else {
				tokenizedExpression.push_back(make<Greater>());
			}
			continue;
		}

		// Handle '<'
		if (*currentChar == '<') {
			++currentChar;
			if (*currentChar == '=') {
				tokenizedExpression.push_back(make<LessEqual>());
				++currentChar;
			}
			else {
				tokenizedExpression.push_back(make<Less>());
			}
			continue;
		}

		// Handle '='
		if (*currentChar == '=') {
			++currentChar;
			if (*currentChar == '=') {
				tokenizedExpression.push_back(make<Equality>());
				++currentChar;
			}
			else {
				tokenizedExpression.push_back(make<Assignment>());
			}
			continue;
		}

		// not a recognized token
		throw XBadCharacter(expression, currentChar - begin(expression));
	}

	return tokenizedExpression;
}

/*=============================================================

Revision History

Version 0.3.0: 2017-11-23
Added Python-style power operator '**'.

Version 0.2.0: 2012-11-16
Added BitAnd, BitNot, BitOr, BitXOr, BitShiftLeft, BitShiftRight
Simplified CHECK_OP macros

Version 0.1.0: 2012-11-15
Replaced BadCharacter with XTokenizer, XBadCharacter, and XNumericOverflow
Added BinaryInteger, Binary <function>

Version 0.0.1: 2012-11-13
C++ 11 cleanup

Version 0.0.0: 2009-11-25
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
