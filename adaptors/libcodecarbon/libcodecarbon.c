#include <Python.h>

void
init_libcodecarbon(void)
{
	Py_Initialize();
	PyRun_SimpleString("from codecarbon import EmissionsTracker");
	PyRun_SimpleString("tracker = EmissionsTracker()");
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

void
end_codecarbon(void)
{
	PyRun_SimpleString("emissions: float = tracker.stop()");
	PyRun_SimpleString("print(emissions)");
}
