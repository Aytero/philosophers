#include "philo.h"

void	monitor_status(t_vars *vars)
{
	int		i;

	while (1)
	{
		vars->eat_cntr = 0;
		i = -1;
		while (++i < vars->philo_nbr)
		{
			if (!vars->philo[i].flag_eating && get_time()
				> vars->philo[i].time_when_done)
			{
				vars->flag_death = 1;
				write_message(vars, vars->philo[i].position, HAS_DIED);
				return ;
			}
			(vars->times_must_eat && vars->each_ate[i] >= vars->times_must_eat)
				&& vars->eat_cntr++;
			if (vars->eat_cntr >= vars->philo_nbr)
			{	
				vars->flag_done = 1;
				return ;
			}
		}
		usleep(50);
	}
}

int	execute(t_vars *vars)
{
	pthread_t	id;
	int			i;

	vars->time_start = get_time();
	i = -1;
	while (++i < vars->philo_nbr)
	{
		if (pthread_create(&id, NULL, do_routine, &vars->philo[i]) != 0)
			return (0);
		pthread_detach(id);
		(i % 2 == 0) && usleep(50);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	(argc < 5 || argc > 6) && exit_error("Invalid number of arguments");
	init(argc, argv, &vars) || (free_mem(&vars) && exit_error(NULL));
	execute(&vars) || (free_mem(&vars) && exit_error("Pthread error"));
	usleep(50);
	monitor_status(&vars);
	free_mem(&vars);
	return (0);
}
