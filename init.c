#include "philo.h"

int	init_mutex()
{
	pthread_mutex_init(&, NULL);
}

int	init_philo(t_vars *vars)
{
	int		i;

	i = -1;
	while (++i < vars->philo_nbr)
	{
		memset(vars->philo[i], 0, sizeof(t_philo));
		vars->philo[i].forks[LFORK] = i;
		vars->philo[i].forks[RFORK] = (i + 1) % vars->philo_nbr;
		vars->philo[i].position = i;
	}
}

int	init(int argc, char **argv, t_vars *vars)
{
	memset(vars, 0, sizeof(t_vars));
	vars->philo_nbr = ft_atoi(argv[1]);
	vars->time_to_die = ft_atoi(argv[2]);
	vars->time_to_eat = ft_atoi(argv[3]);
	vars->time_to_sleep = ft_atoi(argv[4]);
	argc == 6 || vars->times_must_eat = ft_atoi(argv[5]);

	//check validity of params
	if (vars->philo_nbr > 200 || vars->time_to_die < 60 || vars->time_to_eat < 60
			|| vars->time_to_sleep < 60)
		return (1);

	vars->philo = ft_calloc(sizeof(t_philo), vars->philo_nbr);
	if (!philo)
		return (0);
	init_philo();
	init_mutex();
	//return (init_mutex());
	return (0);
}
