#include "interior-point-method.hpp";

#include "log-barrier-function.hpp";

#include "function.hpp";

#include <algorithm>

InteriorPointMethod::InteriorPointMethod(IPM ipm)
{
	this->ipm = ipm;
	InteriorPointMethod::m_omega = 0.000005;
	for (int i = 0; i < ipm.c.size(); i++)
	{
		InteriorPointMethod::m_x.push_back(*std::max_element(std::begin(ipm.b), std::end(ipm.b)));
	}
}

POINT InteriorPointMethod::calculate()
{
	LogBarrierFunction *lbf = new LogBarrierFunction(ipm, m_omega);
	NewtonMethod nm = NewtonMethod(lbf, ipm.c.size());

	for (int i = 1; i < 250; i++)
	{
		lbf->omega = (1 + 0.25) * lbf->omega;
		try
		{
			m_x = nm.iterate(ipm, m_x).convertToVector();
		}
		catch (std::exception e)
		{
			//std::cout << e.what() << std::endl;
			break;
		}
	}
	return m_x;
}