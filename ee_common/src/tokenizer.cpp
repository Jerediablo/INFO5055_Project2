/** @file: tokenizer.cpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@version 0.3.0
	@date 2017-11-23
	@note Compiles under Visual C++ 15.4.4

	@brief Tokenizer class implementation.
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
//	keywords_["abs"]     = keywords_["Abs"]		= keywords_["ABS"]		= make<Abs>();
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

		// Handle '*' 
		if (*currentChar == '*') {
			++currentChar;
			tokenizedExpression.push_back(make<Addition>());
		
		}

		// Handle '!'
		if (*currentChar == '!') {
			++currentChar;
			if (tokenizedExpression.size() == 0) {
				throw XBadCharacter(expression, currentChar - begin(expression), "Factorial must follow Expression");
			}
			else if (is<RightParenthesis>(tokenizedExpression.back()) || is<Operand>(tokenizedExpression.back())
				|| is<PostfixOperator>(tokenizedExpression.back())) {

				tokenizedExpression.push_back(make<Factorial>());
			}
			else {
				throw XBadCharacter(expression, currentChar - begin(expression), "Factorial must follow Expression");
			}
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
