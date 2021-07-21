#include "philo_bonus.h"

static void	*monitor_status(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		if (get_time() > philo->time_when_done)
		{
			sem_wait(philo->vars->death_sem);
			write_message(philo->vars, philo->position, HAS_DIED);
			exit(1);
		}
	}
	return ((void *)0);
}

static void	take_forks(t_philo *philo)
{
	sem_wait(philo->vars->eat_sem);
	sem_wait(philo->vars->forks_sem);
	write_message(philo->vars, philo->position, TAKEN_FORK);
	sem_wait(philo->vars->forks_sem);
	write_message(philo->vars, philo->position, TAKEN_FORK);
}

static void	eat(t_philo *philo)
{	
	uint64_t	time_tmp;

	philo->time_when_done = get_time() + philo->vars->time_to_die;
	write_message(philo->vars, philo->position, IS_EATING);
	time_tmp = get_time() + philo->vars->time_to_eat;
	while (get_time() <= time_tmp)
		usleep(100);
	if (philo->vars->times_must_eat > 0)
		philo->vars->each_ate[philo->position - 1] += 1;
	sem_post(philo->vars->forks_sem);
	sem_post(philo->vars->forks_sem);
	sem_post(philo->vars->eat_sem);
}

int	do_routine(t_philo *philo)
{
	uint64_t	time_tmp;

	philo->time_when_done = get_time() + philo->vars->time_to_die;
	if (pthread_create(&philo->wid, NULL, monitor_status, philo) != 0)
		free_mem(philo->vars) && exit_error("Pthread error\n");//Error: pthread creation failed
	pthread_detach(philo->wid);
	while (1)
	{
		sem_wait(philo->vars->death_sem);
		sem_post(philo->vars->death_sem);
		take_forks(philo);
		eat(philo);
		if (philo->vars->times_must_eat && ++philo->eat_cntr
			== philo->vars->times_must_eat)
			exit(2);
		write_message(philo->vars, philo->position, IS_SLEEPING);
		time_tmp = get_time() + philo->vars->time_to_eat;
		while (get_time() <= time_tmp)
			usleep(100);
		write_message(philo->vars, philo->position, IS_THINKING);
	}
	return (1);
}
