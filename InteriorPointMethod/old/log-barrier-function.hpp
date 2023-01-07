#pragma once

#include "typedef.h";
#include "struct-ipm-all.hpp";

#include "function.hpp";

#ifndef LOG_BARRIER_FUNCTION_H
#define LOG_BARRIER_FUNCTION_H

class LogBarrierFunction : public Function
{
	public:
		IPM ipm;

		OMEGA omega;
	
	public:
		LogBarrierFunction(IPM, OMEGA);
		VALUE call(POINT);
};

#endif // !LOG_BARRIER_FUNCTION_H
