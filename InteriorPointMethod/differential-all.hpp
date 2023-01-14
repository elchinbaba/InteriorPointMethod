#pragma once

#include "function-all.hpp";

#ifndef DIFFERENTIAL_H
#define DIFFERENTIAL_H

#define EPS 0.01

VALUE derivative(Function* &function, POINT &x, PARTIALS partials)
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
			forward.push_back(x[i] + EPS);
			backward.push_back(x[i] - EPS);
		}
		else
		{
			forward.push_back(x[i]);
			backward.push_back(x[i]);
		}
	}

	return (derivative(function, forward, partials) - derivative(function, backward, partials)) / (2 * EPS);
}

VALUE derivative2(Function*& function, POINT& x, PARTIALS partials)
{
	if (partials.size() == 0)
	{
		return function->call(x);
	}

	UNSIGNED_INT deriving = partials[partials.size() - 1];
	partials.pop_back();

	POINT forward;
	for (int i = 0; i < x.size(); i++)
	{
		if (i == deriving - 1)
		{
			forward.push_back(x[i] + EPS);
		}
		else
		{
			forward.push_back(x[i]);
		}
	}
	return (derivative2(function, forward, partials) - function->call(x)) / EPS;
}

#endif