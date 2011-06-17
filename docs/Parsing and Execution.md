Stages of Parsing
=================
  1. Code string
    * The code as written by the programmer including all whitespace and
      comments.
  1. Tokens
    * First pass over the code. Extracted tokens represent full chunks of
      information from the code.
    * Tokens have a type and in some cases a string representation.
  1. Statements
    * Tokens are grouped together into expressions which make up a statement.
    * Each expression results in a value which can be used by the next
      expression to operate.
    * Statements produce one value and can have any number of side effects.
  1. Statement tree
    * Statements are ordered into a tree as branches of the tree, and each node
      is an expression.
    * Statement trees can be walked in a depth-first traversal to execute the
      code in the correct order.

Code
----
Code is the actual words and symbols that the programmer writes, combined.

    $cout << "Hello" << " " << "world!";

Tokens
------
Tokens are the individual pieces words or symbols in the code. Each of the
following is a separate token:

  * $cout
  * <<
  * "Hello"
  * <<
  * " "
  * <<
  * " world!"
  * ;

Statements
----------
Statements are the tokens grouped together into one or more expressions. Each of
the following is a separate expression which make up one statement:

  * $cout << "Hello"
  * _previous result_ << " "
  * _previous result_ << " world!"

Note that the semicolon is not part of the statement, but simply denotes the end
of the statement.

Statement Tree
--------------
The expressions are then ordered into a heirarchy and put into a statement tree
which denotes the order of execution. Operators make up the switch nodes, and
identifiers, variables, and literal constants make up leaf nodes.

                                    +--------+
                                    | << (3) |
                                    +--------+
                                   /          \
                              +--------+  +----------+
                              | << (2) |  | "world!" |
                              +--------+  +----------+
                             /          \
                        +--------+    +-----+
                        | << (1) |    | " " |
                        +--------+    +-----+
                       /          \
                  +-------+   +---------+
                  | $cout |   | "Hello" |
                  +-------+   +---------+

The parse tree displayed above in ASCII would start at the node `<< (3)`, step
down to `<< (2)`, then `<< (1)`. `<< (1)` would get executed using `$cout` and
`"Hello"` as the two parameters. The result of `<< (1)` would be used to execute
`<< (2)` with `" "`. The result of that would then be used with `"world!"` by
`<< (3)`. And finally the result of `<< (3)` would be the value returned by this
statement in the statement tree.

Parse trees are not binary trees, a node can have 3 or more sub-statements. For
example, an `if-then-else` statement would result in a root node with 3
immediate child expressions: the if conditional, the then code block, and the
else code block. Code blocks can have any number of child statements which each
get executed sequentially.


