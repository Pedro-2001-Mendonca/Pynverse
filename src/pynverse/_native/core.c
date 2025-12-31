#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <numpy/arrayobject.h>
#include <math.h>
#include "matrix_api.h"

/* Wrapper */
static PyObject* py_inv_from_array(PyObject* self, PyObject* args) {
    PyObject* input_obj;


    if (!PyArg_ParseTuple(args, "O", &input_obj))
        return NULL;

    PyArrayObject* array =
        (PyArrayObject*)PyArray_FROM_OTF(input_obj, NPY_FLOAT32, NPY_ARRAY_IN_ARRAY);

    if (!array)
        return NULL;

    int total = (int)PyArray_SIZE(array);
    int size = (int)sqrt(total);

    if (size * size != total) {
        Py_DECREF(array);
        PyErr_SetString(PyExc_ValueError, "Array cannot be converted to a square matrix");
        return NULL;
    }

    float* data = (float*)PyArray_DATA(array);

    float* result = invert_from_array(data, size);

    if (!result) {
        Py_DECREF(array);
        PyErr_SetString(PyExc_RuntimeError, "Matrix inversion failed");
        return NULL;
    }

    npy_intp dims[2] = { size, size };
    PyObject* out = PyArray_SimpleNewFromData(2, dims, NPY_FLOAT32, result);

    PyArray_ENABLEFLAGS((PyArrayObject*)out, NPY_ARRAY_OWNDATA);

    Py_DECREF(array);

    return out;
}

/* Métodos */
static PyMethodDef methods[] = {
    {"inv_from_array", py_inv_from_array, METH_VARARGS, "Invert matrix"},
    {NULL, NULL, 0, NULL}
};

/* Módulo */
static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "core",
    NULL,
    -1,
    methods
};

PyMODINIT_FUNC PyInit_core(void) {
    import_array();
    return PyModule_Create(&module);
}
