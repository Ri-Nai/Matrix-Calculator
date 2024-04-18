/*
 * @Author: Reina__
 * @Date: 2024-04-18 13:44:02
 * @Last Modified by: Reina__
 * @Last Modified time: 2024-04-18 21:13:08
 */
#ifndef MENU_HPP
#define MENU_HPP

#include "Color.h"
#include <conio.h>
#include <stdlib.h>
#include <functional>

// 定义菜单类,函数和子标题绑定
class Menu
{
private:
    std::string title;
    std::vector<std::string> subtitles;
    std::vector<std::function<void()>> functions;

public:
    Menu() {}
    Menu(std::string title_) : title(title_) {}
    Menu(std::string title_, std::vector<std::string> subtitles_) : title(title_), subtitles(subtitles_) {}
    Menu(std::string title_, std::vector<std::string> subtitles_, std::vector<std::function<void()>> functions_)
    {
        title = title_;
        subtitles = subtitles_;
        functions = functions_;
    }
    void Show()
    {
        system("cls");
        // 填充菜单
        auto Format_String = [&](std::string title, int total, std::string color, bool flag)
        {
            int length = title.size();
            int left = (total - length) / 2;
            int right = total - length - left;
            std::string left_space(left, ' '), right_space(right, ' ');
            std::string res;
            if (flag)
                res = "║" + color + left_space + title + right_space + reset + "║";
            else
                res = "║" + color + title + reset + left_space + right_space + "║";
            return res;
        };
        // 数字编号
        auto numbered = [&](std::string s, int id)
        {
            return " " + std::string(1, char(id + '1')) + ". " + s;
        };
        std::cout << "╔══════════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << Format_String(title, 62, white, true) << std::endl;
        if (!subtitles.empty())
            std::cout << "╟──────────────────────────────────────────────────────────────╢" << std::endl;
        for (int i = 0; i < subtitles.size(); ++i)
            std::cout << Format_String(numbered(subtitles[i], i), 62, cyan, false) << std::endl;
        if (!functions.empty())
            std::cout << Format_String(numbered("退出菜单", -1), 62, red, false) << std::endl;
        std::cout << "╚══════════════════════════════════════════════════════════════╝" << std::endl;
    }
    void Switch()
    {
        while (true)
        {
            Show();
            char chr = getch();
            int state = chr - '0';
            if (state == 0)
                break;
            if (state > 0 && state <= functions.size())
                functions[state - 1]();
        }
    }
};

#endif
