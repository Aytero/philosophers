#include "philo_bonus.h"

static void	*monitor_status(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		if (!philo->flag_eating && get_time() > philo->time_when_done)
		{
			sem_wait(philo->vars->death_sem);
			write_message(philo->vars, philo->position, HAS_DIED, 1);
			exit(1);
		}
		usleep(50);
	}
	return ((void *)0);
}

static void	take_forks(t_philo *philo)
{
	sem_wait(philo->vars->forks_sem);
	write_message(philo->vars, philo->position, TAKEN_FORK, 0);
	sem_wait(philo->vars->forks_sem);
	write_message(philo->vars, philo->position, TAKEN_FORK, 0);
}

static void	eat(t_philo *philo)
{	
	sem_wait(philo->vars->eat_sem);
	philo->time_when_done = get_time() + philo->vars->time_to_die;
	write_message(philo->vars, philo->position, IS_EATING, 0);
	usleep_divided(get_time() + philo->vars->time_to_eat);
	sem_post(philo->vars->forks_sem);
	sem_post(philo->vars->forks_sem);
	sem_post(philo->vars->eat_sem);
}

int	do_routine(t_philo *philo)
{
	philo->time_when_done = get_time() + philo->vars->time_to_die;
	if (pthread_create(&philo->wid, NULL, monitor_status, philo) != 0)
		free_mem(philo->vars) && exit_error("Pthread error");
	pthread_detach(philo->wid);
	while (1)
	{
		sem_wait(philo->vars->death_sem);
		sem_post(philo->vars->death_sem);
		take_forks(philo);
		philo->flag_eating = 1;
		eat(philo);
		philo->flag_eating = 0;
		if (++philo->eat_cntr == philo->vars->times_must_eat)
			exit(2);
		write_message(philo->vars, philo->position, IS_SLEEPING, 0);
		usleep_divided(get_time() + philo->vars->time_to_sleep);
		write_message(philo->vars, philo->position, IS_THINKING, 0);
	}
	return (1);
}
