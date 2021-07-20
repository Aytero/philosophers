#include "philo.h"

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->forks_mutex[philo->forks[LFORK]]);
	write_message(philo->vars, philo->position, TAKEN_FORK);
	pthread_mutex_lock(&philo->vars->forks_mutex[philo->forks[RFORK]]);
	write_message(philo->vars, philo->position, TAKEN_FORK);
}

static void	eat(t_philo *philo)
{	
	pthread_mutex_lock(&philo->eat_mutex);
	write_message(philo->vars, philo->position, IS_EATING);
	philo->flag_eating = 1;
	philo->time_when_done = get_time() + philo->vars->time_to_die;
	usleep(philo->vars->time_to_eat * 1000);
	philo->flag_eating = 0;
	pthread_mutex_unlock(&philo->eat_mutex);
}

static void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->vars->forks_mutex[philo->forks[RFORK]]);
	pthread_mutex_unlock(&philo->vars->forks_mutex[philo->forks[LFORK]]);
	write_message(philo->vars, philo->position, IS_SLEEPING);
	usleep(philo->vars->time_to_sleep * 1000);
}

void	*do_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		take_forks(philo);
		eat(philo);
		release_forks(philo);
		write_message(philo->vars, philo->position, IS_THINKING);
	}
	return ((void *)0);
}

/*
void	*_do_routine(void *ptr)
{
	t_philo		*philo;

	philo = (t_philo *)ptr;
	philo->time_when_done = get_time() + philo->vars->time_to_die;//
	while (1)
	{
		pthread_mutex_lock(&philo->eat_mutex);
		philo->flag_eating = 1;
		philo->time_when_done = get_time() + philo->vars->time_to_die;
		usleep(philo->vars->time_to_eat * 1000);
		philo->flag_eating = 0;
		pthread_mutex_unlock(&philo->eat_mutex);
		pthread_mutex_unlock(&philo->vars->forks);
		usleep(philo->vars->time_to_sleep * 1000);
	}
	return ((void *)0);
}
*/
