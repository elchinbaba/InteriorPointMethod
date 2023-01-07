#include "function.hpp";

#include "typedef.h";

VALUE linearFunction(COEFFICIENTS c, POINT p)
{
	MATRIX point = Matrix::convert(p);
	return Matrix::convert(c).transpose().multiply(point).getArray()[0][0];
}