#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>

pthread_mutex_t		mutex;
uint64_t			time_start;

uint64_t	get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * (uint64_t)1000 + tv.tv_usec / 1000);//multiplying affects long time
}

void	*func()
{
	uint64_t	time_end;

	pthread_mutex_lock(&mutex);
	write(1, "wait 3 sec\n", 11);
	sleep(3);
	time_end = get_time();
	printf("time passed %llu\n", time_end - time_start);
	pthread_mutex_unlock(&mutex);
	return (NULL);
}

void	*print_func(void *buf)
{
	int		i;

	pthread_mutex_lock(&mutex);
	i = 0;
	while (i < 10)
	{
		write(1, (char *)buf, strlen(buf));
		usleep(100000);
		i++;
	}
	pthread_mutex_unlock(&mutex);
	return (NULL);
}

int	main()
{
//	char		*str = "shi\n";
//	char		*str1 = "ni\n";
	pthread_t	id;
	pthread_t	id1;

	time_start = get_time();

	pthread_mutex_init(&mutex, NULL);
//	pthread_create(&id, NULL, print_func, (void *)str);
//	pthread_create(&id1, NULL, print_func, (void *)str1);
	pthread_create(&id, NULL, func, NULL);
	pthread_create(&id1, NULL, func, NULL);
	pthread_join(id, NULL);
	pthread_join(id1, NULL);
	pthread_mutex_destroy(&mutex);

	write(1, "exit\n", 5);
	//exit(0);
	return (0);
}
