/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obehavka <obehavka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:35:06 by obehavka          #+#    #+#             */
/*   Updated: 2024/11/28 08:46:51 by obehavka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static int	parse_input(int argc, char **argv, t_vars *vars)
{
	vars->number_of_philosophers = ft_atoi(argv[1]);
	vars->time_to_die = ft_atoi(argv[2]) * 1000;
	vars->time_to_eat = ft_atoi(argv[3]) * 1000;
	vars->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		vars->eat_times = ft_atoi(argv[5]);
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

void	initialize_vars(t_vars *vars)
{
	int	i;

	i = 0;
	vars->start_time = 0;
	vars->is_finished = 0;
	while (i < vars->number_of_philosophers)
	{
		vars->philosophers[i].id = i + 1;
		vars->philosophers[i].vars = vars;
		vars->philosophers[i].last_eat = 0;
		vars->philosophers[i].eat_count = 0;
		if (i % 2 == 0)
		{
			vars->philosophers[i].first_fork = i;
			vars->philosophers[i].second_fork = (i + 1)
				% vars->number_of_philosophers;
		}
		else
		{
			vars->philosophers[i].first_fork = (i + 1)
				% vars->number_of_philosophers;
			vars->philosophers[i].second_fork = i;
		}
		++i;
	}
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

int	initialize(t_vars *vars)
{
	if (mutex_array_init(vars->forks, vars->number_of_philosophers))
		return (exit_error("Failed to initialize fork mutex"));
	if (mutex_array_init(vars->last_eat_mutex, vars->number_of_philosophers))
		return (exit_error("Failed to initialize eat count mutex"));
	if (mutex_array_init(vars->eat_count_mutex, vars->number_of_philosophers))
		return (exit_error("Failed to initialize last eat mutex"));
	if (pthread_mutex_init(&vars->print_mutex, NULL))
		return (exit_error("Failed to initialize mutex"));
	if (pthread_mutex_init(&vars->is_finished_mutex, NULL))
		return (exit_error("Failed to initialize mutex"));
	if (pthread_mutex_init(&vars->start_time_mutex, NULL))
		return (exit_error("Failed to initialize mutex"));
	initialize_vars(vars);
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
		return (1);
	mutex_array_destroy(vars.forks, vars.number_of_philosophers);
	mutex_array_destroy(vars.last_eat_mutex, vars.number_of_philosophers);
	mutex_array_destroy(vars.eat_count_mutex, vars.number_of_philosophers);
	pthread_mutex_destroy(&vars.print_mutex);
	pthread_mutex_destroy(&vars.is_finished_mutex);
	pthread_mutex_destroy(&vars.start_time_mutex);
	return (0);
}
