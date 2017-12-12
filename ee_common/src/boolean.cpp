/** @file: boolean.cpp
	@author Garth Santor/Trinh Han
	@author http://www.gats.ca/
	@date 2012-11-13
	@version 0.0.1
	@note Compiles under Visual C++ v110

	@brief Boolean class implementation.
	*/

#include "../inc/boolean.hpp"
#include <boost/multiprecision/debug_adaptor.hpp>

Boolean::string_type Boolean::to_string() const {
	return /*string_type("Boolean: ") + */boost::lexical_cast<string_type>(get_value());
}

False::string_type False::to_string() const {
	return /*string_type("False: ") + */boost::lexical_cast<string_type>(get_value());
}

True::string_type True::to_string() const {
	return /*string_type("True: ") + */boost::lexical_cast<string_type>(get_value());
}
/*=============================================================

Revision History

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
