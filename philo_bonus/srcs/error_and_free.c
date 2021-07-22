#include "philo_bonus.h"

int	free_mem(t_vars *vars)
{
	sem_unlink("/forks_sem");
	sem_unlink("/write_sem");
	sem_unlink("/write_death_sem");
	sem_unlink("/death_sem");
	sem_unlink("/eat_sem");
	if (vars->philo)
		free(vars->philo);
	return (1);
}

int	kill_processes(t_vars *vars)
{
	int		i;

	i = -1;
	while (++i < vars->philo_nbr)
		kill(vars->philo[i].pid, SIGKILL);
	sem_post(vars->death_sem);
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
	exit(1);
}
