#include "philo.h"

static int	init_mutex(t_vars *vars)
{
	int		i;
	vars->forks_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t *) * vars->philo_nbr);
	if (!vars->forks_mutex)
		return (write_error("Malloc error\n", 13));
	i = -1;
	while (++i < vars->philo_nbr)
	{
		//vars->forks_mutex[i] = (pthread_mutex_t)malloc(sizeof(pthread_mutex_t));
//		if (!vars->forks_mutex[i])
//			return (write_error("Malloc error\n", 13));
		pthread_mutex_init(&vars->forks_mutex[i], NULL);
	}

	pthread_mutex_init(&vars->write_mutex, NULL);
	//pthread_mutex_init(&vars->death_mutex, NULL);
	return (1);
}

static int	init_philo(t_vars *vars)
{
	int		i;

	vars->philo = malloc(sizeof(t_philo) * vars->philo_nbr);
	if (!vars->philo)
		return (write_error("Malloc error\n", 13));
	i = -1;
	while (++i < vars->philo_nbr)
	{
		memset(&vars->philo[i], 0, sizeof(t_philo));
		vars->philo[i].forks[LFORK] = i;
		vars->philo[i].forks[RFORK] = (i + 1) % vars->philo_nbr;
		vars->philo[i].position = i;
		vars->philo[i].vars = vars;
	}
	return (1);
}

int	init(int argc, char **argv, t_vars *vars)
{
	memset(vars, 0, sizeof(t_vars));
	vars->philo_nbr = ft_atoi(argv[1]);
	vars->time_to_die = ft_atoi(argv[2]);
	vars->time_to_eat = ft_atoi(argv[3]);
	vars->time_to_sleep = ft_atoi(argv[4]);
	write(1, "1\n", 2);
	(void)argc;
	//argc == 6 || (vars->times_must_eat = ft_atoi(argv[5]));

	//check validity of params
	if (vars->philo_nbr > 200 || vars->philo_nbr <= 0 || vars->time_to_die < 60
			|| vars->time_to_eat < 60 || vars->time_to_sleep < 60)
		return (write_error("Invalid arguments\n", 18));

	if (!init_philo(vars))
		return (0);
	return (init_mutex(vars));
}
