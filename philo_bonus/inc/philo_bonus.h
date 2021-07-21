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

# define LFORK 0
# define RFORK 1
# define TAKEN_FORK "has taken a fork\n"
# define IS_EATING "is eating\n"
# define IS_SLEEPING "is sleeping\n"
# define IS_THINKING "is thinking\n"
# define HAS_DIED "died\n"

typedef struct s_philo
{
	int				eat_cntr;
	int				position;
	pthread_t		wid;
	pid_t			pid;
	uint64_t		time_when_done;
	struct s_vars	*vars;
}					t_philo;

typedef struct s_vars
{
	int				philo_nbr;
	int				eat_cntr;
	int				flag_death;//
	int				flag_done;//
	int				*each_ate;//
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				times_must_eat;
	uint64_t		time_start;
	sem_t			*forks_sem;
	sem_t			*write_sem;
	sem_t			*death_sem;
	sem_t			*eat_sem;
	t_philo			*philo;
}					t_vars;

int					kill_processes(t_vars *vars);
int					free_mem(t_vars *vars);
int					write_error(char *str, int len);
int					exit_error(char *str);
void				write_message(t_vars *vars, int position, char *str);
int					do_routine(t_philo *philo);
int					execute(t_vars *vars);
int					init(int argc, char **argv, t_vars *vars);
size_t				ft_strlen(const char *s);
int					ft_atoi(const char *str);
uint64_t			get_time(void);

#endif
