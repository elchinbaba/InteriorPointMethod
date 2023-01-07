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
			VALUE sum = 0;
			for (int i = 0; i < ipm.A.size(); i++)
			{
				
				sum -= log(Matrix::convert(ipm.A[i]).transpose().multiply(Matrix::convert(x)).getArray()[0][0] - ipm.b[i]);
			}
			return omega * Matrix::convert(ipm.c).transpose().multiply(Matrix::convert(x)).getArray()[0][0] + sum;
		}
};

#endif FUNCTION_H