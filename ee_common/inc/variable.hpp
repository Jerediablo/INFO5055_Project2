#if !defined(GUARD_variable_hpp20091126_)
#define GUARD_variable_hpp20091126_

/** @file: variable.hpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@date 2012-11-13
	@version 0.1.1
	@note Compiles under Visual C++ v110

	@brief Variable class declaration.
	*/

#include "operand.hpp"

/** Variable token. */
class Variable : public Operand {
	// TO DO 
};

/*=============================================================

Revision History

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
#endif // GUARD_variable_hpp20091126_
