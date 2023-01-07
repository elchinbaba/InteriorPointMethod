#pragma once

#include "typedef.h";
#include "struct-ipm.h";

#include "matrix.hpp";

#include "differential.hpp";

#include "newton-method.hpp";

#ifndef INTERIOR_POINT_METHOD_H
#define INTERIOR_POINT_METHOD_H

class InteriorPointMethod
{
	private:
		IPM ipm;

		OMEGA m_omega;
		POINT m_x;

	public:
		InteriorPointMethod(IPM);
		POINT calculate();
};

#endif INTERIOR_POINT_METHOD_H