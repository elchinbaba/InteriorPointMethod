#include "pyutils.hpp"
#include <stdexcept>

PyObject* vectorToList(const POINT& data)
{
	PyObject* listObj = PyList_New(data.size());
	if (!listObj) throw std::logic_error("Unable to allocate memory for Python list");
	for (unsigned int i = 0; i < data.size(); i++) {
		PyObject* num = PyFloat_FromDouble(data[i]);
		if (!num) {
			Py_DECREF(listObj);
			throw std::logic_error("Unable to allocate memory for Python list");
		}
		PyList_SET_ITEM(listObj, i, num);
	}
	return listObj;
}

VECTOR_DOUBLE listToVector(PyObject* incoming) {
	VECTOR_DOUBLE data;
	if (PyList_Check(incoming)) {
		for (Py_ssize_t i = 0; i < PyList_Size(incoming); i++) {
			PyObject* value = PyList_GetItem(incoming, i);
			data.push_back(PyFloat_AsDouble(value));
		}
	}
	else {
		throw std::logic_error("Passed PyObject pointer was not a list!");
	}
	return data;
}

ARRAY listToArray(PyObject* incoming) {
	ARRAY data;
	if (PyList_Check(incoming)) {
		data.resize(PyList_Size(incoming));
		for (Py_ssize_t i = 0; i < PyList_Size(incoming); i++) {
			PyObject* vector = PyList_GetItem(incoming, i);
			for (Py_ssize_t j = 0; j < PyList_Size(vector); j++)
			{
				PyObject* value = PyList_GetItem(vector, j);
				data[i].push_back(PyFloat_AsDouble(value));
			}
		}
	}
	else {
		throw std::logic_error("Passed PyObject pointer was not a list!");
	}
	return data;
}