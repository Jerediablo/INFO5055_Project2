/*
File:		real.cpp
Author:		Jeremy Peterson-Katz
Date:		December 14, 2017
*/

#include "../inc/real.hpp"
#include <boost/lexical_cast.hpp>

//Function to return the token type as a string for a Real token
Real::string_type Real::to_string() const {
	return /*string_type("Real: ") + */boost::lexical_cast<string_type>(get_value());
}

/*=============================================================

Revision History
Version 1.0.0: 2014-10-29
C++ 11 refactor.
Switched value_type to boost::multiprecision::cpp_dec_float_100

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
