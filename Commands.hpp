//
// Created by ake on 01.04.2020.
//

#ifndef TEXY_COMMANDS_HPP
#define TEXY_COMMANDS_HPP

#include "Global.hpp"

class Interpreter;

class Commands
{
public:
    explicit Commands( Interpreter* interpreter );
    CommandExecutable Get( std::string_view name );

private:
    void Set( Stack& stack );
    void Do( Stack& stack );
    void Get( Stack& stack );
    void Ref( Stack& stack );
    void Lt( Stack& stack );
    void If( Stack& stack );
    void Pick( Stack& stack );
    void Add( Stack& stack );
    void Print( Stack& stack );
    void DoFile( Stack& stack );

    std::map< std::string, CommandExecutable, std::less<> > m_registred;
    Interpreter* m_interpreter;
};

#endif //TEXY_COMMANDS_HPP
