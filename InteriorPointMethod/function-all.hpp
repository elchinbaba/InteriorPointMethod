#pragma once

#include "matrix-all.hpp"
#include "struct-ipm-all.hpp"

#ifndef FUNCTION_ALL_H
#define FUNCTION_ALL_H

class Function
{
	public:
		virtual VALUE call(POINT) = 0;
};

class LogBarrierFunction : public Function
{
	public:
		IPM ipm;

		OMEGA omega;

	public:
		LogBarrierFunction(IPM ipm, OMEGA omega)
		{
			LogBarrierFunction::ipm = ipm;
			LogBarrierFunction::omega = omega;
		}
		VALUE call(POINT x)
		{
			VALUE sum = 0, value = -99999, old_value;
			for (int i = 0; i < ipm.A.size(); i++)
			{
				old_value = value;
				value = Matrix(ipm.A[i]).transpose().multiply(Matrix(x)).getArray()[0][0] - ipm.b[i];
				if (value == -old_value && value < 0)
				{
					sum -= log(-value);
				}
				else
				{
					sum -= log(value);
				}
			}
			return omega * Matrix::convert(ipm.c).transpose().multiply(Matrix::convert(x)).getArray()[0][0] + sum;
		}
};

#endif FUNCTION_H