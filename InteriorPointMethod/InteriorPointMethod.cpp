// InteriorPointMethod.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <functional>
#include "matrix.hpp";
#include "differential.hpp";

void checkMatrices()
{
    ARRAY array1, array2;

    array1 = {
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 }
    };

    array2 = {
        { 4, 3, 2 },
        { 2, 4, 5 }
    };

    Matrix matrix1 = Matrix(array1);
    Matrix matrix2 = Matrix(array2);
    Matrix matrix3 = 2.5 * matrix2;
    matrix3 = matrix3.transpose();

    try
    {
        Matrix matrix4 = matrix1 * matrix3;
        matrix4.show();
    }
    catch (std::exception e)
    {
        std::cout << e.what();
    }
}

double sumFUNC(POINT point)
{
    return point[0]*point[0] * point[1] * point[2];
}

void checkDerivatives()
{
    std::function<double (POINT)> sumFunc;
    sumFunc = [](POINT point) { return point[0] * point[0] * point[1] * point[2]; };

    POINT point = { 1, 2, 3 };
    PARTIALS partials = { 1, 2 };

    std::cout << derivative(sumFunc, point, partials);
}

int main()
{
    checkDerivatives();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
