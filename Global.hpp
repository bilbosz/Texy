//
// Created by ake on 02.04.2020.
//

#ifndef TEXY_GLOBAL_HPP
#define TEXY_GLOBAL_HPP

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using Symbols = std::vector< std::string_view >;
using Stack = std::vector< std::string >;
using CommandExecutable = std::function< void( Stack& ) >;

inline void Dummy() {};

#endif //TEXY_GLOBAL_HPP
