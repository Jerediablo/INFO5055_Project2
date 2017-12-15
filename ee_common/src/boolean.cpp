/*
File:		boolean.cpp
Author:		Jeremy Peterson-Katz
Date:		December 14, 2017
*/

#include "../inc/boolean.hpp"
#include <boost/multiprecision/debug_adaptor.hpp>

//Function to return the token type as a string for a Boolean token
Boolean::string_type Boolean::to_string() const {
	return /*string_type("Boolean: ") + */boost::lexical_cast<string_type>(get_value());
}

//Function to return the token type as a string for a False token
False::string_type False::to_string() const {
	return /*string_type("False: ") + */boost::lexical_cast<string_type>(get_value());
}

//Function to return the token type as a string for a True token
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
