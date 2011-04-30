/**
 * @file Interpreter.cpp
 *
 * @brief Contains the code for the CPPS Interpreter.
 *
 * @author Nate Lillich
 */


#include "Interpreter.h"
#include <sstream>

using namespace std;

namespace cpps
{

enum TokenType
{
    tt_TypeName,        // [a-zA-Z_]\w*
    tt_Identifier,      // \$[a-zA-Z_]\w*
    tt_StringLiteral,   // (['"]).*?(?<!\\)\1
    tt_NumericLiteral,  // (?:\d+|\d*\.\d+)
    tt_Scope,           // ::
    tt_MemberAccess,    // ->
    tt_Semicolon,       // ;
    tt_Comma,           // ,
    tt_Plus,            // \+
    tt_Minus,           // -
    tt_Multiply,        // \*
    tt_Divide,          // /
    tt_Modulo,          // %
    tt_Concat,          // \.
    tt_Increment,       // \+\+
    tt_Decrement,       // --
    tt_OpenParen,       // \(
    tt_CloseParen,      // \)
    tt_OpenBrace,       // \{
    tt_CloseBrace,      // \}
    tt_OpenBracket,     // \[
    tt_CloseBracket,    // \]
    tt_LogicalNot,      // !
    tt_LogicalOr,       // \|\|
    tt_LogicalAnd,      // &&
    tt_Equality,        // ==
    tt_NotEquality,     // !=
    tt_GreaterThan,     // >
    tt_LessThan,        // <
    tt_GreaterEqual,    // >=
    tt_LessEqual,       // <=
    tt_Assign,          // =
    tt_AssignPlus,      // \+=
    tt_AssignMinus,     // -=
    tt_AssignMultiply,  // \*=
    tt_AssignDivide,    // /=
    tt_AssignModulo,    // %=
    tt_AssignBitAnd     // &=
    tt_AssignBitXOr,    // \^=
    tt_AssignBitOr      // |=
    tt_AssignLeftShift, // <<=
    tt_AssignRightShift,// >>=
    tt_BitwiseNot,      // ~
    tt_BitwiseAnd,      // &
    tt_BitwiseXOr,      // \^
    tt_BitwiseOr,       // \|
    tt_TypeNameOperator,// typename
    tt_SizeOf,          // sizeof
    tt_InstanceOf,      // instanceof
    tt_New,             // new
    tt_Delete,          // delete
    tt_RighShift,       // >>
    tt_LeftShift,       // <<
    tt_TernaryIf,       // \?
    tt_TernaryElse,     // :

    tt_TokenTypeCount
}; // end enum TokenType

Interpreter::Interpreter( void )
{
}


/*********************************************************/


Object Interpreter::exec(
        const    string& code,
                 Scope&  scope,
        unsigned int     lineNumber
    )
{
    // Tokenize
    

    // Parse / Execute
}


} // end namespace cpps

