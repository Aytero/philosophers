#include "philo.h"

void	write_message(t_vars *vars, int position, char *str)
{
	pthread_mutex_lock(&vars->write_mutex);
	printf("%llu philo %d %s", get_time() - vars->time_start, position, str);
	pthread_mutex_unlock(&vars->write_mutex);
}
