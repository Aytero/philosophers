#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>

//pthread_mutex_t		mutex;
typedef struct s_philo
{
	int					pos;
	int					flag_eating;
	uint64_t			time_when_done;
	pthread_mutex_t		m;
	struct s_vars		*vars;
}						t_philo;

typedef struct s_vars
{
	int					flag_death;
	pthread_mutex_t		forks;
	pthread_mutex_t		death_m;
	uint64_t			time_start;
	uint64_t			time_to_eat;
	uint64_t			time_to_die;
	uint64_t			time_to_sleep;
	t_philo				*philo;
}						t_vars;

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

//void	*watcher(void *ptr)
void	watcher(void *ptr)
{
	int			i;
	t_vars		*vars;

	vars = (t_vars *)ptr;
	while (1)
	{
		i = -1;
		while (++i < 2)
		{
			//pthread_mutex_lock(&vars->philo[i].m);
			if (!vars->philo[i].flag_eating && get_time() > vars->philo[i].time_when_done)
			{
				printf("%llu philo %d died\n", get_time() - vars->time_start, vars->philo[i].pos);
				vars->flag_death = 1;
				//pthread_mutex_unlock(&vars->philo[i].m);
				//pthread_mutex_unlock(&vars->death_m);
				//exit(0);
				//return ((void *)1);
				return ;
			}
			//pthread_mutex_unlock(&vars->philo[i].m);
			//usleep(1000);
		}
	}
	//return ((void *)0);
}

void	*routine(void *ptr)
{
	t_philo		*philo;
	//pthread_t	wid;

	philo = (t_philo *)ptr;
	philo->time_when_done = get_time() + philo->vars->time_to_die;
	//pthread_create(&wid, NULL, watcher, philo);
	//pthread_detach(wid);
	//sleep(100);
	while (1)
	{
		pthread_mutex_lock(&philo->vars->forks);
		printf("%llu philo %d has taken forks\n", get_time() - philo->vars->time_start,
				(int)philo->pos);
		pthread_mutex_lock(&philo->m);
		philo->flag_eating = 1;
		philo->time_when_done = get_time() + philo->vars->time_to_die;
		printf("%llu philo %d is eating\n", get_time() - philo->vars->time_start,
				philo->pos);
		usleep(philo->vars->time_to_eat * 1000);
		philo->flag_eating = 0;
		pthread_mutex_unlock(&philo->m);
		//printf("%llu philo %d has released forks\n", get_time() - time_start,
		//		(int)philo->pos);
		pthread_mutex_unlock(&philo->vars->forks);
		printf("%llu philo %d is sleeping\n", get_time() - philo->vars->time_start,
				philo->pos);
		usleep(philo->vars->time_to_sleep * 1000);
		printf("%llu philo %d is thinking\n", get_time() - philo->vars->time_start,
				philo->pos);
	}
	return ((void *)0);
}

int	main()
{
	pthread_t	id;
	pthread_t	id1;
	t_vars		vars;



	memset(&vars, 0, sizeof(t_vars));
	vars.philo = malloc(sizeof(t_philo) * 2);
	memset(&vars.philo[0], 0, sizeof(t_philo));
	memset(&vars.philo[1], 0, sizeof(t_philo));
	vars.philo[1].pos = 1;
	vars.philo[0].vars = &vars;
	vars.philo[1].vars = &vars;
	vars.time_to_eat = 100;
	vars.time_to_die = 150;
	vars.time_to_sleep = 200;

	pthread_mutex_init(&vars.philo[0].m, NULL);
	pthread_mutex_init(&vars.philo[1].m, NULL);
//	pthread_mutex_init(&vars.death_m, NULL);
	pthread_mutex_init(&vars.forks, NULL);

//	pthread_mutex_lock(&vars.death_m);

	vars.time_start = get_time();

	/*
	vars.philo[0].time_when_done = get_time() + vars.time_to_die;
	vars.philo[1].time_when_done = get_time() + vars.time_to_die;
	pthread_t	wid;
	pthread_create(&wid, NULL, watcher,& vars);
	pthread_detach(wid);
	sleep(100);
*/
	pthread_create(&id, NULL, routine, &vars.philo[0]);
	pthread_detach(id);
	usleep(100);
	pthread_create(&id1, NULL, routine, &vars.philo[1]);
	pthread_detach(id1);
	usleep(100);

	watcher(&vars);

//	pthread_join(wid, NULL);
//	pthread_join(id, NULL);

//	pthread_mutex_lock(&vars.death_m);
//	pthread_mutex_unlock(&vars.death_m);

	pthread_mutex_destroy(&vars.forks);
	pthread_mutex_destroy(&vars.philo[0].m);
	pthread_mutex_destroy(&vars.philo[1].m);
//	pthread_mutex_destroy(&vars.death_m);

	write(1, "exit\n", 5);
	//exit(0);
	return (0);
}
