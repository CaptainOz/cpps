/**
 * @file
 *
 * @brief Describes Scope::Node subclasses.
 *
 * @author Nate Lillich
 */

#ifndef __CPPS_NODES_H_INCLUDED__
#define __CPPS_NODES_H_INCLUDED__

#include <string>
#include <vector>

#include "Object.h"
#include "Scope.h"

namespace cpps
{


//! This namespace contains all the Scope::Node subclasses.
namespace nodeTypes
{

//! TypeName holds a reference to a class or function.
class TypeName : public Scope::Node
{
private:
    const std::string& typeNameStr;

public
    virtual Scriptable::Reference getValue( Scriptable::Reference args );
}; // end class TypeName


/******************************************************************************/


//! Variables holds a reference to a single variable.
class Variable : public Scope::Node
{
private:
    const std::string& variableName;

public
    virtual Scriptable::Reference getValue( Scriptable::Reference args );
}; // end class Variable


/******************************************************************************/


//! StringLiterals hold the value of a quoted string. They are like variables,
//! but unvarying.
class StringLiteral : public Scope::Node
{
private:
    const std::string& value;

public:
    virtual Scriptable::Reference getValue( Scriptable::Reference args );
}; // end class StringLiteral


/******************************************************************************/


//! CodeBlocks contain other statements to be executed.
class CodeBlock : public Scope::Node
{
private:
    const StatementList& statements;

public:
    virtual Scriptable::Reference getValue( Scriptable::Reference args );
}; // end class CodeBlock


/******************************************************************************/


//! UnaryOperators are any operator which take only one operand.
class UnaryOperator : public Scope::Node
{
private:
    Scope::Node* operand;

protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& operand,
            Scriptable::Reference args
        ) = 0;

public:
    virtual Scriptable::Reference getValue( Scriptable::Reference args );

    void setOperand( Scope::Node* node );
}; // end class UnaryOperand


/******************************************************************************/


//! BinaryOperators are any operators which take two operands.
class BinaryOperator : public Scope::Node
{
private:
    Scope::Node* leftOperand;
    Scope::Node* rightOperand;

protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        ) = 0;

public:
    virtual Scriptable::Reference getValue( Scriptable::Reference args );

    void setLeftOperand( Scope::Node* node );
    void setRightOperand( Scope::Node* node );
}; // end class BinaryOperator


/******************************************************************************/


//! TernaryOperators are any operators which take three operands.
class TernaryOperator : public Scope::Node
{
private:
    Scope::Node* leftOperand;
    Scope::Node* middleOperand;
    Scope::Node* rightOperand;

protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& middleOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        ) = 0;

public:
    virtual Scriptable::Reference getValue( Scriptable::Reference args );
    
    void setLeftOperand( Scope::Node* node );
    void setMiddleOperand( Scope::Node* node );
    void setRightOperand( Scope::Node* node );
}; // end class TernaryOperator


/******************************************************************************/


//! ScopeOperator resolves a reference to one within the given scope.
class ScopeOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class ScopeOperator


/******************************************************************************/


//! LogicalOrOperator is true if either of its operands are true.
class LogicalOrOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class LogicalOrOperator


/******************************************************************************/


//! LogicalAndOperator is true if both of its operands are true.
class LogicalAndOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class LogicalAndOperator


/******************************************************************************/


//! InlineIfOperator acts like an if-then-else clause in only one statement.
class InlineIfOperator : public TernaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& middleOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class InlineIfOperator


/******************************************************************************/


//! FunctionOperator references another function by name.
class FunctionOperator : public UnaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& operand,
            Scriptable::Reference args
        );
}; // end class FunctionOperator


/******************************************************************************/


//! TypecastOperator converts one operand to the other's type.
class TypecastOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class TypecastOperator


/******************************************************************************/


//! IndexOperator indexes into the left operand using the right.
class IndexOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class IndexOperator


/******************************************************************************/


//! EqualityOperator is true if both operands are equal.
class EqualityOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class EqualityOperator


/******************************************************************************/


//! NotEqualityOperator is true if both operands are not equal.
class NotEqualityOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class NotEqualityOperator


/******************************************************************************/


//! GreaterEqualOperator is true if the left operand is greater than or equal to
//! the right operand.
class GreaterEqualOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class GreaterEqualOperator


/******************************************************************************/


//! LessEqualOperator is true if the left operand is less than or equal to the
//! right operand.
class LessEqualOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class LessEqualOperator


