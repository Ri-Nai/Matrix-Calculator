/*
 * @Author: Reina__
 * @Date: 2024-04-18 13:43:45
 * @Last Modified by: Reina__
 * @Last Modified time: 2024-04-18 21:12:36
 */
#include "Matrix.h"
#include "Color.h"
Matrix::Matrix()
{
    rows = cols = 0;
}
Matrix::Matrix(int value)
{
    rows = cols = 1;
    data.assign(1, std::vector<Frac>(1, value));
}
Matrix::Matrix(int Num_Rows, int Num_Cols) : rows(Num_Rows), cols(Num_Cols)
{
    data.resize(rows, std::vector<Frac>(cols, Frac(0)));
}

Frac Matrix::Get_Element(int row, int col) const
{
    return data[row][col];
}
void Matrix::Set_Element(int row, int col, const Frac &value)
{
    data[row][col] = value;
}
bool Matrix::empty() const
{
    return rows == 0 && cols == 0;
}

Matrix Matrix::operator+(const Matrix &other) const
{
    if (rows != other.rows || cols != other.cols)
    {
        Color_out(red, "矩阵的行数与列数不符合加法的规则");
        return Matrix();
    }
    Matrix result(rows, cols);
    for (int row = 0; row < rows; ++row)
        for (int col = 0; col < cols; ++col)
            result.Set_Element(row, col, data[row][col] + other.data[row][col]);
    return result;
}
Matrix Matrix::operator-(const Matrix &other) const
{
    if (rows != other.rows || cols != other.cols)
    {
        Color_out(red, "矩阵的行数与列数不符合减法的规则");
        return Matrix();
    }
    Matrix result(rows, cols);
    for (int row = 0; row < rows; ++row)
        for (int col = 0; col < cols; ++col)
            result.Set_Element(row, col, data[row][col] - other.data[row][col]);
    return result;
}

Matrix Matrix::operator*(const Frac &scalar) const
{
    Matrix result(rows, cols);
    for (int row = 0; row < rows; ++row)
        for (int col = 0; col < cols; ++col)
            result.Set_Element(row, col, data[row][col] * scalar);
    return result;
}
Matrix Matrix::operator|(const Matrix &other) const
{
    if (other.rows != rows)
    {
        Color_out(red, "行数不相同的矩阵无法行连接");
        return Matrix();
    }
    Matrix result = *this;
    result.cols += other.cols;
    for (int row = 0; row < rows; ++row)
        result.data[row].insert(result.data[row].end(), other.data[row].cbegin(), other.data[row].cend());
    return result;
}
Matrix Matrix::operator^(const int &pow) const
{
    Matrix result(0, 0), base = *this;
    int now = pow;
    if (cols != rows)
    {
        Color_out(red, "只有方阵才可以自乘哦");
        return Matrix();
    }
    result = Identity(cols);
    if (now < 0)
    {
        if (now == -1)
            return Inverse();
        Color_out(red, "矩阵不存在负次方");
        return Matrix();
    }
    while (now > 0)
    {
        if (now & 1)
            result = result * base;
        base = base * base;
        now >>= 1;
    }
    return result;
}
Matrix Matrix::operator^(const Matrix &fake_int) const
{
    if (fake_int.rows != 1 || fake_int.cols != 1)
    {
        Color_out(red, "矩阵应该没有矩阵次方吧吧吧");
        return Matrix();
    }
    auto value = fake_int.data[0][0];
    if (value.Get_Denominator() != 1)
    {
        Color_out(red, "我只是不知道矩阵的分数次方该怎么算而已我我我");
        return Matrix();
    }
    return *this ^ value.Get_Numerator();
}

Matrix Matrix::operator*(const Matrix &other) const
{
    if (other.cols == 1 && other.rows == 1)
        return *this * other.data[0][0];
    if (cols != other.rows)
    {
        Color_out(red, "矩阵的行数与列数不符合乘法的规则");
        return Matrix();
    }
    Matrix result(rows, other.cols);

    for (int row = 0; row < rows; ++row)
        for (int col = 0; col < other.cols; ++col)
        {
            Frac sum(0);
            for (int mid = 0; mid < cols; ++mid)
                sum = sum + (data[row][mid] * other.data[mid][col]);
            result.Set_Element(row, col, sum);
        }
    return result;
}

Matrix Matrix::operator-() const
{
    return *this * Frac(-1);
}

Matrix operator*(const Frac &scalar, const Matrix &matrix)
{
    return matrix * scalar;
}
std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
{
    for (int row = 0; row < matrix.rows; ++row)
    {
        for (int col = 0; col < matrix.cols; ++col)
            os << matrix.data[row][col].Format_Output(7);
        os << std::endl;
    }
    return os;
}
std::istream &operator>>(std::istream &is, Matrix &matrix)
{
    Color_out(yellow, "请输入矩阵的行数和列数");
    int rows, cols;
    is >> rows >> cols;
    matrix = Matrix(rows, cols);
    Color_out(yellow, "请输入相应行列的数据");
    for (int row = 0; row < matrix.rows; ++row)
        for (int col = 0; col < matrix.cols; ++col)
            is >> matrix.data[row][col];
    return is;
}

Matrix Matrix::Sub_Matrix(const int &beginx, const int &beginy, const int &endx, const int &endy) const
{
    Matrix result(endx - beginx, endy - beginy);
    for (int row = beginx; row < endx; ++row)
        for (int col = beginy; col < endy; ++col)
            result.Set_Element(row - beginx, col - beginy, data[row][col]);
    return result;
}

Matrix Matrix::Transpose() const
{
    Matrix result(cols, rows);
    for (int row = 0; row < rows; ++row)
        for (int col = 0; col < cols; ++col)
            result.Set_Element(col, row, data[row][col]);
    return result;
}
