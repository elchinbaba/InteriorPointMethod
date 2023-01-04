#include "interior-point-method.hpp";

#include "function.hpp";

#include <math.h>;

InteriorPointMethod::InteriorPointMethod(COEFFICIENTS c, Matrix A, Matrix b)
{
	InteriorPointMethod::m_c = c;
	InteriorPointMethod::m_A = A;
	InteriorPointMethod::m_b = b;
	for (int i = 0; i < c.size(); i++)
	{
		InteriorPointMethod::m_x.push_back(0);
	}
}

double InteriorPointMethod::logBarrier()
{
	double sum = 0;
	ARRAY arr_A = InteriorPointMethod::m_A.getMatrix();
	ARRAY arr_b = InteriorPointMethod::m_b.getMatrix();
	for (int i = 0; i < arr_A.size(); i++)
	{
		sum -= log(linearFunction(arr_A[i], InteriorPointMethod::m_x) - arr_b[i][0]);
	}
	return sum;
}