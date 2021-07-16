
void	*print_message()
{
	phread_mutex_lock(&mutex);

	//

	phread_mutex_unlock(&mutex);
	return (NULL);
}

int	init_mutex()

int	init_philo(t_vars *vars)
{
	int		i;

	i = 0;
	while (i < vars->philo_nbr)
	{
		//memset();
		state->philo[i].left_fork = i;
		state->philo[i].right_fork = (i + 1) % vars->philo_nbr;
	}
}

int	init(int argc, char **argv, t_vars *vars)
{
	memset(vars, 0, sizeof(t_vars));
	vars->philo_nbr = ft_atoi(argv[1]);
	vars->time_to_die = ft_atoi(argv[2]);
	vars->time_to_eat = ft_atoi(argv[3]);
	vars->time_to_sleep = ft_atoi(argv[4]);
	argc == 6 || vars->times_must_eat = ft_atoi(argv[5]);

	//check validity of params
	if (vars->philo_nbr > 200 || vars->time_to_die < 60 || vars->time_to_eat < 60
			|| vars->time_to_sleep < 60)
		return (1);

	vars->philo = ft_calloc(sizeof(t_philo), vars->philo_nbr);
	if (!philo)
		return (0);
	init_philo();
	init_mutex();
	//return (init_mutex());
	return (0);
}
