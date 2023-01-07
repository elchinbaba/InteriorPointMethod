#pragma once

#include "function-all.hpp";

#ifndef DIFFERENTIAL_H
#define DIFFERENTIAL_H

#define EPS 0.01

VALUE derivative(Function* function, POINT x, PARTIALS partials)
{
	ARRAY_SIZE size = partials.size();
	if (size == 0)
	{
		return function->call(x);
	}

	UNSIGNED_INT deriving = partials[size - 1];
	partials.pop_back();

	POINT backward, forward;
	for (int i = 0; i < x.size(); i++)
	{
		if (i == deriving - 1)
		{
			backward.push_back(x[i] + EPS);
			forward.push_back(x[i] - EPS);
		}
		else
		{
			backward.push_back(x[i]);
			forward.push_back(x[i]);
		}
	}

	return (derivative(function, backward, partials) - derivative(function, forward, partials)) / (2 * EPS);
}

#endif