#include "philo.h"

void	write_message(t_vars *vars, int position, char *str)
{
	pthread_mutex_lock(&vars->write_mutex);

	printf("%llu philo %d %s", get_time() - vars->time_start, position, str);
	/*
	//write(1, vars->main_time, num);
	ft_putnbr_fd(vars->main_time, 1);

	//philo number
	ft_putnbr_fd(vars->philo[i].position, 1);
	
	write(1, str_type, ft_strlen(str_type));
	*/
	pthread_mutex_unlock(&vars->write_mutex);
}
