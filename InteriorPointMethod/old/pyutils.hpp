#pragma once

#ifndef PYUTILS_H__
#define PYUTILS_H__

#include <Python.h>
#include "typedef.h"

PyObject* vectorToList(const POINT& data);

VECTOR_DOUBLE listToVector(PyObject* incoming);

ARRAY listToArray(PyObject* incoming);

#endif