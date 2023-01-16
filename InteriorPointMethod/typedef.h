#pragma once

#include <vector>
#include <functional>

#ifndef TYPEDEF_H
#define TYPEDEF_H

typedef double VALUE;

typedef unsigned int UNSIGNED_INT;
typedef UNSIGNED_INT ARRAY_SIZE;
typedef ARRAY_SIZE ROW, COLUMN;

typedef std::vector<VALUE> VECTOR_DOUBLE;

typedef std::vector<std::vector<VALUE>> ARRAY;
typedef ARRAY INEQUALITY_CONSTRAINT_ARRAY;

typedef VECTOR_DOUBLE POINT;
typedef POINT START_POINT;

typedef std::vector<UNSIGNED_INT> PARTIALS;
typedef VECTOR_DOUBLE COEFFICIENTS;
typedef VECTOR_DOUBLE INEQUALITY_CONSTRAINT_VECTOR;

typedef class Matrix MATRIX;
typedef VALUE OMEGA;
typedef VALUE Q;

#endif