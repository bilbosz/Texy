//
// Created by ake on 02.04.2020.
//

#include "Variables.hpp"

void Variables::Set( std::string_view name, std::string_view value )
{
    m_registred.insert( std::make_pair( name, value ) );
}

std::string Variables::Get( std::string_view name )
{
    auto it = m_registred.find( name );
    assert( it != m_registred.cend() );
    return it->second;
}

void Variables::Remove( std::string_view name )
{
    auto it = m_registred.find( name );
    assert( it != m_registred.cend() );
    m_registred.erase( it );
}
