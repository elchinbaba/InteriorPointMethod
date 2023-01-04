#include "function.hpp";

#include "typedef.h";

#include "matrix.hpp";

double linearFunction(COEFFICIENTS c, POINT p)
{
	Matrix point = Matrix::convert(p);
	return Matrix::convert(c).transpose().multiply(point).getMatrix()[0][0];
}