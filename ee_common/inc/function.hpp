#if !defined(GUARD_function_hpp20091126_)
#define GUARD_function_hpp20091126_

/*
File:		function.hpp
Author:		Jeremy Peterson-Katz
Date:		December 14, 2017
*/

#include "operation.hpp"

/** Function token base class. */
class Function : public Operation { };

		/** One argument function token base class. */
		class OneArgFunction : public Function {
		public:
			virtual unsigned number_of_args() const override { return 1; }
		};

				/** Absolute value function token. */
				class Abs : public OneArgFunction {
				public:
					int operationIndex() { return 21; }
				};

				/** Arccos function token. */
				class Arccos : public OneArgFunction {
				public:
					int operationIndex() { return 22; }
				};

				/** Arcsin function token. */
				class Arcsin : public OneArgFunction {
				public:
					int operationIndex() { return 23; }
				};

				/** Arctan function token. */
				class Arctan : public OneArgFunction { 
				public:
					int operationIndex() { return 24; }
				};

				/** Ceil function token. */
				class Ceil : public OneArgFunction {
				public:
					int operationIndex() { return 25; }
				};

				/** Cos function token. */
				class Cos : public OneArgFunction {
				public:
					int operationIndex() { return 26; }
				};

				/** Exp function token. */
				class Exp : public OneArgFunction {
				public:
					int operationIndex() { return 27; }
				};

				/** Floor function token. */
				class Floor : public OneArgFunction {
				public:
					int operationIndex() { return 28; }
				};

				/** Lb function token. */
				class Lb : public OneArgFunction {
				public:
					int operationIndex() { return 29; }
				};

				/** Ln function token. */
				class Ln : public OneArgFunction {
				public:
					int operationIndex() { return 30; }
				};

				/** Log function token. */
				class Log : public OneArgFunction {	};

				/** Result function token. */
				class Result : public OneArgFunction { };

				/** Sin function token. */
				class Sin : public OneArgFunction {
				public:
					int operationIndex() { return 31; }
				};

				/** Sqrt function token. */
				class Sqrt : public OneArgFunction {
				public:
					int operationIndex() { return 32; }
				};

				/** Tan function token. */
				class Tan : public OneArgFunction {
				public:
					int operationIndex() { return 33; }
				};

		/** Two argument function token base class. */
		class TwoArgFunction : public Function {
		public:
			virtual unsigned number_of_args() const override { return 2; }
		};

				/** Arctan two argument function token. */
				class Arctan2 : public TwoArgFunction {
				public:
					int operationIndex() { return 36; }
				};

				/** Max function token. */
				class Max : public TwoArgFunction {
				public:
					int operationIndex() { return 34; }
				};

				/** Min function token. */
				class Min : public TwoArgFunction {
				public:
					int operationIndex() { return 35; }
				};

				/** Power function token. */
				class Pow : public TwoArgFunction {
				public:
					int operationIndex() { return 8; }
				};
/*=============================================================

Revision History

Version 1.0.0: 2016-11-02
Added 'override' keyword where appropriate.

Version 0.0.2: 2014-10-30
Removed binary function

Version 0.0.1: 2012-11-13
C++ 11 cleanup

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
#endif // GUARD_function_hpp20091126_
