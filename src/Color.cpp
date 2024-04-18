/*
 * @Author: Reina__
 * @Date: 2024-04-18 13:43:57
 * @Last Modified by: Reina__
 * @Last Modified time: 2024-04-18 16:31:18
 */
#include "Color.h"

const std::string red("\033[1;31m");
const std::string green("\033[1;32m");
const std::string white("\033[1;4;30;47m");
const std::string yellow("\033[1;33m");
const std::string cyan("\033[1;36m");
const std::string reset("\033[0m");


void Color_out(const std::string &color, const std::string &str)
{
    std::cout << color << str << reset << std::endl;
}

