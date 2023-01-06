#pragma once

#include "typedef.h";

#include "function.hpp";

#ifndef DIFFERENTIAL_H
#define DIFFERENTIAL_H

#define EPS 0.01

VALUE derivative(Function*, POINT, PARTIALS);

#endif