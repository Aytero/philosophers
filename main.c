
#include "philo.h"

int	execute(t_vars *vars)
{
	pthread_t	id;
	int			i;

	if (vars->times_must_eat > 0)
		;
	i = -1;
	while (++i < vars->philo_nbr)
	{
		if (pthread_create(&id, NULL, do_routine, (void *)vars) != 0)
			return (0);
		pthread_detach(id);
		usleep(50);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc < 5 || argc > 6)
		return (exit_error("Invalid number of arguments\n"));
	if (!init(argc, argv, &vars))
		return (free_mem(&vars) && exit_error("Invalid number of arguments\n"));
	if (!execute(&vars))
		return (free_mem(&vars) && exit_error("Invalid number of arguments\n"));
	//main mutex
	free_mem(&vars);
	return (0);
}
