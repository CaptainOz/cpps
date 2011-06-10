/**
 * @file
 *
 * @brief Contains the Token class description.
 *
 * @author Nate Lillich
 */

#ifndef __CPPS_TOKEN_H_INCLUDED__
#define __CPPS_TOKEN_H_INCLUDED__

#include <string>
#include <vector>

#include "Exceptions.h"

namespace cpps
{

//! Class for the first-pass of parsing code.
/**
 * Each Token is an individual lexeme extracted from a source file. The public
 * static member Token::tokenize is a Token factory that generates tokens from
 * source code. It is the intended way to create Tokens.
 */
class Token
{
public:

    //! Enumeration of all possible token types.
    /**
     * @note
     * When updating this enumeration, also update the @c TypeNames, _keywords,
     * and _operators arrays defined in Token.cpp.
     *
     * These types are sorted by a combination of grouping and extraction order.
     * When adding or updating any token type make sure its regex match value
     * does not match the start of any of the types that follow it. For example,
     * LogicalOr (||) and AssignBitOr (|=) must both come before BitOr (|)
     * because BitOr starts both of them, however LogicalOr can come either
     * before or after AssignBitOr because neither is a substring of the other.
     */
    enum Type
    {
    //  Token type          Regex to match          detection   extraction

        // *** Begin Miscelaneous Token Types *** //
        TypeName,        // [a-zA-Z_]\w*            DONE        DONE
        Variable,        // \$[a-zA-Z_]\w*          DONE        DONE
        StringLiteral,   // (['"]).*?(?<!\\)\1      DONE        DONE
        NumericLiteral,  // (?i:[1-9]\d*|\d+\.\d*|0[0-7]*|0x[\da-f]+|0b[01]+)
                         //                         DONE        DONE
        CommentLine,     // \/\/[^\n]*              DONE        DONE
        CommentBlock,    // \/\*.*?\*\/             DONE        DONE
        RegexMatch,      // \/.*(?<!\\)\/
        // *** End Miscelaneous Token Types *** //

        // *** Begin Non-Overloadable Operators *** //
        Scope,           // ::                      DONE        DONE
        Semicolon,       // ;                       DONE        DONE
        Colon,           // :                       DONE        DONE
        Comma,           // ,                       DONE        DONE
        LogicalOr,       // \|\|                    DONE        DONE
        LogicalAnd,      // &&                      DONE        DONE
        TernaryIf,       // \?                      DONE        DONE
        OpenBrace,       // \{                      DONE        DONE
        CloseBrace,      // \}                      DONE        DONE
        // *** End Non-Overloadable Operators *** //

        // *** Begin Overloadable Operators *** //
        OpenParen,       // \(                      DONE        DONE
        CloseParen,      // \)                      DONE        DONE
        OpenBracket,     // \[                      DONE        DONE
        CloseBracket,    // \]                      DONE        DONE
        Equality,        // ==                      DONE        DONE
        NotEquality,     // !=                      DONE        DONE
        GreaterEqual,    // >=                      DONE        DONE
        LessEqual,       // <=                      DONE        DONE
        Assign,          // =                       DONE        DONE
        AssignPlus,      // \+=                     DONE        DONE
        AssignMinus,     // -=                      DONE        DONE
        AssignConcat,    // .=                      DONE        DONE
        AssignMultiply,  // \*=                     DONE        DONE
        AssignDivide,    // \/=                     DONE        DONE
        AssignModulo,    // %=                      DONE        DONE
        AssignBitAnd,    // &=                      DONE        DONE
        AssignBitXOr,    // \^=                     DONE        DONE
        AssignBitOr,     // \|=                     DONE        DONE
        AssignLeftShift, // <<=                     DONE        DONE
        AssignRightShift,// >>=                     DONE        DONE
        RighShift,       // >>                      DONE        DONE
        LeftShift,       // <<                      DONE        DONE
        Increment,       // \+\+                    DONE        DONE
        Decrement,       // --                      DONE        DONE
        MemberAccess,    // ->                      DONE        DONE
        GreaterThan,     // >                       DONE        DONE
        LessThan,        // <                       DONE        DONE
        Plus,            // \+                      DONE        DONE
        Minus,           // -                       DONE        DONE
        Multiply,        // \*                      DONE        DONE
        Divide,          // \/                      DONE        DONE
        Modulo,          // %                       DONE        DONE
        Concat,          // \.                      DONE        DONE
        LogicalNot,      // !                       DONE        DONE
        BitwiseNot,      // ~                       DONE        DONE
        BitwiseAnd,      // &                       DONE        DONE
        BitwiseXOr,      // \^                      DONE        DONE
        BitwiseOr,       // \|                      DONE        DONE
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
    }; // end Token::Type

    //! Array of token type-names suitable for human consumption.
    static const char* TypeNames[];

    //! A list of tokens as generated by the Token::tokenize static method.
    typedef std::vector<Token*> List;

