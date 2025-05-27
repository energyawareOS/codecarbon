#include <Python.h>
#include <stdlib.h>

#include "libcodecarbon.h"

void
init_libcodecarbon(void)
{
	if (getenv("CODECARBON_LOG_LEVEL") == NULL) {
		/* Suppress verbose output by setting log level to critical,
		 * unless explicitly overridden by environment variable.
		 */
		setenv("CODECARBON_LOG_LEVEL", "critical", 1);
	}

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

int
stop_codecarbon(codecarbon_result_t *pres)
{
	PyRun_SimpleString("carbon: float = tracker.stop() * 1000; energy: float = tracker._total_energy.kWh");

	PyObject	*main_module = PyImport_AddModule("__main__");
	PyObject	*dict = PyModule_GetDict(main_module);
	PyObject	*py_carbon = PyDict_GetItemString(dict, "carbon");
	PyObject	*py_energy = PyDict_GetItemString(dict, "energy");

	if (py_carbon && py_energy && PyFloat_Check(py_carbon) && PyFloat_Check(py_energy)) {
		pres->carbon = PyFloat_AsDouble(py_carbon);
		pres->energy = PyFloat_AsDouble(py_energy);
		return 0;
	}
	return -1;
}
