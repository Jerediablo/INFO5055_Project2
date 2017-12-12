#if !defined(GUARD_operator_hpp20091126_)
#define GUARD_operator_hpp20091126_

/** @file: operator.hpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@date 2012-11-16
	@version 0.2.0
	@note Compiles under Visual C++ v110

	@brief Operator class declarations
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
						};

						class Assignment : public RAssocOperator {
							DEF_PRECEDENCE(ASSIGNMENT)
						};

			    class LAssocOperator : public BinaryOperator { };

					class Multiplication : public LAssocOperator {
						DEF_PRECEDENCE(MULTIPLICATIVE)
					};

					class Division : public LAssocOperator {
						DEF_PRECEDENCE(MULTIPLICATIVE)
					};

					class Modulus : public LAssocOperator {
						DEF_PRECEDENCE(MULTIPLICATIVE)
					};

					class Addition : public LAssocOperator {
						DEF_PRECEDENCE(ADDITIVE)
					};

					class Subtraction : public LAssocOperator {
						DEF_PRECEDENCE(ADDITIVE)
					};

					class Or : public LAssocOperator {
						DEF_PRECEDENCE(LOGOR)
					};

					class And : public LAssocOperator {
						DEF_PRECEDENCE(LOGAND)
					};

					class Xor : public LAssocOperator {
						DEF_PRECEDENCE(LOGXOR)
					};

					class Nor : public LAssocOperator {
						DEF_PRECEDENCE(LOGOR)
					};

					class Nand : public LAssocOperator {
						DEF_PRECEDENCE(LOGAND)
					};

					class Xnor : public LAssocOperator {
						DEF_PRECEDENCE(LOGXOR)
					};

					class Equality : public LAssocOperator {
						DEF_PRECEDENCE(EQUALITY)
					};

					class Greater : public LAssocOperator {
						DEF_PRECEDENCE(RELATIONAL)
					};

					class GreaterEqual : public LAssocOperator {
						DEF_PRECEDENCE(RELATIONAL)
					};

					class Inequality : public LAssocOperator {
						DEF_PRECEDENCE(EQUALITY)
					};

					class Less : public LAssocOperator {
						DEF_PRECEDENCE(RELATIONAL)
					};

					class LessEqual : public LAssocOperator {
						DEF_PRECEDENCE(RELATIONAL)
					};

		class NonAssociative : public Operator {};

			class UnaryOperator : public NonAssociative {
			DEF_PRECEDENCE(UNARY)
			public:
				virtual unsigned number_of_args() const override { return 1; }
			};

				class Negation : public UnaryOperator {};

				class Identity : public UnaryOperator {};

				class Not : public UnaryOperator {};

				class PostfixOperator : public UnaryOperator {
					DEF_PRECEDENCE(POSTFIX)
				};
					
					class Factorial : public PostfixOperator { };

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
