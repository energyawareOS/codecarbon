#ifndef _LIBCODECARBON_H_
#define _LIBCODECARBON_H_

typedef struct {
	double	energy;		/* kWh */
	double	carbon;		/* g CO2eq */
} codecarbon_result_t;

void
init_libcodecarbon(void);

void
fini_libcodecarbon(void);

void
start_codecarbon(void);

int
stop_codecarbon(codecarbon_result_t *pres);

#endif
