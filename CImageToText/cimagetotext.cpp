#include <Python.h>
#include "ImageToTextConverter.h"

static PyObject *
cimagetotext_convert_image(PyObject *self, PyObject *args)
{
    const char *output = "Hello world!";
    return PyUnicode_FromString(output);
}

static PyMethodDef CImageToTextMethods[] = {
    {"convert_image", cimagetotext_convert_image, METH_VARARGS,
     "Return an image converted to text"},
    {NULL, NULL, 0, NULL} /* Sentinel */
};

static struct PyModuleDef cimagetotext = {
    PyModuleDef_HEAD_INIT,
    "cimagetotext", /* name of module */
    NULL,           /* module documentation, may be NULL */
    -1,             /* size of per-interpreter state of the module,
                      or -1 if the module keeps state in global variables */
    CImageToTextMethods};

PyMODINIT_FUNC
PyInit_cimagetotext(void)
{
    return PyModule_Create(&cimagetotext);
}