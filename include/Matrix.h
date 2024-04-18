/*
 * @Author: Reina__
 * @Date: 2024-04-18 13:44:05
 * @Last Modified by: Reina__
 * @Last Modified time: 2024-04-18 21:54:21
 */
#ifndef MATRIX_H
#define MATRIX_H

#include <map>
#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include "Frac.h"
#include "Color.h"

class Matrix
{
private:
    std::vector<std::vector<Frac>> data;
    int rows;
    int cols;

public:
    Matrix();
    Matrix(int value);
    Matrix(int Num_Rows, int Num_Cols);

    Frac Get_Element(int row, int col) const;
    void Set_Element(int row, int col, const Frac &value);
    bool empty() const;
    int Get_Rank()const;
    Matrix operator+(const Matrix &other) const;
    Matrix operator-(const Matrix &other) const;
    Matrix operator*(const Frac &scalar) const;
    Matrix operator*(const Matrix &other) const;
    Matrix operator|(const Matrix &other) const;
    Matrix operator^(const int &pow) const;
    Matrix operator^(const Matrix &fake_int) const;
    Matrix operator-() const;
    friend Matrix operator*(const Frac &scalar, const Matrix &matrix);
    friend std::istream &operator>>(std::istream &is, Matrix &matrix);
    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix);
    Matrix Transpose() const;
    Matrix Sub_Matrix(const int &beginx, const int &beginy, const int &endx, const int &endy) const;

    Frac Determinant() const;
    Matrix Inverse(bool process = false) const;
    std::pair<int, Matrix> Guass_Elimination(bool process = 0, bool show_result = false) const;
};
extern std::map<std::string, Matrix> Matset;
const Matrix Identity(const int &dimension);

#endif
