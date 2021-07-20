#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

uint64_t	get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);//multiplying affects long time
}

int	main()
{
	uint64_t	time;
	uint64_t	time_end;

	time = get_time();
	//printf("%llu\n", time);

	//usleep(10000);
	sleep(10);
	time_end = get_time();
	printf("%llu\n", time_end - time);
	return (0);
}
