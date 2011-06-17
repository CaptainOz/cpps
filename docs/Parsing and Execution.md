Stages of Parsing
-----------------
  1. Code string
    * The code as written by the programmer including all whitespace and
      comments.
  1. Tokens
    * First pass over the code. Extracted tokens represent full chunks of
      information from the code.
    * Tokens have a type and in some cases a string representation.
  1. Operations
    * Tokens are converted to operation commands.
    * Operations are made up of groups of tokens.
    * When given a scope and parameters, operations can be executed to result
      in a single object.
  1. Statements
    * Operations are grouped together into statements where the result of one
      operation acts as a parameter to the next.
    * Statements result in nothing and use only a scope, no parameters.
  1. Statement tree
    * 

