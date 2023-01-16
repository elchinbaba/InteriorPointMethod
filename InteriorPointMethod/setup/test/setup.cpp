#include <Python.h>
#include "interior-point-method-all.hpp"
#include "pyutils-all.hpp"
#include <iostream>

static PyObject* method_linprog(PyObject* self, PyObject* args) {
    PyObject* py_c, * py_A, * py_b;
    if (!PyArg_ParseTuple(args, "OOO", &py_c, &py_A, &py_b)) {
        return NULL;
    }

    COEFFICIENTS c = listToVector(py_c);
    INEQUALITY_CONSTRAINT_ARRAY A = listToArray(py_A);
    INEQUALITY_CONSTRAINT_VECTOR b = listToVector(py_b);
    std::cout << "c" << "\n";
    Matrix(c).show();

    std::cout << "A" << "\n";
    Matrix(A).show();

    std::cout << "b" << "\n";
    Matrix(b).show();

    for (int i = 0; i < A.size(); i++)
    {
        if (A[i].size() != c.size())
        {
            PyErr_SetString(PyExc_Exception, "Size of lists must be convenient for problem.");
            return NULL;
        }
    }
    if (A.size() != b.size())
    {
        PyErr_SetString(PyExc_Exception, "Size of lists must be convenient for problem.");
        return NULL;
    }

    POINT result = InteriorPointMethod(IPM(c, A, b), false).calculate();

    std::cout << "result" << "\n";
    Matrix(result).show();

    return vectorToList(result);
}

static PyMethodDef OptimizeMethods[] = {
    {"linprog", method_linprog, METH_VARARGS, "Return the solution."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef optimizemodule = {
    PyModuleDef_HEAD_INIT,
    "optimize",
    "A Python module that returns the solution of the Linear Programming problem using Interior Point Method.",
    -1,
    OptimizeMethods
};

PyMODINIT_FUNC PyInit_optimize(void) {
    return PyModule_Create(&optimizemodule);
}