#include <string> // for string
#include <iostream>
#include <sstream>
#include "str2l-error.h"
using namespace std; // for string
                     /**
                      * A string to long conversion exception.
                      */

str2l_error::str2l_error(string str)
{
  ostringstream oss;
  oss << "(str2l_error: unable to convert the string \"" << str << "\" to a long)";
  this->str = oss.str();
}

str2l_error::~str2l_error() throw() {}

const char *str2l_error::what() const throw()
{
  return this->str.c_str();
}
