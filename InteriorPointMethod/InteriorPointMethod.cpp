// InteriorPointMethod.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "interior-point-method-all.hpp"

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

    //std::cout << derivative(sumFunc, point, partials);
}

void checkFunctions()
{
    //std::cout << linearFunction({ 1, 2, 3 }, { 1, 5, 4});
}

void checkBarrier()
{
    ARRAY A, b;

    A = {
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 }
    };

    b = {
        {-0.5},
        {-2},
        {-3}
    };

    //InteriorPointMethod* ipm = new InteriorPointMethod({ 1, 2, 3 }, Matrix(A), Matrix(b));

    //std::cout << ipm->logBarrier();
}

void checkDeterminant()
{
    ARRAY arr = {
        { 1, 2, 5 },
        { 1, 3, 2 },
        { 8, 4, 5 }
    };

    std::cout << Matrix(arr).determinant();
}

void checkInverse()
{
    ARRAY arr = {
           { 1, 2, 5 },
           { 1, 3, 2 },
           { 8, 4, 5 }
    };

    Matrix(arr).inverse().show();
}

void checkNewton()
{
    COEFFICIENTS c = { 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.5, 0.5 };
    INEQUALITY_CONSTRAINT_ARRAY A = {
        { 0, 0.33, 0.67, 1, 1, 0.5, 0, 1, -1 },
        { 1, 1, 1, 1, 1, 1, 1, 0, 0 },
        { 1.5, 1.83, 2.17, 2.5, 3, 3.5, 4, 0, 0 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 1, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 1 }
    };
    INEQUALITY_CONSTRAINT_VECTOR b = { 25, 50, 130, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    Matrix(InteriorPointMethod(IPM(c, A, b)).calculate()).show();
}

int main()
{
    checkNewton();
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
