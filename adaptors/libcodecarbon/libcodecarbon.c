#include <Python.h>

void
init_libcodecarbon(void)
{
	Py_Initialize();

	PyRun_SimpleString("from codecarbon import EmissionsTracker; tracker = EmissionsTracker()");
}

void
fini_libcodecarbon(void)
{
	Py_Finalize();
}

void
start_codecarbon(void)
{
	PyRun_SimpleString("tracker.start()");
}

double
stop_codecarbon(void)
{
	PyRun_SimpleString("emissions: float = tracker.stop()");

	PyObject	*main_module = PyImport_AddModule("__main__");
	PyObject	*dict = PyModule_GetDict(main_module);
	PyObject	*py_emissions = PyDict_GetItemString(dict, "emissions");

	if (py_emissions && PyFloat_Check(py_emissions))
		return PyFloat_AsDouble(py_emissions);
	return 0;
}
