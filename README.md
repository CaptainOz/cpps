CPPS - C Plus Plus Script
=========================

CPPS is to C++ as JS is to Java, that is to say it has a similar syntax and some
shared standard objects. CPPS is not .cpp files interpreted as scripts, it has
its own syntax which, while similar to C++, is different in many ways.


Variable Typing in CPPS
-----------------------

In CPPS, all variables should be explicitly declared in the scope they are to
exist in. Any variable that is not declared before use is assumed to be a global
of type "var." Variable declarations are in the following format:

    <type> <name> [( [<variable> [, <variable> [, ...]]] ) | = <variable>];

  * "Type" must be either a class name or the keyword "var." Variables declared
    as "var" can be assigned any value and assigned to any variable.
  * "Name" must be a valid identifier. CPPS follows the C++ identifier rules,
    meaning it must start with an underscore or alphabetical character followed
    by any alphanumeric character or underscore however they must be preceded by
    a dollar sign ($).
  * "Variable" must be either a variable identifier or a literal constant.

If a "type" other than "var" is given then only values of classes that are or
inherit from the given type, or the type has a conversion constructor for can be
assigned to it. In the case where this is not followed, a fatal error is raised.

The following types are supplied built-in to CPPS:
  * object
    - Base type inherited by all other classes.
  * string
    - Basic string type for characters.
  * number
    - Basic numeric type. All numbers are of this type. Numbers have two
      sub-types: int and float. By default all numbers are floats, but through
      either casting to or direct declaration as int you can remove the decimal
      part.
  * function
    - The type of functions. Any object with a function operator defined
      (operator()) can be safely cast to the function type.
  * stream
    - All IO classes inherit from this class.
  * file
    - Enhanced stream class used for file reading/writing.
  * array
    - Numerically keyed array.

You can cast from one type to another using either C or C++ style casting:

    (<type>)<variable> 
        - OR -
    <type>(<variable))


Functions in CPPS
-----------------

A function's signature is a combination of its name and its parameters. Both the
number of and type of parameters is used. In this fashion it is possible to
overload functions similar to how C++ overloads. Function delcarations are in
the following format:

    [<type>][&] function <name>( [[<type>][&] $<name> [, [<type>][&] $<name> [, ...]]] )
    {
        [<code>]
    }

In any place where "type" is omitted it is assumed to be "var." The ampersand
operator in the parameter list indicates that the variable will be based by
reference instead of by value to the function. The ampersand before the
"function" keyword means the value returned from the function will be returned
by reference.


Referencing in CPPS
-------------------

CPPS will not do any implicit referencing, it will pass variables by reference
as a performance increase, but unless the variable is explicitly passed by
reference its contents will be copied to a new variable upon first modification.
The same holds true for returning variables from functions.



