//
// Created by ake on 01.04.2020.
//

#ifndef TEXY_TEXYINTERPRETER_HPP
#define TEXY_TEXYINTERPRETER_HPP

#include "Commands.hpp"
#include "Global.hpp"
#include "Variables.hpp"
#include <deque>
#include <map>
#include <string>
#include <string_view>
#include <vector>

class Interpreter
{
public:
    Interpreter();
    void Interpret( std::string_view code, Stack& stack );
    Symbols Parse( std::string_view code );
    void Evaluate( const Symbols& symbols, Stack& stack );
    void ExecuteCommand( const std::string_view& command, Stack& stack );
    Variables& GetVariables() { return m_variables; }
    void DumpStack( Stack& stack );

private:
    Commands m_commands;
    Variables m_variables;
};

#endif //TEXY_TEXYINTERPRETER_HPP