/******************************************************************************/


//! AssignOperator assigns the value of the right operand to the left.
class AssignOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class AssignOperator


/******************************************************************************/


//! AssignPlusOperator increments the value of the left operand by the value of
//! the right operand.
class AssignPlusOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class AssignPlusOperator


/******************************************************************************/


//! AssignMinusOperator decrements the value of the left operand by the value of
//! the right operand.
class AssignMinusOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class AssignMinusOperator


/******************************************************************************/


//! AssignConcatOperator appends the value of the right operand to the end of
//! the left operand.
class AssignConcatOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class AssignConcatOperator


/******************************************************************************/


//! AssignMultiplyOperator multiplies the value of the left operand by the value
//! of the right operand.
class AssignMultiplyOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class AssignMultiplyOperator


/******************************************************************************/


//! AssignDivideOperator divides the value of the left operand by the value of
//! the right operand.
class AssignDivideOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class AssignDivideOperator


/******************************************************************************/


//! AssignModuloOperator assigns the remainder of the left operand divided by
//! the right to the left operand.
class AssignModuloOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class AssignModuloOperator


/******************************************************************************/


//! AssignBitAndOperator assigns the bitwise combinations of the operands to the
//! left operand.
class AssignBitAndOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class AssignBitAndOperator


/******************************************************************************/


//! AssignBitXOrOperator assigns the bitwise exclusive or of the operands to the
//! left operand.
class AssignBitXOrOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class AssignBitXOrOperator


/******************************************************************************/


//! AssignBitOrOperator assigns the bitwise or of the operands to the left one.
class AssignBitOrOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class AssignBitOrOperator


/******************************************************************************/


//! AssignLeftShiftOperator shifts the value of the left operand by the value of
//! the right operand.
class AssignLeftShiftOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class AssignLeftShiftOperator


/******************************************************************************/


//! AssignRightShiftOperator shifts the value of the left operand by the value
//! of the right operand.
class AssignRightShiftOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class AssignRightShiftOperator


/******************************************************************************/


//! RightShiftOperator returns the value of the left operand shifted right by
//! the right operand.
class RightShiftOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class RightShiftOperator


/******************************************************************************/


//! LeftShiftOperator returns the value of the left operand shifted left by the
//! right operand.
class LeftShiftOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class LeftShiftOperator


/******************************************************************************/


//! PreIncrementOperator increments the value of the operand by one.
class PreIncrementOperator : public UnaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& operand,
            Scriptable::Reference args
        );
}; // end class PreIncrementOperator


/******************************************************************************/


//! PostIncrementOperator increments the value of the operand by one and returns
//! the original value.
class PostIncrementOperator : public UnaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& operand,
            Scriptable::Reference args
        );
}; // end class PostIncrementOperator


/******************************************************************************/


//! PreDecrementOperator decrements the value of the operand by one.
class PreDecrementOperator : public UnaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& operand,
            Scriptable::Reference args
        );
}; // end class PreDecrementOperator


/******************************************************************************/


//! PostDecrementOperator decrements the value of the operand by one and returns
//! the original value.
class PostDecrementOperator : public UnaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& operand,
            Scriptable::Reference args
        );
}; // end class PostDecrementOperator


/******************************************************************************/


//! MemberAccessOperator accesses a single member of the left operand with the
//! value of the right operand.
class MemberAccessOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class MemberAccessOperator


/******************************************************************************/


//! GreaterThanOperator is true if the left operand is greater than the right.
class GreaterThanOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class GreaterThanOperator


/******************************************************************************/


//! LessThanOperator is true if the left operand is less than the right.
class LessThanOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class LessThanOperator


/******************************************************************************/


//! PlusOperator returns the sum of the left and right operands.
class PlusOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class PlusOperator


/******************************************************************************/


//! MinusOperator returns the difference of the left and right operands.
class MinusOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class MinusOperator


/******************************************************************************/


//! NegativeOperator returns the opposite value of its operand.
class NegativeOperator : public UnaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& operand,
            Scriptable::Reference args
        );
}; // end class NegativeOperator


/******************************************************************************/


//! MultiplyOperator returns the product of the left and right operands.
class MultiplyOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class MultiplyOperator


/******************************************************************************/


//! DivideOperator returns the quotient of the left and right operands.
class DivideOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class DivideOperator


/******************************************************************************/


