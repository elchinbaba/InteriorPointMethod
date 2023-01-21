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
	ipm.A[1].push_back(-1);
	ipm.A[1].push_back(1);
	for (int i = 2; i < ipm.A.size(); i++)
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
		ipm.b.push_back(0);
	}

	return ipm;
}

IPM positive_goal_problem(IPM ipm)
{
	IPM positive_ipm;
	/*positive_ipm.c.resize(2 * ipm.c.size());
	positive_ipm.A.resize(ipm.A.size() + ipm.c.size());
	positive_ipm.b.resize(ipm.b.size() + ipm.c.size());*/
	for (int i = 0; i < ipm.c.size() - 2; i++)
	{
		positive_ipm.c.push_back(ipm.c[i]);
		positive_ipm.c.push_back(-ipm.c[i]);
	}
	positive_ipm.c.push_back(ipm.c[ipm.c.size() - 2]);
	positive_ipm.c.push_back(ipm.c[ipm.c.size() - 1]);
	for (int i = 0; i < ipm.A.size() - ipm.c.size(); i++)
	{
		positive_ipm.A.push_back({});
		for (int j = 0; j < ipm.A[i].size() - 2; j++)
		{
			positive_ipm.A[i].push_back(ipm.A[i][j]);
			positive_ipm.A[i].push_back(-ipm.A[i][j]);
		}
		positive_ipm.A[i].push_back(ipm.A[i][ipm.A[i].size() - 2]);
		positive_ipm.A[i].push_back(ipm.A[i][ipm.A[i].size() - 1]);
	}
	for (int i = 0; i < positive_ipm.c.size(); i++)
	{
		positive_ipm.A.push_back({});
		for (int j = 0; j < positive_ipm.c.size(); j++)
		{
			if (j != i)
			{
				positive_ipm.A[ipm.A.size() - ipm.c.size() + i].push_back(0);
			}
			else
			{
				positive_ipm.A[ipm.A.size() - ipm.c.size() + i].push_back(1);
			}
		}
	}
	for (int i = 0; i < ipm.b.size(); i++)
	{
		positive_ipm.b.push_back(ipm.b[i]);
	}
	for (int i = 0; i < ipm.c.size() - 2; i++)
	{
		positive_ipm.b.push_back(0);
	}
	return positive_ipm;
}

#endif // !HELPERS_ALL
