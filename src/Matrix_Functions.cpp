/*
 * @Author: Reina__
 * @Date: 2024-04-18 13:43:42
 * @Last Modified by: Reina__
 * @Last Modified time: 2024-04-18 21:11:37
 */
#include "Matrix.h"
#include "Color.h"
std::map<std::string, Matrix> Matset;
Frac Matrix::Determinant() const
{
    if (rows != cols)
    {
        Color_out(red, "只有方阵才可以求行列式哦");
        return Frac(0, 0);
    }
    if (rows == 1)
        return data[0][0];
    Frac result(0, 1);
    int sign = 1;
    for (int col = 0; col < cols; ++col)
    {
        Matrix rest = Sub_Matrix(1, 0, rows, col) | Sub_Matrix(1, col + 1, rows, cols);
        result = result + sign * data[0][col] * rest.Determinant();
        sign = sign * -1;
    }
    return result;
}

Matrix Matrix::Inverse(bool process) const
{
    if (rows != cols)
    {
        Color_out(red, "只有方阵才可以求矩阵的逆哦");
        return Matrix();
    }
    if (Get_Rank() != cols)
    {
        Color_out(red, "看起来你的矩阵不满秩哦");
        return Matrix();
    }
    auto [rank, result] = (*this | Identity(cols)).Guass_Elimination(process);
    return result.Sub_Matrix(0, cols, rows, rows + cols);
}

int Matrix::Get_Rank() const
{
    return Guass_Elimination().first;
}

std::pair<int, Matrix> Matrix::Guass_Elimination(bool process, bool show_result) const
{
    Matrix result = *this;
    auto &data0 = result.data;
    std::vector<int> Top; // Top记录的是最终矩阵每一行非0值的列数
    if (process)
        std::cout << "the beginning status" << std::endl
                  << result << std::endl;
    auto clear = [&](int col0, int by, int from, int to)
    {
        for (int row = from; row < to; ++row)
        {
            if (data0[row][col0] == Frac(0, 1))
                continue;
            Frac times = data0[row][col0] / data0[by][col0];
            for (int col = 0; col < cols; ++col)
                data0[row][col] = data0[row][col] - times * data0[by][col];
            if (process)
            {
                std::cout << "R" << row + 1 << " - "
                          << "R" << by + 1 << " * " << times << std::endl;
                std::cout << result << std::endl;
            }
        }
    };
    for (int row = 0, col = 0; row < rows && col < cols; ++row, ++col)
    {
        int num = row;
        for (int nxt = row + 1; nxt < rows; ++nxt)
            // 选取一行该列非零的值作为主元
            // 由于分数不需要处理误差，取比较人性的绝对值最小的列
            if (data0[num][col] == Frac(0, 1) || abs(data0[num][col]) > abs(data0[nxt][col]))
                num = nxt;
        if (data0[num][col] == Frac(0, 1))
            --row; // 当前列不存在非零值就遍历下一列
        else
        {
            Top.push_back(col);
            std::swap(data0[row], data0[num]);
            // 将后面的每一行都消去该主元
            clear(col, row, row + 1, rows);
            if (process && row != num)
            {
                std::cout << "R" << row + 1 << " <---> "
                          << "R" << num + 1 << std::endl;
                std::cout << result << std::endl;
            }
        }
    }
    int rank = Top.size();
    // 回代
    for (int row = rank - 1; row >= 0; --row)
        clear(Top[row], row, 0, row);
    // 将每一行的主元变为1
    for (int row = 0; row < rank; ++row)
    {
        int col0 = Top[row];
        if (process)
            std::cout << "R" << row + 1 << " * " << Frac(1, 1) / data0[row][col0] << std::endl;
        for (int col = cols - 1; col >= col0; --col)
            data0[row][col] = data0[row][col] / data0[row][col0];
        if (process)
            std::cout << result << std::endl;
    }
    if(show_result)
    {
        std::cout << "rank = " << rank << std::endl;
        std::cout << "The result is:" << std::endl;
        std::cout << result << std::endl;
    }

    return {rank, result};
}

const Matrix Identity(const int &dimension)
{
    Matrix result(dimension, dimension);
    for (int row = 0; row < dimension; ++row)
        result.Set_Element(row, row, Frac(1));
    return result;
}
