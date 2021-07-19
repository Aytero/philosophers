#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>

//pthread_mutex_t		mutex;
pthread_mutex_t		forks;
pthread_mutex_t		death_m;
uint64_t			time_start;
int					death;

uint64_t			time_to_eat = 100;
uint64_t			time_to_die = 350;
uint64_t			time_to_sleep = 200;

typedef struct s_philo
{
	int					pos;
	int					flag_eating;
	uint64_t			time_when_done;
	pthread_mutex_t		m;
}						t_philo;


uint64_t	get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * (uint64_t)1000 + tv.tv_usec / 1000);//multiplying affects long time
}

/*
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
*/

void	*watcher(void *ptr)
{
	int			i;
	t_philo		*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		i = -1;
		//while (++i < 2)
		//{
			//pthread_mutex_lock(&vars->philo[i].m);
			pthread_mutex_lock(&philo->m);
			if (!philo->flag_eating && get_time() > philo->time_when_done)
			{
				death = 1;
				printf("%llu philo %d died\n", get_time() - time_start, philo->pos);
				pthread_mutex_unlock(&philo->m);
				pthread_mutex_unlock(&death_m);
				exit(0);
				return ((void *)1);
			}
			pthread_mutex_unlock(&philo->m);
			usleep(1000);
		//}
	}
	return ((void *)0);
}

void	*routine(void *ptr)
{
	t_philo		*philo;
	pthread_t	wid;

	philo = (t_philo *)ptr;
	philo->time_when_done = get_time() + time_to_die;
	pthread_create(&wid, NULL, watcher, philo);
	pthread_detach(wid);
	usleep(100);
	while (1)
	{
		pthread_mutex_lock(&forks);
		printf("%llu philo %d has taken forks\n", get_time() - time_start,
				(int)philo->pos);
		pthread_mutex_lock(&philo->m);
		philo->flag_eating = 1;
		philo->time_when_done = get_time() + time_to_die;
		printf("%llu philo %d is eating\n", get_time() - time_start, philo->pos);
		usleep(time_to_eat * 1000);
		philo->flag_eating = 0;
		pthread_mutex_unlock(&philo->m);
		//printf("%llu philo %d has released forks\n", get_time() - time_start,
		//		(int)philo->pos);
		pthread_mutex_unlock(&forks);
		printf("%llu philo %d is sleeping\n", get_time() - time_start, philo->pos);
		usleep(time_to_sleep * 1000);
		printf("%llu philo %d is thinking\n", get_time() - time_start, philo->pos);
	}
	return ((void *)0);
}

int	main()
{
//	char		*str = "shi\n";
//	char		*str1 = "ni\n";
	pthread_t	id;
	pthread_t	id1;

	time_start = get_time();


	t_philo		*philo;
	philo = malloc(sizeof(t_philo) * 2);
	memset(&philo[0], 0, sizeof(t_philo));
	memset(&philo[1], 0, sizeof(t_philo));
	philo[1].pos = 1;
	pthread_mutex_init(&philo[0].m, NULL);
	pthread_mutex_init(&philo[1].m, NULL);
	pthread_mutex_init(&death_m, NULL);

	pthread_mutex_init(&forks, NULL);
//	pthread_create(&id, NULL, print_func, (void *)str);
//	pthread_create(&id1, NULL, print_func, (void *)str1);
//	pthread_create(&id, NULL, func, NULL);
//	pthread_create(&id1, NULL, func, NULL);


	pthread_create(&id, NULL, routine, &philo[0]);
//	pthread_detach(id);
	usleep(100);
	pthread_create(&id1, NULL, routine, &philo[1]);
	pthread_detach(id1);
	usleep(100);

//	pthread_join(wid, NULL);
	pthread_join(id, NULL);
//	pthread_join(id1, NULL);

	pthread_mutex_lock(&death_m);
	pthread_mutex_unlock(&death_m);

	pthread_mutex_destroy(&forks);
	pthread_mutex_destroy(&philo[0].m);
	pthread_mutex_destroy(&philo[1].m);
	pthread_mutex_destroy(&death_m);

	write(1, "exit\n", 5);
	//exit(0);
	return (0);
}
