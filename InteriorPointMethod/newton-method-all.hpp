#pragma once

#include "differential-all.hpp";

#ifndef NEWTON_METHOD_ALL_H
#define NEWTON_METHOD_ALL_H

static MATRIX evaluateHessian(MATRIX hessian, Function* function, POINT point)
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

static MATRIX evaluateGradient(MATRIX gradient, Function* function, POINT point)
{
	ROW row = gradient.getRow();
	ARRAY arr = gradient.getArray();

	for (ARRAY_SIZE i = 0; i < row; i++)
	{
		arr[i][0] = derivative(function, point, { i + 1 });
	}

	return Matrix(arr);
}

class NewtonMethod
{
	public:
		Function* function;
	private:
		MATRIX m_Hessian;
		MATRIX m_gradient;

	public:
		MATRIX getHessian()
		{
			return NewtonMethod::m_Hessian;
		}
		void setHessian(MATRIX hessian)
		{
			NewtonMethod::m_Hessian = hessian;
		}
		MATRIX getGradient()
		{
			return NewtonMethod::m_gradient;
		}
		void setGradient(MATRIX gradient)
		{
			NewtonMethod::m_gradient = gradient;
		}

	public:
		NewtonMethod()
		{
			NewtonMethod::function = NULL;
			NewtonMethod::m_Hessian = Matrix();
			NewtonMethod::m_gradient = Matrix();
		}
		NewtonMethod(Function* function, ARRAY_SIZE n)
		{
			NewtonMethod::function = function;
			NewtonMethod::m_gradient = Matrix(n, 1);
			NewtonMethod::m_Hessian = Matrix(n, n);
		}

	public:
		MATRIX iterate(POINT x)
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
				throw ex.what();
			}
			
			MATRIX subtract = inverse_hessian * m_gradient;
			VALUE checkNaN = subtract.getArray()[0][0];
			if (checkNaN != checkNaN)
			{
				throw std::exception("NaN found");
			}
			return Matrix(x) - subtract;
		}
};

#endif // !NEWTON_METHOD_H
