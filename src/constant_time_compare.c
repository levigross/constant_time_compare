#include <Python.h>

static PyObject *secure_compare(PyObject *self, PyObject *args);
static PyObject *constant_type_compare(unsigned char sentinel, unsigned char check_byte);

static PyMethodDef ConstantTimeCompareMethods[] = {
    {"compare", secure_compare, METH_VARARGS, "Compares a string in a constant time"},
    {NULL, NULL, 0, NULL}
};

static PyObject *secure_compare(PyObject *self, PyObject *args)
{
    PyObject *temp_string_one;
    PyObject *temp_string_two;
    volatile const unsigned char *left;
    volatile const unsigned char *right;
    Py_ssize_t string_size;

    /* How many arguments were provided to the function */
    if (PyTuple_Size(args) != 2)
    {
        PyErr_SetString(PyExc_ValueError, "You must only supply 2 arguments");
        return NULL;
    }
    /* Can we parse them? */
    if (!PyArg_ParseTuple(args, "OO", &temp_string_one, &temp_string_two)) 
    {
        PyErr_SetString(PyExc_TypeError, "Unable To Parse Function Arguments");
        return NULL;
    }

    /* Are they Python Strings */
    if (!(PyString_CheckExact(temp_string_one)) || !(PyString_CheckExact(temp_string_two))) 
    {
        PyErr_SetString(PyExc_TypeError, "You must supply 2 string objects");
        return NULL;   
    } 

    /* Are they the same size? */
    if (PyString_Size(temp_string_one) != PyString_Size(temp_string_two)) 
    {
        Py_RETURN_FALSE;
    }

    
    left = (const volatile unsigned char *) PyString_AsString(temp_string_one);
    right = (const volatile unsigned char *) PyString_AsString(temp_string_two);
    volatile unsigned char sentinel = 0;
    string_size = PyString_Size(temp_string_one);

    for(int i = 0; i < string_size; i++)
    {
        sentinel |= *left++ ^ *right++;
    }

    return constant_type_compare(sentinel, 0);
}

static PyObject *constant_type_compare(volatile unsigned char sentinel, volatile unsigned char check_byte)
{
    volatile unsigned char z = ~(sentinel ^ check_byte);
    z &= z >> 4;
    z &= z >> 2;
    z &= z >> 1;
    if (z == 1)
    {
        Py_RETURN_TRUE;
    }
    Py_RETURN_FALSE;
}


PyMODINIT_FUNC initconstant_time_compare(void)
{
    PyObject *m;
    m = Py_InitModule("constant_time_compare", ConstantTimeCompareMethods);
    if (m == NULL)
    {
        PyErr_SetString(PyExc_RuntimeError, "Unable to instantiate constant_time_compare");
        return;
    }
}
