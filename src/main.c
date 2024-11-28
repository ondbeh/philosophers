/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obehavka <obehavka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:35:06 by obehavka          #+#    #+#             */
/*   Updated: 2024/11/28 14:14:29 by obehavka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	parse_input(int argc, char **argv, t_vars *vars)
{
	vars->number_of_philosophers = ft_atol(argv[1]);
	vars->time_to_die = ft_atol(argv[2]) * 1000;
	vars->time_to_eat = ft_atol(argv[3]) * 1000;
	vars->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (argc == 6)
		vars->eat_times = ft_atol(argv[5]);
	else
		vars->eat_times = -1;
	if (vars->number_of_philosophers < 1)
		return (exit_error("Invalid number of philosophers"));
	if (vars->time_to_die < 30000
		|| vars->time_to_eat < 30000
		|| vars->time_to_sleep < 30000)
		return (exit_error("Invalid time values"));
	if (argc == 6 && vars->eat_times < 0)
		return (exit_error("Invalid number of times to eat"));
	return (0);
}

int	create_threads(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->number_of_philosophers)
	{
		if (pthread_create(&vars->philosophers[i].thread, NULL,
				philo_routine, &vars->philosophers[i]))
			return (exit_error("Failed to create thread"));
		++i;
	}
	if (pthread_create(&vars->observer_thread, NULL, observer_routine, vars))
		return (exit_error("Failed to create observer thread"));
	if (pthread_join(vars->observer_thread, NULL))
		return (exit_error("Failed to join observer thread"));
	i = 0;
	while (i < vars->number_of_philosophers)
	{
		if (pthread_join(vars->philosophers[i].thread, NULL))
			return (exit_error("Failed to join thread"));
		++i;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 5 && argc != 6)
		return (exit_error("Invalid number of arguments"));
	if (parse_input(argc, argv, &vars))
		return (1);
	if (initialize(&vars))
		return (1);
	if (create_threads(&vars))
	{
		write_long(&vars.is_finished, 1, &vars.is_finished_mutex);
		write_long(&vars.start_time, 1, &vars.start_time_mutex);
	}
	clean_mutexes(&vars, (t_mutex_error){NONE, 0});
	return (0);
}
