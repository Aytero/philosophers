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
	uint64_t	time_tmp;

	philo->time_when_done = get_time() + philo->vars->time_to_die;
	write_message(philo->vars, philo->position, IS_EATING);
	philo->flag_eating = 1;
	time_tmp = get_time() + philo->vars->time_to_eat;
	while (get_time() <= time_tmp)
		usleep(100);
	if (philo->vars->times_must_eat)
		philo->vars->each_ate[philo->position - 1] += 1;
	philo->flag_eating = 0;
	pthread_mutex_unlock(&philo->vars->forks_mutex[philo->forks[RFORK]]);
	pthread_mutex_unlock(&philo->vars->forks_mutex[philo->forks[LFORK]]);
}

void	*do_routine(void *ptr)
{
	uint64_t	time_tmp;
	t_philo		*philo;

	philo = (t_philo *)ptr;
	philo->time_when_done = get_time() + philo->vars->time_to_die;
	while (1)
	{
		if (philo->vars->flag_death || philo->vars->flag_done)
			break ;
		take_forks(philo);
		eat(philo);
		if (philo->vars->times_must_eat > 0
			&& philo->vars->each_ate[philo->position - 1]
			== philo->vars->times_must_eat)
			break ;
		write_message(philo->vars, philo->position, IS_SLEEPING);
		time_tmp = get_time() + philo->vars->time_to_eat;
		while (get_time() <= time_tmp)
			usleep(100);
		write_message(philo->vars, philo->position, IS_THINKING);
	}
	return ((void *)0);
}
