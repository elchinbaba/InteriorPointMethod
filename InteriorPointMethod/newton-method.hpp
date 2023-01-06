#pragma once

#include "interior-point-method.hpp";

#include "function.hpp";

#ifndef NEWTON_METHOD_H
#define NEWTON_METHOD_H

class NewtonMethod
{
	public:
		Function *function;
	private:
		MATRIX m_Hessian;
		MATRIX m_gradient;

	public:
		MATRIX getHessian();
		void setHessian(MATRIX);
		MATRIX getGradient();
		void setGradient(MATRIX);

	public:
		NewtonMethod();
		NewtonMethod(Function*, ARRAY_SIZE);

	public:
		MATRIX iterate(IPM, POINT);
};

#endif // !NEWTON_METHOD_H
