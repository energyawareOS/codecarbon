#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#include "libcodecarbon.h"

static int	duration = 1;

static int
check_duration(struct timeval *ptv_start)
{
	struct timeval	tv_check;
	float	elapsed;

	gettimeofday(&tv_check, NULL);
	elapsed = (tv_check.tv_sec - ptv_start->tv_sec) * 1.0;
	elapsed += ((tv_check.tv_usec - ptv_start->tv_usec) / 1000000);
	if (elapsed > (float)duration)
		return 1;
	return 0;
}

static double
do_computation(void)
{
	double result = 0.0;
	struct timeval	tv_start;

	gettimeofday(&tv_start, NULL);

	while (1) {
		for (int i = 0; i < 1000000; i++) {
			result += sin(i) * cos(i) * sqrt(i + 1);
		}

		if (check_duration(&tv_start))
			break;
	}

	return result;
}

void
main(int argc, char *argv[])
{
	codecarbon_result_t	res;

	if (argc > 1) {
		duration = atoi(argv[1]);
	}

	init_libcodecarbon();
	start_codecarbon();

	(void)do_computation();

	stop_codecarbon(&res);

	printf("Energy used: %lf(kWh)\n", res.energy);
	printf("Carbon used: %lf(gCO2eq)\n", res.carbon);

	fini_libcodecarbon();
}
