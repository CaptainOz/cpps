/**
 * @file Scope.h
 *
 * @brief Describes the Scope class.
 *
 * @author Nate Lillich
 */

#ifndef __CPPS_SCOPE_H_INCLUDED__
#define __CPPS_SCOPE_H_INCLUDED__

#include <list>
#include <map>
#include <stack>
#include <string>
#include <vector>

#include "AbstractSyntaxTree.h"
#include "Function.h"
#include "Scriptable.h"

namespace cpps
{

class Scope : public Scriptable
{
private:
    typedef std::map< std::string, Scope* > ScopeMap;
//    typedef std::map< std::string, Function* > FunctionMap;
    typedef std::map< std::string, Scriptable* > ScriptableMap;

    Scope*        m_parentScope;
    ScopeMap      m_namespaces;
//    FunctionMap   m_functions;
    ScriptableMap m_variables;
    AbstractSyntaxTree m_statements;

    /// Flag indicating if code should be executed as it added to the scope.
    const bool m_liveExecution;

public:
    Scope( const bool& liveExecution = false );

    void addStatement( AbstractSyntaxTree::Node* statement );
}; // end class Scope


/*****************************************************************************/


inline Scope::Scope( const bool& liveExecution )
    : m_liveExecution( liveExecution )
{
}


} // end namespace cpps

#endif // __CPPS_SCOPE_H_INCLUDED__

