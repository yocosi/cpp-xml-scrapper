#include <string> // for string
#include <iostream>
#include <sstream>
#include "str2i-error.h"
using namespace std; // for string
                     /**
                      * A string to int conversion exception.
                      */

str2i_error::str2i_error(string str)
{
  ostringstream oss;
  oss << "(str2i_error: unable to convert the string \"" << str << "\" to an int)";
  this->str = oss.str();
}

str2i_error::~str2i_error() throw() {}

const char *str2i_error::what() const throw()
{
  return this->str.c_str();
}
