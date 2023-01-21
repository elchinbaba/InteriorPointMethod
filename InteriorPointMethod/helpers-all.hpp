#pragma once

#ifndef HELPERS_ALL
#define HELPERS_ALL

#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

VECTOR_DOUBLE negative(VECTOR_DOUBLE vector)
{
	for (int i = 0; i < vector.size(); i++)
	{
		vector[i] *= -1;
	}
	return vector;
}

IPM ipm_problem(json data, int i)
{
	json problem = data["problems"][i];

	json c = problem["c"];
	json A_ub = problem["A_ub"];
	json b_ub = problem["b_ub"];
	json A_eq = problem["A_eq"];
	json b_eq = problem["b_eq"];
	json bounds = problem["bounds"];

	if (!A_eq.is_null())
	{
		for (int i = 0; i < A_eq.size(); i++)
		{
			A_ub.push_back(A_eq[i]);
			b_ub.push_back(b_eq[i]);
			A_ub.push_back(negative(A_eq[i]));
			b_ub.push_back(-(VALUE)b_eq[i]);
		}
	}

	for (int i = 0; i < bounds.size(); i++)
	{
		if (!bounds[i][0].is_null())
		{
			VECTOR_DOUBLE vector;
			for (int j = 0; j < c.size(); j++)
			{
				if (j != i)
				{
					vector.push_back(0);
				}
				else
				{
					vector.push_back(1);
				}
			}

			A_ub.push_back(vector);
			b_ub.push_back(bounds[i][0]);
		}

		if (!bounds[i][1].is_null())
		{
			VECTOR_DOUBLE vector;
			for (int j = 0; j < c.size(); j++)
			{
				if (j != i)
				{
					vector.push_back(0);
				}
				else
				{
					vector.push_back(-1);
				}
			}

			A_ub.push_back(vector);
			b_ub.push_back(-(VALUE)bounds[i][1]);
		}
	}

	return IPM(c, A_ub, b_ub);
}

IPM goal_problem(json data, int i)
{
	IPM ipm = ipm_problem(data, i);
	VECTOR_DOUBLE c;
	for (int i = 0; i < ipm.A[0].size(); i++)
	{
		c.push_back(0);
	}
	c.push_back(1);
	c.push_back(1);

	ipm.c = c;

	ipm.A[0].push_back(1);
	ipm.A[0].push_back(-1);
	for (int i = 1; i < ipm.A.size(); i++)
	{
		ipm.A[i].push_back(0);
		ipm.A[i].push_back(0);
	}

	VECTOR_DOUBLE vector;
	for (int i = 0; i < ipm.c.size(); i++)
	{
		vector.resize(0);
		for (int j = 0; j < c.size(); j++)
		{
			if (j != i)
			{
				vector.push_back(0);
			}
			else
			{
				vector.push_back(1);
			}
		}

		ipm.A.push_back(vector);
		ipm.b.push_back(-50);
	}

	return ipm;
}

#endif // !HELPERS_ALL
