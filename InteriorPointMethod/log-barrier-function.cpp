#include "log-barrier-function.hpp";

#include "typedef.h"

LogBarrierFunction::LogBarrierFunction(IPM ipm, OMEGA omega)
{
	LogBarrierFunction::ipm = ipm;
	LogBarrierFunction::omega = omega;
}

VALUE LogBarrierFunction::call(POINT x)
{
	VALUE sum = 0, value = -99999, old_value;
	for (int i = 0; i < ipm.A.size(); i++)
	{
		old_value = value;
		value = linearFunction(ipm.A[i], x) - ipm.b[i];
		if (value == -old_value && value < 0)
		{
			sum -= log(-value);
		}
		else
		{
			sum -= log(value);
		}
	}
	return omega * linearFunction(ipm.c, x) + sum;
}