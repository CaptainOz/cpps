CPPS - C Plus Plus Script
=========================

C++ Script is to C++ as JavaScript is to Java, that is to say it has a similar
syntax and some shared standard objects. CPPS is not .cpp files interpreted as
scripts, it has its own syntax which, while similar to C++, is considerably
different.


Variable Typing in CPPS
-----------------------

In CPPS, all variables should be explicitly declared in the scope they are to
exist in. Any variable that is not declared before use is assumed to be a global
of type "var." Variable declarations are in the following format:

    <type> $<name> [( [<variable> [, <variable> [, ...]]] ) | = <variable>];

  * "Type" must be either a class name or the keyword "var." Variables declared
    as "var" can be assigned any value and assigned to any variable.
  * "Name" must be a valid identifier. CPPS follows the C++ identifier rules,
    meaning it must start with an underscore or alphabetical character followed
    by any alphanumeric character or underscore.
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
    <type>(<variable>)


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
reference instead of by value to the function. CPPS will not do any implicit
referencing ever. If you are passing a large object and don't want it copied,
pass it by reference explicitly.


String Literals in CPPS
---------------

Strings literals can be between either single-quotes (') or double-quotes (").
Either type that you use does not matter to CPPS, both are treated exactly the
same. In either case the string can contain variable names within it which will
be expanded upon execution, similar to Perl or PHP double-quoted strings.


For and Foreach
---------------

CPPS supports the classic 3-part for loop with syntax similar to C++:

    for( [[<type>][&] $<name> [= <value>][, ...]]; <boolean check>; [<increment statement>] )

But CPPS also supports a foreach loop that will loop through all the numeric
indexes if the container supports numeric indexing, otherwise it will loop
through all the keys available in the scope. The syntax for it is as follows:

    foreach( $<name> as [[&] $<key> :] [&] $<value> )

"Available in the scope" refers to the protection placed on members of an object
for encapsulation (i.e. public, protected, private). For instance, take the
following example:

    class Foo
    {
    public:
        function foo()
        {
            foreach( $this as $foo )
                cout << $foo << '\n';
        }

        var $pubFoo = 1;
    protected:
        var $proFoo = 2;
    private:
        var $priFoo = 3;
    };

    class Bar : public Foo
    {
    public:
        function bar()
        {
            foreach( $this as $bar )
                cout << $bar << '\n';
        }
    };

    function foobar( $foobar )
    {
        foreach( $foobar as $foo )
            cout << $foo << '\n';
    }

    Bar $b = new Bar();

    cout << "Foo says:\n";
    $b->foo();
    cout << "Bar says:\n";
    $b->bar();
    cout << "Foobar says:\n";
    foobar( $b );

This will output the following text:

    Foo says:
    1
    2
    3
    Bar says:
    1
    2
    Foobar says:
    1

So you see, Foo::foo has access to all levels (public, protected, and private)
while Bar::bar only has access to public and protected (since Bar inherits from
Foo) and the function foobar only has access to public attributes.

