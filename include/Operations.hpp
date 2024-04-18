/*
 * @Author: Reina__
 * @Date: 2024-04-18 13:43:30
 * @Last Modified by: Reina__
 * @Last Modified time: 2024-04-18 21:10:41
 */
#ifndef OPERATOIONS_HPP
#define OPERATOIONS_HPP
#include "Menu.hpp"
#include "Matrix.h"
#include "Color.h"
#include "Evaluate.hpp"
// 输入函数,直到输入符合要求的名字
std::string Input_name()
{
    std::string name;
    auto check = [&](const std::string &s)
    {
        if (s.empty())
            return false;
        for (int i = 0; i < s.size(); ++i)
            if (!check_name(s[i], !i))
                return false;
        return true;
    };
    while (!(std::cin >> name && check(name)))
        Color_out(red, "求求你输入一个正常的名字吧,让我做什么我都是愿意的");
    return name;
}
// 增添了一层是否已经被记录的判断
std::string In_or_out()
{
    std::string name = Input_name();
    if (name != "exit" && Matset.count(name) == 0)
    {
        Color_out(red, "你输入的矩阵并不存在哦");
        return "";
    }
    return name;
}
//提问并收取回答的函数
bool Yes_yeah_Oh_no(std::string question)
{
    Color_out(green, question + "(Y/n)");
    while (true)
    {
        char c = getch();
        if (c == 'Y')
            return true;
        if (c == 'n')
            return false;
    }
}
//定义了一个输出初态和结果的函数
template <typename res>
void Output_name_result(std::string name, res result)
{
    std::cout << name << ":" << std::endl
              << Matset[name] << std::endl
              << "The result of " << name << " is:" << std::endl
              << result << std::endl;
}
//定义了一个视情况存储结果的函数
void Save_Matrix(Matrix result)
{
    if (result.empty())
        return;
    if (Yes_yeah_Oh_no("是否需要把结果存储到矩阵中?"))
    {
        Color_out(yellow, "输入矩阵的名称");
        std::string name = Input_name();
        Matset[name] = result;
    }
}
void Input_Matrix()
{
    Menu("输入矩阵", {"请先输入矩阵的名称(符合C/C++变量命名标准的)", "再输入矩阵的实际值", "矩阵的名字处输入exit可以退出该模块"}).Show();
    while (true)
    {
        Color_out(yellow, "输入矩阵的名字(当输入exit时退出该模块)");
        std::string name = Input_name();
        if (name == "exit")
            break;
        while (!(std::cin >> Matset[name]))
            ;
    }
}
void Evaluate_Matrix()
{
    Menu("表达式求值", {"作者能力有限", "只支持数字与矩阵之间的+ / * ^(次方运算)", "^-1可以被解析成求逆,^T可以被解析成求转置", "输入exit可以退出该模块"}).Show();
    while (true)
    {
        std::string expression;
        Color_out(yellow, "输入表达式(当输入exit时退出该模块)");
        while (!(std::getline(std::cin, expression) && !expression.empty()))
            ;
        if (expression == "exit")
            break;
        Matrix result = Evaluate(expression);
        std::cout << result << std::endl;
        Save_Matrix(result);
    }
}
void Show_Matrix()
{
    Menu("在这里可以查看所有矩阵的值").Show();
    std::cout << green;
    for (auto [x, y] : Matset)
        std::cout << x << std::endl
                  << y << std::endl;
    std::cout << reset;
    system("pause");
}

void Transpose_Matrix()
{
    Menu("矩阵转置", {"输入需要转置的矩阵的名字", "当输入exit时退出该模块"}).Show();
    while (true)
    {
        Color_out(yellow, "输入需要转置的矩阵的名字(当输入exit时退出该模块)");
        std::string name = In_or_out();
        if (name.empty())
            continue;
        else if (name == "exit")
            break;
        Matrix result = Matset[name].Transpose();
        Output_name_result(name, result);
        Save_Matrix(result);
    }
}

void Inverse_Matrix()
{
    Menu("矩阵转置", {"输入需要求逆的矩阵的名字", "当输入exit时退出该模块"}).Show();
    while (true)
    {
        Color_out(yellow, "输入需要求逆的矩阵的名字(当输入exit时退出该模块)");
        std::string name = In_or_out();
        if (name.empty())
            continue;
        else if (name == "exit")
            break;
        std::cout << name << ":" << std::endl
                  << Matset[name] << std::endl;
        Matrix result = Matset[name].Inverse(Yes_yeah_Oh_no("是否要给出消元的具体过程"));
        std::cout << result << std::endl;
        Save_Matrix(result);
    }
}

void Guass_Matrix()
{
    Menu("高斯消元", {"输入需要消元的矩阵的名字", "当输入exit时退出该模块"}).Show();
    while (true)
    {
        Color_out(yellow, "输入需要消元的矩阵的名字(当输入exit时退出该模块)");
        std::string name = In_or_out();
        if (name.empty())
            continue;
        else if (name == "exit")
            break;
        auto [rank, result] = Matset[name].Guass_Elimination(Yes_yeah_Oh_no("是否要给出消元的具体过程"), 1);
        Save_Matrix(result);
    }
}

void Det_Matrix()
{
    Menu("求行列式", {"输入需要求解的矩阵的名字", "当输入exit时退出该模块"}).Show();
    while (true)
    {
        Color_out(yellow, "输入需要求解的矩阵的名字(当输入exit时退出该模块)");
        std::string name = In_or_out();
        if (name.empty())
            continue;
        else if (name == "exit")
            break;
        Frac result = Matset[name].Determinant();
        Output_name_result(name, result);
    }
}

void Matrix_Operations()
{
    Menu Operations("矩阵的各类计算",
                    {"矩阵转置", "矩阵求逆", "高斯消元", "求行列式"},
                    {Transpose_Matrix, Inverse_Matrix, Guass_Matrix, Det_Matrix});
    Operations.Show();
    Operations.Switch();
}
// 主菜单
Menu Main("矩阵计算器",
          {"输入矩阵", "查看矩阵", "表达式求值", "矩阵的各类计算"},
          {Input_Matrix, Show_Matrix, Evaluate_Matrix, Matrix_Operations});
#endif
