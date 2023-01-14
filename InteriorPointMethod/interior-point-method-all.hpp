#pragma once

#include "newton-method-all.hpp"

#include <algorithm>

#ifndef INTERIOR_POINT_METHOD_ALL_H
#define INTERIOR_POINT_METHOD_ALL_H

class InteriorPointMethod
{
	private:
		IPM ipm;

		OMEGA m_omega;
		POINT m_x;

	public:
		InteriorPointMethod(IPM ipm)
		{
			this->ipm = ipm;
			InteriorPointMethod::m_omega = 0.000005;
			for (int i = 0; i < ipm.c.size(); i++)
			{
				InteriorPointMethod::m_x.push_back(*std::max_element(std::begin(ipm.b), std::end(ipm.b)));
			}
		}
		POINT calculate()
		{
			LogBarrierFunction* lbf = new LogBarrierFunction(ipm, m_omega);
			NewtonMethod* nm = new NewtonMethod(lbf, ipm.c.size());

			for (int i = 1; i < 1000; i++)
			{
				lbf->omega = (1 + 0.5) * lbf->omega;
				try
				{
					m_x = Matrix::convertToVector(nm->iterate(m_x));
				}
				catch (std::exception e)
				{
					std::cout << e.what() << " at iteration " << i << " \n";
					break;
				}
			}
			return m_x;
		}
};

#endif INTERIOR_POINT_METHOD_H