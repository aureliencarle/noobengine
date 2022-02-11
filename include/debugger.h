#pragma once
// Standard library
#include <string>
#include <iostream>

/**
 *
 */
inline void Log(std::string const &message)
{
    std::cout << message << std::endl;
}

template <typename T>
inline void Log(T const &object, std::string const &message = "log : ")
{
    std::cout << message << object << std::endl;
}

