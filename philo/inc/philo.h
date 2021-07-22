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
	int					position;
	int					flag_eating;
	int					forks[2];
	unsigned long long	time_when_done;
	struct s_vars		*vars;
}						t_philo;

typedef struct s_vars
{
	int					philo_nbr;
	int					eat_cntr;
	int					flag_death;
	int					flag_done;
	int					times_must_eat;
	int					*each_ate;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	unsigned long long	time_start;
	pthread_mutex_t		*forks_mutex;
	pthread_mutex_t		write_mutex;
	t_philo				*philo;
}						t_vars;

void					usleep_divided(unsigned long long to_sleep);
int						free_mem(t_vars *vars);
int						write_error(char *str, int len);
int						exit_error(char *str);
void					write_message(t_vars *vars, int position, char *str);
void					*do_routine(void *ptr);
void					monitor_status(t_vars *vars);
int						execute(t_vars *vars);
int						init(int argc, char **argv, t_vars *vars);
int						ft_atoi(const char *str);
unsigned long long		get_time(void);

#endif
