
#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define LFORK 0
# define RFORK 1
# define TAKEN_FORK "has taken a fork\n"
# define IS_EATING "is eating\n"
# define IS_SLEEPING "is sleeping\n"
# define IS_THINKING "is thinking\n"
# define HAS_DIED "died\n"

typedef struct s_philo
{
	int				flag_eating;
	int				position;
	int				forks[2];
	uint64_t		time_when_done;
	pthread_mutex_t	eat_mutex;
	struct s_vars	*vars;
}					t_philo;

typedef struct s_vars
{
	int				philo_nbr;
	int				eat_done;
	int				flag_death;
	int				flag_done;
	int				*each_ate;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	//unsigned long long	time_to_eat;
	uint64_t		time_to_sleep;
	int				times_must_eat;
	uint64_t		time_start;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	write_mutex;
//	pthread_mutex_t	death_mutex;
	t_philo			*philo;
}					t_vars;

int					free_mem(t_vars *vars);
int					write_error(char *str, int len);
int					exit_error(char *str);
void				write_message(t_vars *vars, int position, char *str);
void				*do_routine(void *ptr);
void				monitor_status(t_vars *vars);
int					execute(t_vars *vars);
int					init(int argc, char **argv, t_vars *vars);
size_t				ft_strlen(const char *s);
int					ft_atoi(const char *str);
uint64_t			get_time(void);

#endif
