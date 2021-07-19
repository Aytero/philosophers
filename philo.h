
#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_philo
{
	int				info;
}					t_philo;

typedef struct s_vars
{
	int				philo_number;
	uint64_t		time_to_live;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	uint64_t		times_must_eat;
	uint64_t		start_time;
	phread_mutex_t	*forks_mutex;
	phread_mutex_t	*write_mutex;
	phread_mutex_t	*death_mutex;
	t_philo			*philo;
}					t_vars;

size_t				ft_strlen(const char *s);
int					ft_atoi(const char *str);
uint64_t			get_time(void);

#endif
