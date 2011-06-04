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
        Identifier,      // \$[a-zA-Z_]\w*          DONE        DONE
        StringLiteral,   // (['"]).*?(?<!\\)\1      DONE        DONE
        NumericLiteral,  // (?i:[1-9]\d*|\d+\.\d*|0[0-7]*|0x[\da-f]+|0b[01]+)
                         //                         DONE        DONE
        CommentLine,     // \/\/[^\n]*              DONE        DONE
        CommentBlock,    // \/\*.*?\*\/             DONE        DONE
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
        Break,           // break                   DONE        DONE
        Case,            // case                    DONE        DONE
        Catch,           // catch                   DONE        DONE
        Class,           // class                   DONE        DONE
        Const,           // const                   DONE        DONE
        Continue,        // continue                DONE        DONE
        Default,         // default                 DONE        DONE
        Delete,          // delete                  DONE        DONE
        Do,              // do                      DONE        DONE
        Else,            // else                    DONE        DONE
        Enum,            // enum                    DONE        DONE
        False,           // false                   DONE        DONE
        For,             // for                     DONE        DONE
        Foreach,         // foreach                 DONE        DONE
        Friend,          // friend                  DONE        DONE
        Function,        // function                DONE        DONE
        If,              // if                      DONE        DONE
        Include,         // include                 DONE        DONE
        InstanceOf,      // instanceof              DONE        DONE
        Namespace,       // namespace               DONE        DONE
        New,             // new                     DONE        DONE
        Null,            // null                    DONE        DONE
        Operator,        // operator                DONE        DONE
        Private,         // private                 DONE        DONE
        Protected,       // protected               DONE        DONE
        Public,          // public                  DONE        DONE
        Return,          // return                  DONE        DONE
        SizeOf,          // sizeof                  DONE        DONE
        Static,          // static                  DONE        DONE
        Struct,          // struct                  DONE        DONE
        Switch,          // switch                  DONE        DONE
        This,            // this                    DONE        DONE
        Throw,           // throw                   DONE        DONE
        True,            // true                    DONE        DONE
        Try,             // try                     DONE        DONE
        TypeDef,         // typedef                 DONE        DONE
        TypeNameOperator,// typename                DONE        DONE
        Union,           // union                   DONE        DONE
        Using,           // using                   DONE        DONE
        While,           // while                   DONE        DONE
        Var,             // var                     DONE        DONE
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
            const unsigned int& lineNumber
        );

    static Token _extractNumber(
            const std::string&  code,
                  int&          pos,
            const unsigned int& lineNumber
        );

    static Token _extractIdentifier(
            const std::string&  code,
                  int&          pos,
            const unsigned int& lineNumber
        );

    static void _extractCommentLine(
            const std::string&  code,
                  int&          pos,
            const unsigned int& lineNumber
        );

    static void _extractCommentBlock(
            const std::string&  code,
                  int&          pos,
                  unsigned int& lineNumber
        );

    static Token _extractKeyword(
            const std::string&  code,
                  int&          pos,
            const int&          keywordIndex
            const unsigned int& lineNumber
        );

public:
    Token(
            const Token::Type&  type,
            const std::string&  tokenStr,
            const unsigned int& lineNumber
        );

}; // end class Token

} // end namespace cpps

#endif // __CPPS_TOKEN_H_INCLUDED__

