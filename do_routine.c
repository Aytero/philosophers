#include "philo.h"

void	take_forks()
{
	pthread_mutex_lock(&vars->forks_mutex[philo->forks[LFORK]]);
	write_message(philo->position, TAKEN_FORK);

	pthread_mutex_lock(&vars->forks_mutex[philo->forks[RFORK]]);
	write_message(philo->position, TAKEN_FORK);
}

void	eat()
{
	if (not dead)
	{
		//flag && counter
		//eating mutex ?
		write_message(philo->position, IS_EATING);
		usleep(vars->time_to_eat * 1000);
	}
}

void	release_forks()
{
	pthread_mutex_unlock(&vars->forks_mutex[philo->forks[RFORK]]);
	pthread_mutex_unlock(&vars->forks_mutex[philo->forks[LFORK]]);
	write_message(philo->position, IS_SLEEPING);
	usleep(vars->time_to_sleep * 1000);
	//think
	write_message(philo->position, IS_THINKING);
}

void	*do_routine(void *ptr)
{
	t_vars	*vars;

	vars = ptr;
	while (1)
	{
		take_forks();
		eat();
		release_forks();
		//think
	}
	return ((void *)0);
}
