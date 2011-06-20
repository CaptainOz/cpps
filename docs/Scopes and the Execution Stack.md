Scopes
======

A scope is simple a chunk of code that can contain variable declarations. Code
blocks, namespaces, functions, try-catch blocks, and classes are all scopes.
When a scope is entered a reference to it is added to the execution stack and
when the scope is exited that reference is popped off the stack. For named
scopes (i.e. namespaces and classes) a reference to them is also held on to by
the parent scope. However anonymous scopes (i.e. function calls and code blocks)
have no references held to them, so when they are popped off the execution stack
the scope and any variables it held are freed.

Functions and Classes
---------------------

Both functions and classes are different from the other types of scopes in that
they are named scopes, but never directly added to the execution stack. In both
cases copies of the scopes are initialized and only variables or functions
declared as `static` are added to the original scope. In the case of functions,
copies of the scope are added to the execution stack so variables declared
within the function's execution are not added to the original. Classes are
similar, but are copied into variables instead of the execution stack. Any
variables added to the class instance during execution are not added to the
original class definition. Note that variables and functions declared as
`static` are added to the class or function during parsing, not execution so
they are added to the original class or function.



