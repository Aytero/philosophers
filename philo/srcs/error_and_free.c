#include "philo.h"

int	free_mem(t_vars *vars)
{
	int		i;

	i = -1;
	if (vars->forks_mutex)
	{
		while (++i < vars->philo_nbr)
			pthread_mutex_destroy(&vars->forks_mutex[i]);
		free(vars->forks_mutex);
	}
	if (vars->philo)
		free(vars->philo);
	if (vars->each_ate)
		free(vars->each_ate);
	pthread_mutex_destroy(&vars->write_mutex);
	return (1);
}

int	write_error(char *str, int len)
{
	str && write(1, str, len);
	return (0);
}

int	exit_error(char *str)
{
	str && printf("%s\n", str);
	return (0);
}
