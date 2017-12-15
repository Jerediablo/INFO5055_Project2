/*
File:		variable.cpp
Author:		Jeremy Peterson-Katz
Date:		December 14, 2017
*/

#include "../inc/variable.hpp"
#include <boost/lexical_cast.hpp>

//Function to return the token type as a string for a Variable token
Variable::string_type Variable::to_string() const {

	//If the value is NULL, have an appropriate string printed
	if (get_value() == NULL)
		return string_type("Variable: null");
	else
		return string_type("Variable: ") + boost::lexical_cast<string_type>(get_value()) ;
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
