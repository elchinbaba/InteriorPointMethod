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
			InteriorPointMethod::m_q = 1 / (sqrt(ipm.b.size()));
		}
		void initializeX(VALUE t)
		{
			for (int i = 0; i < ipm.c.size() - 1; i++)
			{
				InteriorPointMethod::m_x.push_back(0);
			}
			InteriorPointMethod::m_x.push_back(t);
		}
		void initializeX(POINT a)
		{
			InteriorPointMethod::m_x = a;
		}
		POINT initialize(IPM ipm, VALUE v)
		{
			IPM ipm_for_init = IPM(ipm.c, ipm.A, ipm.b);

			for (int i = 0; i < ipm_for_init.c.size(); i++)
			{
				ipm_for_init.c[i] = 0;
			}
			ipm_for_init.c.push_back(1);

			for (int i = 0; i < ipm_for_init.A.size(); i++)
			{
				ipm_for_init.A[i].push_back(v);
			}
			VECTOR_DOUBLE a;
			for (int i = 0; i < ipm_for_init.c.size(); i++)
			{
				a.push_back(0);
			}
			a[a.size() - 1] = 1;
			ipm_for_init.A.push_back(a);
			a[a.size() - 1] = -1;
			ipm_for_init.A.push_back(a);

			ipm_for_init.b.push_back(-exp(10));
			ipm_for_init.b.push_back(-exp(10));
			POINT x = InteriorPointMethod(ipm_for_init, true).calculate();
			POINT x_for_init;
			for (int i = 0; i < x.size() - 1; i++)
			{
				x_for_init.push_back(x[i]);
			}
			return x_for_init;
		}
		InteriorPointMethod(IPM ipm, bool doesStart)
		{
			VALUE t = 0;
			for (int i = 0; i < ipm.b.size(); i++)
			{
				t += abs(ipm.b[i]);
			}
			t += 1.1;

			if (doesStart)
			{
				this->ipm = ipm;
				initializeOmega();
				initializeQ();
				initializeX(t);
			}
			else
			{
				this->ipm = ipm;
				initializeOmega();
				initializeQ();
				initializeX(initialize(ipm, t));
			}
		}
		POINT calculate()
		{
			LogBarrierFunction* lbf = new LogBarrierFunction(ipm, m_omega);
			NewtonMethod* nm = new NewtonMethod(lbf, ipm.c.size());
			nm->ipm = ipm;

			for (int i = 1; i < 1000; i++)
			{
				try
				{
					m_x = Matrix::convertToVector(nm->iterate(m_x));
				}
				catch (std::exception e)
				{
					//std::cout << e.what() << " at iteration " << i << " \n";
					VALUE sum1 = 0, sum2 = 0, sum3 = 0;
					for (int i = 0; i < m_x.size() - 2; i++)
					{
						sum1 += ipm.A[0][i] * m_x[i];
						sum2 += ipm.A[2][i] * m_x[i];
						sum3 += ipm.A[4][i] * m_x[i];
					}
					//std::cout << sum1 << " " << sum2 << " " << sum3 << "\n";
					break;
				}
				lbf->omega = (1 + m_q) * lbf->omega;
				nm->omega = lbf->omega;
			}
			return m_x;
		}
};

#endif INTERIOR_POINT_METHOD_H