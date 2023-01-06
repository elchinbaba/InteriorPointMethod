#include "log-barrier-function.hpp";

#include "typedef.h"

LogBarrierFunction::LogBarrierFunction(IPM ipm, OMEGA omega)
{
	LogBarrierFunction::ipm = ipm;
	LogBarrierFunction::omega = omega;
}

VALUE LogBarrierFunction::call(POINT x)
{
	VALUE sum = 0;
	for (int i = 0; i < ipm.A.size(); i++)
	{
		sum -= log(linearFunction(ipm.A[i], x) - ipm.b[i]);
	}
	return omega * linearFunction(ipm.c, x) + sum;
}