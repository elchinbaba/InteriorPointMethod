#include "differential.hpp";

double differential(double (*func) (double x), double a, int n)
{
	if (n == 0) return func(a);
	return differential(func, a + EPS, n - 1) - differential(func, a - EPS, n - 1);
}

double derivative(double (*func) (POINT x), POINT a, PARTIALS partials)
{
	int size = partials.size();
	if (size == 0)
	{
		return func(a);
	}

	int deriving = partials[size - 1];

	partials.pop_back();

	POINT b, c;
	for (int i = 0; i < a.size(); i++)
	{
		if (i == deriving - 1)
		{
			b.push_back(a[i] + EPS);
			c.push_back(a[i] - EPS);
		}
		else
		{
			b.push_back(a[i]);
			c.push_back(a[i]);
		}
	}
	
	return (derivative(func, b, partials) - derivative(func, c, partials))/(2 * EPS);
}

double derivative(std::function<double (POINT)> func, POINT a, PARTIALS partials)
{
	int size = partials.size();
	if (size == 0)
	{
		return func(a);
	}

	int deriving = partials[size - 1];

	partials.pop_back();

	POINT b, c;
	for (int i = 0; i < a.size(); i++)
	{
		if (i == deriving - 1)
		{
			b.push_back(a[i] + EPS);
			c.push_back(a[i] - EPS);
		}
		else
		{
			b.push_back(a[i]);
			c.push_back(a[i]);
		}
	}

	return (derivative(func, b, partials) - derivative(func, c, partials)) / (2 * EPS);
}