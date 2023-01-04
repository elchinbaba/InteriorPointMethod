#pragma once

#include "typedef.h";

#include "matrix.hpp";

#include "differential.hpp";

#ifndef INTERIOR_POINT_METHOD_H
#define INTERIOR_POINT_METHOD_H

class InteriorPointMethod
{
	private:
		double m_omega = 0;
		COEFFICIENTS m_c;
		POINT m_x;
		Matrix m_A;
		Matrix m_b;

	public:
		InteriorPointMethod(COEFFICIENTS, Matrix, Matrix);
		double logBarrier();
		POINT calculate();
};

#endif INTERIOR_POINT_METHOD_H