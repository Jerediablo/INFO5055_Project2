#if !defined(GUARD_pseudo_operation_hpp20091210_)
#define GUARD_pseudo_operation_hpp20091210_

/*
File:		pseudo_operation.hpp
Author:		Jeremy Peterson-Katz
Date:		December 14, 2017
*/

#include "token.hpp"


/** Pseudo-operation token base class. */
class PseudoOperation : public Token { };

		/** Parenthesis operation token base class. */
		class Parenthesis : public PseudoOperation { };

				/** Left-parenthesis token. */
				class LeftParenthesis : public Parenthesis { };

				/** Right-parenthesis token. */
				class RightParenthesis : public Parenthesis { };

		/** Argument-separator operation token. */
		class ArgumentSeparator : public PseudoOperation { };




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
#endif // GUARD_pseudo_operation_hpp20091210_
