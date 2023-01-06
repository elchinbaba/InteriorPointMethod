#pragma once

#include "matrix.hpp";
#include "typedef.h";

#ifndef FUNCTION_H
#define FUNCTION_H

VALUE linearFunction(COEFFICIENTS, POINT);

class Function
{
	public:
		virtual VALUE call(POINT) = 0;
};

#endif FUNCTION_H