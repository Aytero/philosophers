
#include "philo.h"

void	monitor_status(t_vars *vars)
{
	int			i;

	while (1)
	{
		i = -1;
		while (++i < vars->philo_nbr)
		{
			//pthread_mutex_lock(&vars->philo[i].m);
			if (!vars->philo[i].flag_eating && get_time() > vars->philo[i].time_when_done)
			{
				write_message(vars, vars->philo[i].position, HAS_DIED);
				
				//vars->flag_death = 1;
				//pthread_mutex_unlock(&vars->philo[i].m);
				//pthread_mutex_unlock(&vars->death_m);
				return ;
			}
			//pthread_mutex_unlock(&vars->philo[i].m);
			//usleep(1000);
		}
	}
}

int	execute(t_vars *vars)
{
	pthread_t	id;
	int			i;

	vars->time_start = get_time();
	if (vars->times_must_eat > 0)
		;
	i = -1;
	while (++i < vars->philo_nbr)
	{
		if (pthread_create(&id, NULL, do_routine, &vars->philo[i]) != 0)
			return (0);
		pthread_detach(id);
		usleep(50);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc < 5 || argc > 6)
		return (exit_error("Invalid number of arguments\n"));
	if (!init(argc, argv, &vars))
		return (free_mem(&vars) && exit_error(NULL));
	//vars.time_start = get_time();
	if (!execute(&vars))
		return (free_mem(&vars) && exit_error(NULL));
	//main mutex
	monitor_status(&vars);
	free_mem(&vars);
	return (0);
}