    //! Converts source code into a list of Token objects.
    /**
     * @throws ParseException under any circumstance where tokenization would
     *         fail. For more specifics see the Token::_extract* methods.
     *
     * @param code The source code to tokenize.
     *
     * @return A list of Token objects extracted from the source code.
     */
    static Token::List tokenize( const std::string& code ) throw( ParseException );

    const Token::Type& getType( void ) const;
    const std::string& getTypeString( void ) const;
    const std::string& getString( void ) const;
    const unsigned int& getLineNUmber( void ) const;

private:
    const std::string mTokenStr;
    const Token::Type mType;
    const unsigned int mLineNumber;

    //! Array of keyword strings as they should appear in the code.
    static const char* _keywords[];

    //! Array of operator strings as they should appear in the code.
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
        ) throw();

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
        ) throw();

    //! Extracts a quoted string.
    /**
     * @throws ParseException if a newline or end of file is encountered before
     *         the end of the line.
     *
     * @param code       The plain code string to extract from.
     * @param pos        The starting point to extract the string.
     * @param lineNumber The line number the token is on.
     *
     * @return The extracted string literal token.
     */
    static Token* _extractString(
            const std::string&  code,
                  int&          pos,
            const unsigned int& lineNumber
        ) throw( ParseException );

    //! Extracts a number.
    /**
     * @throws ParseException if the number contains illegal characters.
     *
     * @param code       The plain code string to extract from.
     * @param pos        The starting point to extract the number.
     * @param lineNumber The line number the token is on.
     *
     * @return The extracted numeric literal token.
     */
    static Token* _extractNumber(
            const std::string&  code,
                  int&          pos,
            const unsigned int& lineNumber
        ) throw( ParseException );

    //! Extracts an identifier for a variable or typename.
    /**
     * @throws ParseException if the identifier contains illegal characters.
     *
     * @param code       The plain code string to extract from.
     * @param pos        The starting point to extract the identifier.
     * @param lineNumber The line number the token is on.
     *
     * @return The extracted identifier token.
     */
    static Token* _extractIdentifier(
            const std::string&  code,
                  int&          pos,
            const unsigned int& lineNumber
        ) throw( ParseException );

    //! Extracts a single-line comment.
    /**
     * @param code       The plain code string to extract from.
     * @param pos        The starting point to extract the comment.
     * @param lineNumber The line number the token is on.
     */
    static void _extractCommentLine(
            const std::string&  code,
                  int&          pos,
            const unsigned int& lineNumber
        ) throw();

    //! Extracts a block comment.
    /**
     * @throws ParseException if the comment block is not closed.
     *
     * @param code       The plain code string to extract from.
     * @param pos        The starting point to extract the comment.
     * @param lineNumber The line number the token is on.
     */
    static void _extractCommentBlock(
            const std::string&  code,
                  int&          pos,
                  unsigned int& lineNumber
        ) throw( ParseException );

    //! Extracts the given keyword.
    /**
     * @param code         The plain code string to extract from.
     * @param pos          The starting point to extract the keyword.
     * @param keywordIndex The index of the keyword from the Token::_keywords
     *                     array to extract.
     * @param lineNumber   The line number the token is on.
     *
     * @return The extracted keyword token.
     */
    static Token* _extractKeyword(
            const std::string&  code,
                  int&          pos,
            const int&          keywordIndex,
            const unsigned int& lineNumber
        ) throw();

    //! Extracts the given operator.
    /**
     * @param code          The plain code string to extract from.
     * @param pos           The starting point to extract the operator.
     * @param operatorIndex The index of the keyword from the Token::_operators
     *                      array to extract.
     * @param lineNumber    The line number the token is on.
     *
     * @return The extracted keyword token.
     */
    static Token* _extractOperator(
            const std::string&  code,
                  int&          pos,
            const int&          operatorIndex,
            const unsigned int& lineNumber
        ) throw();

    //! Private token constructor used by Token::tokenize.
    /**
     * @param type          The type of token this is.
     * @param lineNumber    The line number the token was extracted from.
     * @param tokenStr      The extract string taken from the source file.
     *
     * @note The @p tokenStr is only required for TypeName, Variable,
     *       StringLiteral, and NumericLiteral tokens. All other token types
     *       have well-defined representations.
     */
    Token(
            const Token::Type&  type,
            const unsigned int& lineNumber,
            const std::string&  tokenStr = ""
        ) throw();

}; // end class Token


/******************************************************************************/


inline const Token::Type& Token::getType( void ) const
{
    return mType;
}


/******************************************************************************/


inline const std::string& Token::getTypeString( void ) const
{
    return Token::TypeNames[ getType() ];
}


/******************************************************************************/


inline const std::string& Token::getString( void ) const
{
    return mTokenStr;
}


/******************************************************************************/


inline const unsigned int& Token::getLineNumber( void ) const
{
    return mLineNumber;
}


} // end namespace cpps

#endif // __CPPS_TOKEN_H_INCLUDED__

