/**
 *
 */

#ifndef __CPPS_TOKEN_H_INCLUDED__
#define __CPPS_TOKEN_H_INCLUDED__

#include <string>
#include <vector>

namespace cpps
{

class Token
{
public:

    //! Enumeration of all possible token types.
    /**
     * @note
     * When updating this enumeration, also update the @c TypeNames array
     * defined in Token.cpp.
     */
    enum Type
    {
    //  Token type          Regex to match          detection   extraction

        // *** Begin Miscelaneous Token Types *** //
        TypeName,        // [a-zA-Z_]\w*            DONE
        Identifier,      // \$[a-zA-Z_]\w*          DONE
        StringLiteral,   // (['"]).*?(?<!\\)\1      DONE        DONE
        NumericLiteral,  // (?:\d+|\d*\.\d+)d?      DONE
        CommentLine,     // \/\/[^\n]*              DONE
        CommentBlock,    // \/\*.*?\*\/             DONE
        RegexMatch,      // \/.*(?<!\\)\/
        // *** End Miscelaneous Token Types *** //

        // *** Begin Non-Overloadable Operators *** //
        Scope,           // ::                      DONE
        Semicolon,       // ;                       DONE
        Colon,           // :                       DONE
        Comma,           // ,                       DONE
        LogicalOr,       // \|\|                    DONE
        LogicalAnd,      // &&                      DONE
        TernaryIf,       // \?                      DONE
        OpenBrace,       // \{                      DONE
        CloseBrace,      // \}                      DONE
        // *** End Non-Overloadable Operators *** //

        // *** Begin Overloadable Operators *** //
        OpenParen,       // \(                      DONE
        CloseParen,      // \)                      DONE
        OpenBracket,     // \[                      DONE
        CloseBracket,    // \]                      DONE
        Equality,        // ==                      DONE
        NotEquality,     // !=                      DONE
        GreaterEqual,    // >=                      DONE
        LessEqual,       // <=                      DONE
        Assign,          // =                       DONE
        AssignPlus,      // \+=                     DONE
        AssignMinus,     // -=                      DONE
        AssignConcat,    // .=                      DONE
        AssignMultiply,  // \*=                     DONE
        AssignDivide,    // \/=                     DONE
        AssignModulo,    // %=                      DONE
        AssignBitAnd,    // &=                      DONE
        AssignBitXOr,    // \^=                     DONE
        AssignBitOr,     // |=                      DONE
        AssignLeftShift, // <<=                     DONE
        AssignRightShift,// >>=                     DONE
        RighShift,       // >>                      DONE
        LeftShift,       // <<                      DONE
        Increment,       // \+\+                    DONE
        Decrement,       // --                      DONE
        MemberAccess,    // ->                      DONE
        GreaterThan,     // >                       DONE
        LessThan,        // <                       DONE
        Plus,            // \+                      DONE
        Minus,           // -                       DONE
        Multiply,        // \*                      DONE
        Divide,          // \/                      DONE
        Modulo,          // %                       DONE
        Concat,          // \.                      DONE
        LogicalNot,      // !                       DONE
        BitwiseNot,      // ~                       DONE
        BitwiseAnd,      // &                       DONE
        BitwiseXOr,      // \^                      DONE
        BitwiseOr,       // \|                      DONE
        // *** End Overloadable Operators *** //

        // *** Begin Keywords *** //
        Break,           // break                   DONE
        Case,            // case                    DONE
        Catch,           // catch                   DONE
        Class,           // class                   DONE
        Const,           // const                   DONE
        Continue,        // continue                DONE
        Default,         // default                 DONE
        Delete,          // delete                  DONE
        Do,              // do                      DONE
        Else,            // else                    DONE
        Enum,            // enum                    DONE
        False,           // false                   DONE
        For,             // for                     DONE
        Foreach,         // foreach                 DONE
        Friend,          // friend                  DONE
        Function,        // function                DONE
        If,              // if                      DONE
        Include,         // include                 DONE
        InstanceOf,      // instanceof              DONE
        Namespace,       // namespace               DONE
        New,             // new                     DONE
        Null,            // null                    DONE
        Operator,        // operator                DONE
        Private,         // private                 DONE
        Protected,       // protected               DONE
        Public,          // public                  DONE
        Return,          // return                  DONE
        SizeOf,          // sizeof                  DONE
        Static,          // static                  DONE
        Struct,          // struct                  DONE
        Switch,          // switch                  DONE
        This,            // this                    DONE
        Throw,           // throw                   DONE
        True,            // true                    DONE
        Try,             // try                     DONE
        TypeDef,         // typedef                 DONE
        TypeNameOperator,// typename                DONE
        Union,           // union                   DONE
        Using,           // using                   DONE
        While,           // while                   DONE
        Var,             // var                     DONE
        // *** End Keywords *** //

        TokenTypeCount
    };

    //! Array of token type-names suitable for human consumption.
    static const char* TypeNames[];

    //! A list of tokens as generated by the Token::tokenize static method.
    typedef std::vector<Token> List;

    static Token::List tokenize( const std::string& code );

private:
    const std::string mTokenStr;
    const Token::Type mType;
    const unsigned int mLineNumber;
    static const char* _keywords[];
    static const char* _operators[];

    //! Detects if the @p code at the given @p position matches the @p keyword.
    /**
     * This is different from Token::_matchToken in that it does an additional
     * check that the character following the keyword is not alphanumeric or an
     * underscore.
     *
     * @param code    The plain code string to read.
     * @param pos     The position to start the comparison at.
     * @param keyword The keyword to compare it to.
     *
     * @return True if the following code chunk is the given keyword.
     */
    static bool _matchKeyword(
            const std::string& code,
            const int&         pos,
            const char*        keyword
        );

    //! Detects if the @p code at the given @p position matches the @p token.
    /**
     * @param code  The plain code string to read.
     * @param pos   The position to start the comparison at.
     * @param token The token to compare it to.
     *
     * @return True if the following code chunk is the given token.
     */
    static bool _matchToken(
            const std::string& code,
            const int&         pos,
            const char*        token
        );

    static Token _extractString(
            const std::string&  code,
                  int&          pos,
            const unsigned int& lineNumber );

public:
    Token(
            const Token::Type&  type,
            const std::string&  tokenStr,
            const unsigned int& lineNumber
        );

}; // end class Token

} // end namespace cpps

#endif // __CPPS_TOKEN_H_INCLUDED__

