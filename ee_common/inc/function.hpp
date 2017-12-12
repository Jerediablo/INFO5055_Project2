#if !defined(GUARD_function_hpp20091126_)
#define GUARD_function_hpp20091126_

/** @file: function.hpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@version 1.0.0
	@date 2012-11-13
	@note Compiles under Visual C++ v120

	@brief function token declarations.
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
				class Abs : public OneArgFunction {	};

				class Arccos : public OneArgFunction { };

				class Arcsin : public OneArgFunction { };

				class Arctan : public OneArgFunction { };

				class Ceil : public OneArgFunction { };

				class Cos : public OneArgFunction {	};

				class Exp : public OneArgFunction {	};

				class Floor : public OneArgFunction {	};

				class Lb : public OneArgFunction {	};

				class Ln : public OneArgFunction {	};

				class Log : public OneArgFunction {	};

				class Result : public OneArgFunction { };

				class Sin : public OneArgFunction {	};

				class Sqrt : public OneArgFunction { };

				class Tan : public OneArgFunction {	};

		class TwoArgFunction : public Function {
		public:
			virtual unsigned number_of_args() const override { return 2; }
		};

				class Arctan2 : public TwoArgFunction {	};

				class Max : public TwoArgFunction {	};

				class Min : public TwoArgFunction {	};

				class Pow : public TwoArgFunction {	};
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
