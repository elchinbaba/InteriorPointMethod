#pragma once

#include "differential-all.hpp";

#ifndef NEWTON_METHOD_ALL_H
#define NEWTON_METHOD_ALL_H

class NewtonMethod
{
	public:
		Function* function;
		IPM ipm;
		OMEGA omega;
		VALUE alfa = 0.85;
		POINT x_old;
		MATRIX gradient_old;
	public:
		MATRIX hessian;
		MATRIX gradient;

	public:
		VALUE linearFunction(VECTOR_DOUBLE v, VECTOR_DOUBLE x)
		{
			return Matrix(v).transpose().multiply(Matrix(x)).arr[0][0];
		}
		void setHessian(MATRIX &hessian)
		{
			NewtonMethod::hessian = hessian;
		}
		void setGradient(MATRIX &gradient)
		{
			NewtonMethod::gradient = gradient;
		}

	public:
		NewtonMethod()
		{
			NewtonMethod::function = NULL;
			NewtonMethod::hessian = Matrix();
			NewtonMethod::gradient = Matrix();
		}
		NewtonMethod(Function* function, ARRAY_SIZE n)
		{
			NewtonMethod::function = function;
			NewtonMethod::gradient = Matrix(n, 1);
			NewtonMethod::hessian = Matrix(n, n);
		}
		NewtonMethod(Function* function, ARRAY_SIZE n, POINT x)
		{
			NewtonMethod::function = function;
			NewtonMethod::gradient = Matrix(n, 1);
			NewtonMethod::hessian = Matrix(n, n);
			NewtonMethod::x_old = x;
			NewtonMethod::gradient_old = findGradient(function, x_old);
		}

	public:
		void evaluateHessian(Function* &function, POINT &point)
		{
			for (ARRAY_SIZE i = 0; i < hessian.row; i++)
			{
				for (ARRAY_SIZE j = 0; j < hessian.column; j++)
				{
					hessian.arr[i][j] = derivative(function, point, { i + 1, j + 1 });
				}
			}
		}
		void evaluateGradient(Function* &function, POINT &point)
		{
			for (ARRAY_SIZE i = 0; i < gradient.row; i++)
			{
				gradient.arr[i][0] = derivative(function, point, { i + 1 });
			}
		}
		void findHessian(Function*& function, POINT& point)
		{
			MATRIX h = Matrix(hessian.row, hessian.column, 0);
			for (int i = 0; i < ipm.b.size(); i++)
			{
				h = h + (1 / pow(linearFunction(ipm.A[i], point) - ipm.b[i], 2)) * Matrix(ipm.A[i]).multiply(Matrix(ipm.A[i]).transpose());
			}
			hessian = h;
		}
		MATRIX findGradient(Function*& function, POINT& point)
		{
			MATRIX g = Matrix(gradient.row, gradient.column, 0);
			for (int i = 0; i < ipm.b.size(); i++)
			{
				g = g + (1 / (linearFunction(ipm.A[i], point) - ipm.b[i])) * Matrix(ipm.A[i]);
			}
			return g + omega * Matrix(ipm.c);
		}
		MATRIX iterate(POINT x)
		{
			//evaluateHessian(function, x);
			//evaluateGradient(function, x);

			gradient = findGradient(function, x);
			findHessian(function, x);

			MATRIX inverse;
			MATRIX subtract;
			try
			{
				inverse = hessian.inverse();
			}
			catch (std::exception ex)
			{
				throw ex;
			}

			subtract = inverse * gradient;
			for (int i = 0; i < subtract.row; i++)
			{
				for (int j = 0; j < subtract.column; j++)
				{
					if (subtract.arr[i][j] != subtract.arr[i][j])
					{
						throw std::exception("NaN found");
					}
				}
			}
			
			return Matrix(x) - alfa * subtract;
		}
};

#endif // !NEWTON_METHOD_H
