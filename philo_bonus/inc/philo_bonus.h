#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/stat.h>

# define TAKEN_FORK "has taken a fork\n"
# define IS_EATING "is eating\n"
# define IS_SLEEPING "is sleeping\n"
# define IS_THINKING "is thinking\n"
# define HAS_DIED "died\n"

typedef struct s_philo
{
	int					eat_cntr;
	int					position;
	int					flag_eating;
	pthread_t			wid;
	pid_t				pid;
	unsigned long long	time_when_done;
	struct s_vars		*vars;
}						t_philo;

typedef struct s_vars
{
	int					philo_nbr;
	int					eat_cntr;
	int					times_must_eat;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	unsigned long long	time_start;
	sem_t				*forks_sem;
	sem_t				*write_sem;
	sem_t				*write_death_sem;
	sem_t				*death_sem;
	sem_t				*eat_sem;
	t_philo				*philo;
}						t_vars;

void				usleep_divided(unsigned long long to_sleep);
int					kill_processes(t_vars *vars);
int					free_mem(t_vars *vars);
int					write_error(char *str, int len);
int					exit_error(char *str);
void				write_message(t_vars *vars, int position, char *str,
						int flag_death);
int					do_routine(t_philo *philo);
int					execute(t_vars *vars);
int					init(int argc, char **argv, t_vars *vars);
int					ft_atoi(const char *str);
unsigned long long	get_time(void);

#endif
