/**
 *
 */

#include "Token.h"

namespace cpps
{

// Token typenames as suitable for humans to read ordered same as Token::Type.
const char* Token::TypeNames[] = {
        // *** Begin Miscelaneous Token Types *** //
        "TypeName",        // [a-zA-Z_]\w*
        "Variable",        // \$[a-zA-Z_]\w*
        "StringLiteral",   // (['"]).*?(?<!\\)\1
        "NumericLiteral",  // (?i:[1-9]\d*|\d+\.\d*|0[0-7]*|0x[\da-f]+|0b[01]+)
        "CommentLine",     // \/\/[^\n]*
        "CommentBlock",    // \/\*.*?\*\/
        "RegexMatch",      // \/.?(?<!\\)\/
        // *** End Miscelaneous Token Types *** //

        // *** Begin Non-Overloadable Operators *** //
        "Scope",           // ::
        "Semicolon",       // ;
        "Colon",           // :
        "Comma",           // ,
        "LogicalOr",       // \|\|
        "LogicalAnd",      // &&
        "TernaryIf",       // \?
        "OpenBrace",       // \{
        "CloseBrace",      // \}
        // *** End Non-Overloadable Operators *** //

        // *** Begin Overloadable Operators *** //
        "OpenParen",       // \(
        "CloseParen",      // \)
        "OpenBracket",     // \[
        "CloseBracket",    // \]
        "Equality",        // ==
        "NotEquality",     // !=
        "GreaterEqual",    // >=
        "LessEqual",       // <=
        "Assign",          // =
        "AssignPlus",      // \+=
        "AssignMinus",     // -=
        "AssignConcat",    // .=
        "AssignMultiply",  // \*=
        "AssignDivide",    // \/=
        "AssignModulo",    // %=
        "AssignBitAnd",    // &=
        "AssignBitXOr",    // \^=
        "AssignBitOr",     // |=
        "AssignLeftShift", // <<=
        "AssignRightShift",// >>=
        "Increment",       // \+\+
        "Decrement",       // --
        "LogicalNot",      // !
        "BitwiseNot",      // ~
        "RighShift",       // >>
        "LeftShift",       // <<
        "MemberAccess",    // ->
        "GreaterThan",     // >
        "LessThan",        // <
        "Plus",            // \+
        "Minus",           // -
        "Multiply",        // \*
        "Divide",          // \/
        "Modulo",          // %
        "Concat",          // \.
        "BitwiseAnd",      // &
        "BitwiseXOr",      // \^
        "BitwiseOr",       // \|
        // *** End Overloadable Operators *** //

        // *** Begin Keywords *** //
        "Break",           // break
        "Case",            // case
        "Catch",           // catch
        "Class",           // class
        "Const",           // const
        "Continue",        // continue
        "Default",         // default
        "Delete",          // delete
        "Do",              // do
        "Else",            // else
        "Enum",            // enum
        "False",           // false
        "For",             // for
        "Foreach",         // foreach
        "Friend",          // friend
        "Function",        // function
        "If",              // if
        "Include",         // include
        "InstanceOf",      // instanceof
        "Namespace",       // namespace
        "New",             // new
        "Null",            // null
        "Operator",        // operator
        "Private",         // private
        "Protected",       // protected
        "Public",          // public
        "Return",          // return
        "SizeOf",          // sizeof
        "Static",          // static
        "Struct",          // struct
        "Switch",          // switch
        "This",            // this
        "Throw",           // throw
        "True",            // true
        "Try",             // try
        "TypeDef",         // typedef
        "TypeNameOperator",// typename
        "Union",           // union
        "Using",           // using
        "While",           // while
        "Var",             // var
        // *** End Keywords *** //

        "EndOfFile",
        0 // End array
    };

// Keyword strings as they appear in the code ordered the same as Token::Type.
const char* Token::_keywords[] = {
        "break",      "case",      "catch",  "class",    "const",    "continue",
        "default",    "delete",    "do",     "else",     "enum",     "false",
        "for",        "foreach",   "friend", "function", "if",       "include",
        "instanceof", "namespace", "new",    "null",     "operator", "private",
        "protected",  "public",    "return", "sizeof",   "static",   "struct",
        "switch",     "this",      "throw",  "true",     "try",      "typedef",
        "typename",   "union",     "using",  "while",    "var",

        0 // End array
    };

// Operator strings as they appear in the code ordered the same as Token::Type.
const char* Token::_operators[] = {
        "::",  ";",   ":",  ",",  "||", "&&", "?",  "{",  "}",
        "(",   ")",   "[",  "]",  "==", "!=", ">=", "<=", "=",
        "+=",  "-=",  ".=", "*=", "/=", "%=", "&=", "^=", "|=",
        "<<=", ">>=", "++", "--", "!",  "~",  ">>", "<<", "->",
        ">",   "<",   "+",  "-",  "*",  "/",  "%",  ".",  "&",
        "^",   "|",

        0 // End array
    };


} // end namespace cpps

