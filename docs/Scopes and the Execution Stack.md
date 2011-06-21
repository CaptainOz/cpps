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


Execution Stack
===============

The CPPS interpreter works off multiple execution stacks similar to JavaScript.
Each frame on a stack is an abstact syntax tree and the last node being executed
is remembered when a new frame is pushed on top of the stack. Function calls and
code blocks add new frames to the stack while setTimeout and setInterval add new
execution stacks to happen after the current one.

Timeouts and Intervals
----------------------

The two global functions `setTimeout` and `setInterval` act much like the same
named functions in JavaScript but their parameters and return values are
different. Both functions have the following signature:

    std::timeout& setTimeout( function $entrance, number $delay, [array $parameters, [object $scope]] );

The first parameter, `$entrance`, is the function that will be called to start
the execution stack. It can be a non-static class method, in which case the last
parameter is required and must be an instance of the class. The second
parameter, `$delay`, is the minimum number of milliseconds to wait before
entering the new execution stack. To specify a higher resolution of time simply
give a non-whole number (i.e. 0.001 for 1 nanosecond). The `$parameters`
argument is an array of parameters to send to the `$entrance` function. This
argument is optional. The last parameter, `$scope`, is the scope within which to
execute the entrance function. If no scope is provided then the function is
executed in the global scope.

Note that `$delay` is only the _minimum_ number of milliseconds to delay the
execution of the stack. If the execution stacks ahead of the new one take longer
than `$delay` milliseconds to execute then the new stack will be executed as
soon as CPPS gets to it.

The returned `std::timeout` object can be used to control the new execution
stack by removing the timeout entirely or modifying the delay time.


