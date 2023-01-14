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
		Q m_q;
		POINT m_x;

	public:
		VALUE detmax(ARRAY arr)
		{
			return exp(0);
		}
		void initializeOmega()
		{
			VECTOR_DOUBLE b_abs, c_abs;
			for (int i = 0; i < ipm.b.size(); i++)
			{
				b_abs.push_back(abs(ipm.b[i]));
				c_abs.push_back(abs(ipm.c[i]));
			}
			VALUE b_max = *std::max_element(std::begin(b_abs), std::end(b_abs));
			VALUE c_max = *std::max_element(std::begin(c_abs), std::end(c_abs));
			VALUE A_detmax = detmax(ipm.A);

			VECTOR_DOUBLE maxes = { log(b_max), log(c_max), log(A_detmax) };
			
			VALUE L = 1 + *std::max_element(std::begin(maxes), std::end(maxes));
			VALUE c = 5;

			InteriorPointMethod::m_omega = exp(-c * L);
		}
		void initializeQ()
		{
			InteriorPointMethod::m_q = 1 / sqrt(ipm.b.size());
		}
		void initializeX()
		{
			for (int i = 0; i < ipm.c.size(); i++)
			{
				InteriorPointMethod::m_x.push_back(*std::max_element(std::begin(ipm.b), std::end(ipm.b))/2);
			}
		}
		InteriorPointMethod(IPM ipm)
		{
			this->ipm = ipm;
			initializeOmega();
			initializeQ();
			initializeX();
		}
		POINT calculate()
		{
			LogBarrierFunction* lbf = new LogBarrierFunction(ipm, m_omega);
			NewtonMethod* nm = new NewtonMethod(lbf, ipm.c.size());

			for (int i = 1; i < 1000; i++)
			{
				lbf->omega = (1 + m_q) * lbf->omega;
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