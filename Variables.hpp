//
// Created by ake on 02.04.2020.
//

#ifndef TEXY_VARIABLES_HPP
#define TEXY_VARIABLES_HPP

#include "Global.hpp"
#include <string_view>
class TexyInterpreter;

class Variables
{
public:
    void Set( std::string_view name, std::string_view value );
    std::string Get( std::string_view name );
    void Remove( std::string_view name );

private:
    std::map< std::string, std::string, std::less<> > m_registred;
};

#endif //TEXY_VARIABLES_HPP
