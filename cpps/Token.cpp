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
        "RightShift",      // >>
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

typedef std::pair< Token::Type, ParserBase::Tokens__ > TokenPair;
const std::map< Token::Type, ParserBase::Tokens__ > Token::_conversion = {
    TokenPair( Token::TypeName,          ParserBase::TypeName ),
    TokenPair( Token::Variable,          ParserBase::Variable ),
    TokenPair( Token::StringLiteral,     ParserBase::StringLiteral ),
    TokenPair( Token::NumericLiteral,    ParserBase::NumericLiteral ),
//  TokenPair( Token::CommentLine,       ParserBase::CommentLine ),
//  TokenPair( Token::CommentBlock,      ParserBase::CommentBlock ),
//  TokenPair( Token::RegexMatch,        ParserBase::RegexMatch ),
//  TokenPair( Token::Scope,             ParserBase::Scope ),
    TokenPair( Token::Semicolon,         ParserBase::Semicolon ),
    TokenPair( Token::Colon,             ParserBase::Colon ),
    TokenPair( Token::Comma,             ParserBase::Comma ),
    TokenPair( Token::LogicalOr,         ParserBase::LogicalOr ),
    TokenPair( Token::LogicalAnd,        ParserBase::LogicalAnd ),
    TokenPair( Token::TernaryIf,         ParserBase::TernaryIf ),
    TokenPair( Token::OpenBrace,         ParserBase::OpenBrace ),
    TokenPair( Token::CloseBrace,        ParserBase::CloseBrace ),
    TokenPair( Token::OpenParen,         ParserBase::OpenParen ),
    TokenPair( Token::CloseParen,        ParserBase::CloseParen ),
    TokenPair( Token::OpenBracket,       ParserBase::OpenBracket ),
    TokenPair( Token::CloseBracket,      ParserBase::CloseBracket ),
    TokenPair( Token::Equality,          ParserBase::Equality ),
    TokenPair( Token::NotEquality,       ParserBase::NotEquality ),
    TokenPair( Token::GreaterEqual,      ParserBase::GreaterEqual ),
    TokenPair( Token::LessEqual,         ParserBase::LessEqual ),
    TokenPair( Token::Assign,            ParserBase::Assign ),
    TokenPair( Token::AssignPlus,        ParserBase::AssignPlus ),
    TokenPair( Token::AssignMinus,       ParserBase::AssignMinus ),
    TokenPair( Token::AssignConcat,      ParserBase::AssignConcat ),
    TokenPair( Token::AssignMultiply,    ParserBase::AssignMultiply ),
    TokenPair( Token::AssignDivide,      ParserBase::AssignDivide ),
    TokenPair( Token::AssignModulo,      ParserBase::AssignModulo ),
    TokenPair( Token::AssignBitAnd,      ParserBase::AssignBitAnd ),
    TokenPair( Token::AssignBitXOr,      ParserBase::AssignBitXOr ),
    TokenPair( Token::AssignBitOr,       ParserBase::AssignBitOr ),
    TokenPair( Token::AssignLeftShift,   ParserBase::AssignLeftShift ),
    TokenPair( Token::AssignRightShift,  ParserBase::AssignRightShift ),
    TokenPair( Token::Increment,         ParserBase::Increment ),
    TokenPair( Token::Decrement,         ParserBase::Decrement ),
    TokenPair( Token::LogicalNot,        ParserBase::LogicalNot ),
    TokenPair( Token::BitwiseNot,        ParserBase::BitwiseNot ),
    TokenPair( Token::RightShift,        ParserBase::RightShift ),
    TokenPair( Token::LeftShift,         ParserBase::LeftShift ),
    TokenPair( Token::MemberAccess,      ParserBase::MemberAccess ),
    TokenPair( Token::GreaterThan,       ParserBase::GreaterThan ),
    TokenPair( Token::LessThan,          ParserBase::LessThan ),
    TokenPair( Token::Plus,              ParserBase::Plus ),
    TokenPair( Token::Minus,             ParserBase::Minus ),
    TokenPair( Token::Multiply,          ParserBase::Multiply ),
    TokenPair( Token::Divide,            ParserBase::Divide ),
    TokenPair( Token::Modulo,            ParserBase::Modulo ),
    TokenPair( Token::Concat,            ParserBase::Concat ),
    TokenPair( Token::BitwiseAnd,        ParserBase::BitwiseAnd ),
    TokenPair( Token::BitwiseXOr,        ParserBase::BitwiseXOr ),
    TokenPair( Token::BitwiseOr,         ParserBase::BitwiseOr ),

//  TokenPair( Token::Break,             ParserBase::Break ),
//  TokenPair( Token::Case,              ParserBase::Case ),
//  TokenPair( Token::Catch,             ParserBase::Catch ),
//  TokenPair( Token::Class,             ParserBase::Class ),
//  TokenPair( Token::Const,             ParserBase::Const ),
//  TokenPair( Token::Continue,          ParserBase::Continue ),
//  TokenPair( Token::Default,           ParserBase::Default ),
    TokenPair( Token::Delete,            ParserBase::Delete ),
//  TokenPair( Token::Do,                ParserBase::Do ),
//  TokenPair( Token::Else,              ParserBase::Else ),
//  TokenPair( Token::Enum,              ParserBase::Enum ),
//  TokenPair( Token::False,             ParserBase::False ),
//  TokenPair( Token::For,               ParserBase::For ),
//  TokenPair( Token::Foreach,           ParserBase::Foreach ),
//  TokenPair( Token::Friend,            ParserBase::Friend ),
//  TokenPair( Token::Function,          ParserBase::Function ),
//  TokenPair( Token::If,                ParserBase::If ),
//  TokenPair( Token::Include,           ParserBase::Include ),
//  TokenPair( Token::InstanceOf,        ParserBase::InstanceOf ),
//  TokenPair( Token::Namespace,         ParserBase::Namespace ),
    TokenPair( Token::New,               ParserBase::New ),
//  TokenPair( Token::Null,              ParserBase::Null ),
//  TokenPair( Token::Operator,          ParserBase::Operator ),
//  TokenPair( Token::Private,           ParserBase::Private ),
//  TokenPair( Token::Protected,         ParserBase::Protected ),
//  TokenPair( Token::Public,            ParserBase::Public ),
//  TokenPair( Token::Return,            ParserBase::Return ),
    TokenPair( Token::SizeOf,            ParserBase::SizeOf ),
//  TokenPair( Token::Static,            ParserBase::Static ),
//  TokenPair( Token::Struct,            ParserBase::Struct ),
//  TokenPair( Token::Switch,            ParserBase::Switch ),
//  TokenPair( Token::This,              ParserBase::This ),
    TokenPair( Token::Throw,             ParserBase::Throw ),
//  TokenPair( Token::True,              ParserBase::True ),
//  TokenPair( Token::Try,               ParserBase::Try ),
//  TokenPair( Token::TypeDef,           ParserBase::TypeDef ),
    TokenPair( Token::TypeNameOperator,  ParserBase::TypeNameOperator ),
//  TokenPair( Token::Union,             ParserBase::Union ),
//  TokenPair( Token::Using,             ParserBase::Using ),
//  TokenPair( Token::While,             ParserBase::While ),
//  TokenPair( Token::Var,               ParserBase::Var ),
};


} // end namespace cpps

