#pragma once

#include "differential-all.hpp";

#ifndef NEWTON_METHOD_ALL_H
#define NEWTON_METHOD_ALL_H

class NewtonMethod
{
	public:
		Function* function;
	public:
		MATRIX* hessian;
		MATRIX* gradient;

	public:
		void setHessian(MATRIX* hessian)
		{
			NewtonMethod::hessian = hessian;
		}
		void setGradient(MATRIX* gradient)
		{
			NewtonMethod::gradient = gradient;
		}

	public:
		NewtonMethod()
		{
			NewtonMethod::function = NULL;
			NewtonMethod::hessian = new Matrix();
			NewtonMethod::gradient = new Matrix();
		}
		NewtonMethod(Function* function, ARRAY_SIZE n)
		{
			NewtonMethod::function = function;
			NewtonMethod::gradient = new Matrix(n, 1);
			NewtonMethod::hessian = new Matrix(n, n);
		}

	public:
		void evaluateHessian(Function* &function, POINT &point)
		{
			for (ARRAY_SIZE i = 0; i < hessian->row; i++)
			{
				for (ARRAY_SIZE j = 0; j < hessian->column; j++)
				{
					hessian->arr[i][j] = derivative(function, point, { i + 1, j + 1 });
				}
			}
		}
		void evaluateGradient(Function* &function, POINT &point)
		{
			for (ARRAY_SIZE i = 0; i < gradient->row; i++)
			{
				gradient->arr[i][0] = derivative(function, point, { i + 1 });
			}
		}
		MATRIX iterate(POINT x)
		{
			evaluateHessian(function, x);
			evaluateGradient(function, x);

			MATRIX subtract;
			try
			{
				subtract = *(hessian->inverse()) * *gradient;
			}
			catch (std::exception ex)
			{
				throw ex;
			}
			
			VALUE checkNaN = subtract.arr[0][0];
			if (checkNaN != checkNaN)
			{
				throw std::exception("NaN found");
			}

			return Matrix(x) - subtract;
		}
};

#endif // !NEWTON_METHOD_H
