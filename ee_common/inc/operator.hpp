#if !defined(GUARD_operator_hpp20091126_)
#define GUARD_operator_hpp20091126_

/*
File:		operator.hpp
Author:		Jeremy Peterson-Katz
Date:		December 14, 2017
*/

#include "operation.hpp"
#include "operand.hpp"


/** Operator Precedence values. */
typedef enum { MIN = 0, 
	ASSIGNMENT, LOGOR, LOGXOR, LOGAND, BITOR, BITXOR, BITAND, EQUALITY, 
	RELATIONAL, BITSHIFT, ADDITIVE, MULTIPLICATIVE, POWER, UNARY, POSTFIX,
	MAX } precedence_type;



/** Defines a precedence category method.  Used inside a class declaration. */
#define DEF_PRECEDENCE(category)	public: precedence_type get_precedence() const override { return category; }



/** Operator token base class. */
class Operator : public Operation {
public:
	DEF_POINTER_TYPE(Operator)
	virtual precedence_type get_precedence() const = 0;
	
};

		/** Binary operator token base class. */
		class BinaryOperator : public Operator {
		public:
			virtual unsigned number_of_args() const override { return 2; }
		};

				/** Right-associative operator base class. */
				class RAssocOperator : public BinaryOperator { };

						/** Power token. */
						class Power : public RAssocOperator {
							DEF_PRECEDENCE(POWER)
						public:
							int operationIndex() { return 8; }
						};

						/** Assignment token. */
						class Assignment : public RAssocOperator {
							DEF_PRECEDENCE(ASSIGNMENT)
						};

				/** Left-associative operator base class. */
			    class LAssocOperator : public BinaryOperator { };

					/** Multiplication token. */
					class Multiplication : public LAssocOperator {
						DEF_PRECEDENCE(MULTIPLICATIVE)
					public:
						int operationIndex() { return 3; }
					};

					/** Division token. */
					class Division : public LAssocOperator {
						DEF_PRECEDENCE(MULTIPLICATIVE)
					public:
						int operationIndex() { return 4; }
					};

					/** Modulus token. */
					class Modulus : public LAssocOperator {
						DEF_PRECEDENCE(MULTIPLICATIVE)
					public:
						int operationIndex() { return 7; }
					};

					/** Addition token. */
					class Addition : public LAssocOperator {
						DEF_PRECEDENCE(ADDITIVE)
					public:
						int operationIndex() { return 5; }
					};

					/** Subtraction token. */
					class Subtraction : public LAssocOperator {
						DEF_PRECEDENCE(ADDITIVE)
					public:
						int operationIndex() { return 6; }
					};

					/** Or token. */
					class Or : public LAssocOperator {
						DEF_PRECEDENCE(LOGOR)
					public:
						int operationIndex() { return 13; }
					};

					/** And token. */
					class And : public LAssocOperator {
						DEF_PRECEDENCE(LOGAND)
					public:
						int operationIndex() { return 10; }
					};

					/** Xor token. */
					class Xor : public LAssocOperator {
						DEF_PRECEDENCE(LOGXOR)
					public:
						int operationIndex() { return 14; }
					};

					/** Nor token. */
					class Nor : public LAssocOperator {
						DEF_PRECEDENCE(LOGOR)
					public:
						int operationIndex() { return 12; }
					};

					/** Nand token. */
					class Nand : public LAssocOperator {
						DEF_PRECEDENCE(LOGAND)
					public:
						int operationIndex() { return 11; }
					};

					/** Xnor token. */
					class Xnor : public LAssocOperator {
						DEF_PRECEDENCE(LOGXOR)
					public:
						int operationIndex() { return 37; }
					};

					/** Equality (==) token. */
					class Equality : public LAssocOperator {
						DEF_PRECEDENCE(EQUALITY)
					public:
						int operationIndex() { return 15; }
					};

					/** Greater (>) token. */
					class Greater : public LAssocOperator {
						DEF_PRECEDENCE(RELATIONAL)
					public:
						int operationIndex() { return 17; }
					};

					/** Greater Equal (>=) token. */
					class GreaterEqual : public LAssocOperator {
						DEF_PRECEDENCE(RELATIONAL)
					public:
						int operationIndex() { return 18; }
					};

					/** Inequality (!=) token. */
					class Inequality : public LAssocOperator {
						DEF_PRECEDENCE(EQUALITY)
					public:
						int operationIndex() { return 16; }
					};

					/** Less (<) token. */
					class Less : public LAssocOperator {
						DEF_PRECEDENCE(RELATIONAL)
					public:
						int operationIndex() { return 19; }
					};

					/** Less Equal (<=) token. */
					class LessEqual : public LAssocOperator {
						DEF_PRECEDENCE(RELATIONAL)
					public:
						int operationIndex() { return 20; }
					};

		/** NonAssociative operator token base class. */
		class NonAssociative : public Operator {};

			/** Unary operator token base class. */
			class UnaryOperator : public NonAssociative {
			DEF_PRECEDENCE(UNARY)
			public:
				virtual unsigned number_of_args() const override { return 1; }
			};

				/** Negation token. */
				class Negation : public UnaryOperator {
				public:
					int operationIndex() { return 1; }
				};

				/** Identity token. */
				class Identity : public UnaryOperator {
				public:
					int operationIndex() { return 0; }
				};

				/** Not token. */
				class Not : public UnaryOperator {
				public:
					int operationIndex() { return 9; }
				};

				/** Postfix operator token base class. */
				class PostfixOperator : public UnaryOperator {
					DEF_PRECEDENCE(POSTFIX)
				};

					/** Factorial token. */
					class Factorial : public PostfixOperator {
					public:
						int operationIndex() { return 2; }
					};

/*=============================================================

Revision History
Version 1.0.0: 2016-11-02
Added 'override' keyword where appropriate.

Version 0.3.0: 2014-10-30
Removed bitwise operators.

Version 0.2.0: 2012-11-16
Added BitAnd, BitNot, BitOr, BitShiftLeft, BitShiftRight

Version 0.1.1: 2012-11-13
C++ 11 cleanup

Version 0.1.0: 2010-11-09
Switched boost::shared_ptr<> to std::shared_ptr<>.
Added TOKEN_PTR_TYPE macro.

Version 0.0.0: 2009-11-26
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
#endif // GUARD_operator_hpp20091126_
