
#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>

# define LFORK 0
# define RFORK 1

typedef struct s_philo
{
	int				flag_eating;;
	int				position;
	int				forks[2];
	uint64_t		start;
	pthread_mutex_t	eating_mutex;
}					t_philo;

typedef struct s_vars
{
	int				philo_nbr;
	uint64_t		time_to_live;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				times_must_eat;
	uint64_t		start_time;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	*write_mutex;
	pthread_mutex_t	*death_mutex;
	t_philo			*philo;
}					t_vars;

size_t				ft_strlen(const char *s);
int					ft_atoi(const char *str);
uint64_t			get_time(void);

#endif
