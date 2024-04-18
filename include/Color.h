/*
 * @Author: Reina__
 * @Date: 2024-04-18 13:44:14
 * @Last Modified by: Reina__
 * @Last Modified time: 2024-04-18 16:31:32
 */
#ifndef COLOR_HPP
#define COLOR_HPP

#include <string>
#include <iostream>

extern const std::string red;
extern const std::string green;
extern const std::string white;
extern const std::string yellow;
extern const std::string cyan;
extern const std::string reset;

void Color_out(const std::string &color, const std::string &str);
#endif
