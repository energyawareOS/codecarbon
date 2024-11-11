#include "libcodecarbon.h"

void
main(int argc, char *argv[])
{
	init_libcodecarbon();
	start_libcodecarbon();
	/* some computions*/
	stop_libcodecarbon();
	fini_libcodecarbon();
}
