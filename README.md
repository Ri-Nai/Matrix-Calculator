# 矩阵计算器 | Matrix_Calculator
![](/img/head.png)
## 代码简介
### 文件结构
- `include`
  - 在`Frac.h`中封装了`Frac`分数类
  - 在`Matrix.h`中封装了`Matrix`矩阵类
  - 在`Color.h`中
    - 声明了几个ANSI转义符,用于设计交互界面的字体样式
    - 声明了一个颜色输出函数,用于
  - 在`Menu.h`中封装了`Menu`菜单类,用于可视化和交互设计
  - 在`Evaluate.hpp`中主要定义了表达式求值的函数
  - 在`Operations.hpp`中定义了菜单中的各类交互操作,以及定义了Menu类型变量Main,即为主菜单
- `src`
  - `Color.cpp,Frac.cpp, Matrix_Functions.cpp, Matrix_Operators.cpp, `分别提供了上述头文件的代码实现
  - `Matrix_Functions.cpp`里定义了`Matset`变量,该变量类型为`std::map<std::string,Matrix>`,意义为存储矩阵名和实际矩阵值的键值对
  - `main.cpp`中定义了`main`函数

```
文件树
Matrix_Calculator
│  CMakeLists.txt
│
├─include
│      Color.h
│      Evaluate.hpp
│      Frac.h
│      Matrix.h
│      Menu.hpp
│      Operations.hpp
│
├─lib
└─src
        Color.cpp
        Frac.cpp
        main.cpp
        Matrix_Functions.cpp
        Matrix_Operators.cpp
```
### 功能介绍
- **基本功能**
![](/img/basic.png)
  - **输入矩阵**
    - 可以以小数分数和整数的形式输入
    - ![](/img/Input_sample.png)
    - 最终以分数`Frac`类的形式显示
    - ![](/img/Output_sample.png)
  - **查看矩阵**
  - **矩阵表达式求值**
    - 加,减,乘,次方
    - 求逆,转置
  - **各类相关的矩阵计算**
    - **矩阵转置**
    - **矩阵求逆**
      - 使用与单位矩阵一并高斯消元的方式进行求逆
      - 可以显示做题过程以便抄写线性代数作业
    - **高斯消元**
      - 可以显示做题过程以便抄写线性代数作业
    - **求行列式**
      - 使用按行展开的方式递归地求解
- **错误排查**
![](/img/hint.png)
  - 考虑了部分用户输入失误的情况
  - 考虑了部分数据错误的情况
  - 配备了部分错误情况输出提醒
## 自测运行环境
### 环境
- **操作系统**: Windows 11 专业版
- **编译环境**:
  - **语言标准**: C++20
  - `g++: 13.2.0`
  - `cmake: 3.29.2`
  - `ninja: 1.11.1`
### 启动！方式

1. 编译源文件的方式(保证已经安装并配置CMake环境)\
在命令行中输入以下内容
```
mkdir build (如果不存在build文件夹)
cd .\build\
cmake ..
cmake --build .
```
之后会在`.\build\`下生成一个`Matrix-Calculator.exe`可执行文件

2. 直接运行Compile.ps1 \
之后也会在`.\build\`下生成一个`Matrix-Calculator.exe`
