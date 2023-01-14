// InteriorPointMethod.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "interior-point-method-all.hpp"

POINT checkNewton()
{
    COEFFICIENTS c = { 0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015 };
    INEQUALITY_CONSTRAINT_ARRAY A = {
        { 0, 0.33, 0.67, 1, 1, 0.5, 0, 1, -1 },
        { 0, -0.33, -0.67, -1, -1, -0.5, 0, -1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 0, 0 },
        { -1, -1, -1, -1, -1, -1, -1, 0, 0 },
        { 1.5, 1.83, 2.17, 2.5, 3, 3.5, 4, 0, 0 },
        { -1.5, -1.83, -2.17, -2.5, -3, -3.5, -4, 0, 0 },
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
    INEQUALITY_CONSTRAINT_VECTOR b = { 0.5, -0.5, 1, -1, 2.6, -2.6, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    /*COEFFICIENTS c = { 1, 2, 3 };
    INEQUALITY_CONSTRAINT_ARRAY A = {
        { 2, 3, 4 },
        {-2,-3,-4 },
        { 1, 0, 0 },
        { 0, 1, 0 },
        { 0, 0, 1 }
    };
    INEQUALITY_CONSTRAINT_VECTOR b = { 1, -1, 0, 0, 0 };*/

    return InteriorPointMethod(IPM(c, A, b)).calculate();
}

int main()
{
    Matrix(checkNewton()).show();

    std::cout << "Stop program";
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
