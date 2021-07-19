#include "philo.h"

void	*write_message()
{
	phread_mutex_lock(&vars->write_mutex);

	//
	//write(1, vars->main_time, num);
	ft_putnbr_fd(vars->main_time, 1);

	//philo number
	ft_putnbr_fd(vars->philo[i].position, 1);
	
	write(1, str_type, ft_strlen(str_type));

	phread_mutex_unlock(&vars->write_mutex);
	return (NULL);
}
