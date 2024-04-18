/*
 * @Author: Reina__
 * @Date: 2024-04-18 13:43:36
 * @Last Modified by: Reina__
 * @Last Modified time: 2024-04-18 21:13:41
 */
#include <stack>
#include <cctype>
#include "Matrix.h"
bool is_op(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}
bool is_unary(char c)
{
    return c == '+' || c == '-';
}
bool check_name(char c, bool front)
{
    if (isalpha(c) || c == '_')
        return true;
    return !front && isdigit(c);
}
int priority(char op)
{
    if (op < 0) // 正号或者负号
        return 4;
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    return -1;
}
inline void Warning()
{
    Color_out(red, "求求你输入正确的表达式吧，让我做什么我都是愿意的");
}
bool process_op(std::stack<Matrix> &Mats, char op)
{
    if (Mats.size() < 2 - (op < 0))
    {
        Warning();
        return false;
    }
    if (op < 0)
    {
        Matrix l = Mats.top();
        Mats.pop();
        if (-op == '+')
            Mats.push(l);
        else
            Mats.push(l * Frac(-1));
    }
    else
    {
        Matrix r = Mats.top();
        Mats.pop();
        Matrix l = Mats.top();
        Mats.pop();
        if (op == '+')
            Mats.push(l + r);
        else if (op == '-')
            Mats.push(l - r);
        else if (op == '*')
            Mats.push(l * r);
        else
            Mats.push(l ^ r);
    }
    return true;
}

Matrix Evaluate(const std::string &str)
{
    std::string s = "";
    for (auto chr : str)
        if (chr != ' ')
            s += chr;
    std::stack<Matrix> Mats;
    std::stack<char> Ops;
    // 记录当前运算符是否可能为正号或负号
    // 若之前为操作符，则为正负号

    bool may_be_unary = true;
    for (int i = 0; i < s.size(); ++i)
    {
        if (s[i] == '(')
        {
            Ops.push('(');
            may_be_unary = true;
        }
        else if (s[i] == ')')
        {
            // 不断输出栈顶元素，直至遇到左括号
            while (Ops.top() != '(')
            {
                if (!process_op(Mats, Ops.top()))
                {
                    Warning();
                    return Matrix();
                }
                Ops.pop();
            }
            Ops.pop();
            may_be_unary = false;
        }
        else if (is_op(s[i]))
        {
            char cur_op = s[i];
            if (may_be_unary && is_unary(cur_op))
                cur_op = -cur_op;
            // 不断输出所有运算优先级大于等于当前运算符的运算符
            while (!Ops.empty() && cur_op >= 0 && priority(Ops.top()) >= priority(cur_op))
            {
                if (!process_op(Mats, Ops.top()))
                {
                    Warning();
                    return Matrix();
                }
                Ops.pop();
            }
            if (cur_op == '^' && i + 1 < s.size() && s[i + 1] == 'T')
            {
                if (Mats.empty())
                {
                    Warning();
                    return Matrix();
                }
                Matrix pre = Mats.top();
                Mats.pop();
                Mats.push(pre.Transpose());
                ++i;
                continue;
            }
            Ops.push(cur_op); // 新的运算符入运算符栈
            may_be_unary = true;
        }
        else
        {
            // 数字量
            if (isdigit(s[i]))
            {
                int number = 0;
                while (i < s.size() && isdigit(s[i]))
                    number = number * 10 + s[i++] - '0';
                --i;
                Mats.push(number);
                may_be_unary = false;
            }
            // 矩阵名称
            else if (check_name(s[i], true))
            {
                std::string name = "";
                while (i < s.size() && check_name(s[i], false))
                    name += s[i++];
                --i;
                if(Matset.count(name) == 0)
                {
                    Warning();
                    return Matrix();
                }
                Mats.push(Matset[name]);
                may_be_unary = false;
            }
        }
    }
    while (!Ops.empty())
    {
        if (!process_op(Mats, Ops.top()))
        {
            Warning();
            return Matrix();
        }
        Ops.pop();
    }
    if (Mats.size() != 1)
    {
        Warning();
        return Matrix();
    }
    return Mats.top();
}