//! ModuloOperator returns the remainder of the left operand divided by the
//! right operand.
class ModuloOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class ModuloOperator


/******************************************************************************/


//! ConcatOperator returns the right operand appended to the end of the left.
class ConcatOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class ConcatOperator


/******************************************************************************/


//! LogicalNotOperator is true if its operand is false.
class LogicalNotOperator : public UnaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& operand,
            Scriptable::Reference args
        );
}; // end class LogicalNotOperator


/******************************************************************************/


//! BitwiseNotOperator returns the bitwise compliment to its operand.
class BitwiseNotOperator : public UnaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& operand,
            Scriptable::Reference args
        );
}; // end class BitwiseNotOperator


/******************************************************************************/


//! BitwiseAndOperator returns the bitwise and of the left and right operands.
class BitwiseAndOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class BitwiseAndOperator


/******************************************************************************/


//! ReferenceOperator returns a reference to its operand.
class ReferenceOperator : public UnaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& operand,
            Scriptable::Reference args
        );
}; // end class ReferenceOperator


/******************************************************************************/


//! BitwiseXOrOperator returns the bitwise exclusive-or of its operands.
class BitwiseXOrOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class BitwiseXOrOperator


/******************************************************************************/


//! BitwiseOrOperator returns the bitwise or of its operands.
class BitwiseOrOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class BitwiseOrOperator


/******************************************************************************/


//! BreakKeyword stops a loop or breaks out of a block of code.
class BreakKeyword : public Scope::Node
{
private:
    const std::string& value;

public:
    virtual Scriptable::Reference getValue( Scriptable::Reference args );
}; // end class BreakKeyword


/******************************************************************************/


//! ConstKeyword is used by TypeCast to make a variable reference constant.
class ConstKeyword : public Scope::Node
{
private:
    const std::string& value;

public:
    virtual Scriptable::Reference getValue( Scriptable::Reference args );
}; // end class ConstKeyword


/******************************************************************************/


//! ContinueKeyword stops the current iteration of a loop but doesn't stop the
//! loop from continuing.
class ContinueKeyword : public Scope::Node
{
private:
    const std::string& value;

public:
    virtual Scriptable::Reference getValue( Scriptable::Reference args );
}; // end class ContinueKeyword


/******************************************************************************/


//! DeleteOperator deletes its operand, freeing its resources.
class DeleteOperator : public UnaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& operand,
            Scriptable::Reference args
        );
}; // end class DeleteOperator


/******************************************************************************/


//! IncludeOperator includes an outside source file or library.
class IncludeOperator : public UnaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& operand,
            Scriptable::Reference args
        );
}; // end class IncludeOperator


/******************************************************************************/


//! InstanceOfOperator is true if the left operand is an instance of the right.
class InstanceOfOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class InstanceOfOperator


/******************************************************************************/


//! NewOperator initializes a new instance of its operand.
class NewOperator : public UnaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& operand,
            Scriptable::Reference args
        );
}; // end class NewOperator


/******************************************************************************/


//! ReturnOperator exits the function and returns the value of its operand.
class ReturnOperator : public UnaryOperator;
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& operand,
            Scriptable::Reference args
        );
}; // end class ReturnOperator


/******************************************************************************/


//! SizeOfOperator returns the amount of memory used by its operand in bytes.
class SizeOfOperator : public UnaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& operand,
            Scriptable::Reference args
        );
}; // end class SizeOfOperator


/******************************************************************************/


//! ThrowOperator throws its operand to the nearest try-catch in the stack.
class ThrowOperator : public UnaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& operand,
            Scriptable::Reference args
        );
}; // end class ThrowOperator


/******************************************************************************/


//! TypeDefOperator creates an alias to the left operand at the value of the
//! right operand.
class TypeDefOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& leftOperand,
            const Scope::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class TypeDefOperator


/******************************************************************************/


//! TypeNameOperator returns the name of the operands type as a string.
class TypeNameOperator : public UnaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const Scope::Node& operand,
            Scriptable::Reference args
        );
}; // end class TypeNameOperator


/******************************************************************************/


//! VarKeyword creates new variables.
class VarKeyword : public Scope::Node
{
private:
    const Statements variables;

public:
    virtual Scriptable::Reference getValue( Scriptable::Reference args );
}; // end class VarKeyword


} // end namespace nodeTypes


} // emd namespace cpps

#endif // __CPPS_NODES_H_INCLUDED__

