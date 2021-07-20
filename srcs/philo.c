#include "philo.h"

/*
void	*monitor_eat_cntr(void *ptr)
{
	t_vars	*vars;
	int		eat_cntr;

	vars = (t_vars *)ptr;
	while (1)
	{
		eat_cntr = 0;
		if (vars->each_ate[i] >= vars->times_must_eat)
				eat_cntr++;
		if (eat_cntr >= vars->philo_nbr)
		{	
			//pthread_mutex_lock(&vars->write_mutex);
			return ;
		}
	}
}*/

void	monitor_status(t_vars *vars)
{
	int		i;
	int		eat_cntr;

	while (1)
	{
		eat_cntr = 0;
		i = -1;
		while (++i < vars->philo_nbr)
		{
			//pthread_mutex_lock(&vars->philo[i].eat_mutex);
			if (!vars->philo[i].flag_eating && get_time() > vars->philo[i].time_when_done)
			{
				write_message(vars, vars->philo[i].position, HAS_DIED);
				
				//pthread_mutex_unlock(&vars->philo[i].eat_mutex);
				//pthread_mutex_unlock(&vars->death_m);
				return ;
			}
			if (vars->times_must_eat > 0 && vars->each_ate[i] >= vars->times_must_eat)
				eat_cntr++;
			if (eat_cntr >= vars->philo_nbr)
			{	
				//pthread_mutex_unlock(&vars->philo[i].eat_mutex);
				return ;
			}
			//pthread_mutex_unlock(&vars->philo[i].eat_mutex);
		}
		//usleep(1000);//causes messages after death or eating done
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
		//if (i % 2 == 0)
		//{
			if (pthread_create(&id, NULL, do_routine, &vars->philo[i]) != 0)
				return (0);
			pthread_detach(id);
			usleep(50);
		//}
	}
	/*
	i = -1;
	while (++i < vars->philo_nbr)
	{
		if (i % 2 != 0)
		{
			if (pthread_create(&id, NULL, do_routine, &vars->philo[i]) != 0)
				return (0);
			pthread_detach(id);
			usleep(50);
		}
	}
	*/
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
		return (free_mem(&vars) && exit_error("Pthread error\n"));
	monitor_status(&vars);
	free_mem(&vars);
	return (0);
}
