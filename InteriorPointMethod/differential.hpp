#pragma once

#include "typedef.h";

#include <functional>

#ifndef DIFFERENTIAL_H
#define DIFFERENTIAL_H

#define EPS 0.01

double differential(double (*func) (double), double, int);
double derivative(double (*func) (POINT), POINT, PARTIALS);
double derivative(std::function<double (POINT)>, POINT, PARTIALS);

#endif