#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <getopt.h>

#include "libcodecarbon.h"

static int	stopped;

static void
handle_signals(int sig)
{
	stopped = 1;
}

static void
setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_signals;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}

static unsigned long
get_elapsed(struct timeval *ptv_start)
{
	struct timeval	tv_check;
	float	elapsed;

	gettimeofday(&tv_check, NULL);
	elapsed = (tv_check.tv_sec - ptv_start->tv_sec) * 1000;
	elapsed += ((tv_check.tv_usec - ptv_start->tv_usec) / 1000);
	return elapsed;
}

static unsigned long
do_wait(void)
{
	struct timeval	tv_start;

	gettimeofday(&tv_start, NULL);

	while (!stopped) {
		usleep(1000000);
	}

	return get_elapsed(&tv_start);
}

int
main(int argc, char *argv[])
{
	codecarbon_result_t	res;
	unsigned long	elapsed;

	init_libcodecarbon();

	start_codecarbon();

	setup_signals();

	printf("Start to monitor carbon emission\n");
	printf("Press Ctrl+C to stopmonitoring..");
	fflush(stdout);

	elapsed = do_wait();

	stop_codecarbon(&res);

	printf("\n");
	printf("Elapsed: %0.3f(sec)\n", elapsed / 1000.0);
	printf("Energy used: %lf(kWh)\n", res.energy);
	printf("Carbon used: %lf(gCO2eq)\n", res.carbon);

	fini_libcodecarbon();

	return 0;
}
