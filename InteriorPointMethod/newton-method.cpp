#include "newton-method.hpp";

#include "differential.hpp";

#include "typedef.h";

static MATRIX evaluateHessian(MATRIX hessian, Function *function, POINT point)
{
	ROW row = hessian.getRow();
	COLUMN column = hessian.getColumn();
	ARRAY arr = hessian.getArray();

	for (ARRAY_SIZE i = 0; i < row; i++)
	{
		for (ARRAY_SIZE j = 0; j < column; j++)
		{
			arr[i][j] = derivative(function, point, { i + 1, j + 1 });
		}
	}

	return Matrix(arr);
}

static MATRIX evaluateGradient(MATRIX gradient, Function *function, POINT point)
{
	ROW row = gradient.getRow();
	ARRAY arr = gradient.getArray();

	for (ARRAY_SIZE i = 0; i < row; i++)
	{
		arr[i][0] = derivative(function, point, { i + 1 });
	}

	return Matrix(arr);
}

NewtonMethod::NewtonMethod()
{

}

NewtonMethod::NewtonMethod(Function *function, ARRAY_SIZE n)
{
	NewtonMethod::function = function;
	NewtonMethod::m_gradient = Matrix(n, 1);
	NewtonMethod::m_Hessian = Matrix(n, n);
}

MATRIX NewtonMethod::getHessian()
{
	return NewtonMethod::m_Hessian;
}

void NewtonMethod::setHessian(MATRIX hessian)
{
	NewtonMethod::m_Hessian = hessian;
}

MATRIX NewtonMethod::getGradient()
{
	return NewtonMethod::m_gradient;
}

void NewtonMethod::setGradient(MATRIX gradient)
{
	NewtonMethod::m_gradient = gradient;
}

MATRIX NewtonMethod::iterate(IPM ipm, POINT x)
{
	this->setHessian(evaluateHessian(this->getHessian(), function, x));
	this->setGradient(evaluateGradient(this->getGradient(), function, x));

	MATRIX inverse_hessian;
	try
	{
		inverse_hessian = m_Hessian.inverse();
	}
	catch (std::exception ex)
	{
		throw ex;
	}

	MATRIX subtract = inverse_hessian * m_gradient;
	VALUE checkNaN = subtract.getArray()[0][0];
	if (checkNaN != checkNaN)
	{
		throw std::exception("NaN found");
	}
	return Matrix(x) - subtract;
}