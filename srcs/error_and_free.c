#include "philo.h"

int	free_mem(t_vars *vars)
{
	int		i;

	i = -1;
	while (++i < vars->philo_nbr)
	{
		pthread_mutex_destroy(&vars->philo[i].eat_mutex);
		pthread_mutex_destroy(&vars->forks_mutex[i]);
	}
	pthread_mutex_destroy(&vars->write_mutex);
	//pthread_mutex_destroy(&vars->death_mutex);
	return (1);
}

int	write_error(char *str, int len)
{
	if (str)
		write(1, str, len);
	return (0);
}

int	exit_error(char *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	exit(0);
}
