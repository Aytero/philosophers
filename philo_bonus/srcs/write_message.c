#include "philo_bonus.h"

#define PURPLE "\033[0;35m"
#define RESET "\033[0m"
#define HBLU "\e[0;94m"

void	write_message(t_vars *vars, int position, char *str)
{
	sem_wait(vars->write_sem);
	printf("%-8llu "HBLU"%d"RESET" %s", get_time() - vars->time_start,
		position, str);
	sem_post(vars->write_sem);
}
