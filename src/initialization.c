/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obehavka <obehavka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:08:22 by obehavka          #+#    #+#             */
/*   Updated: 2024/11/28 14:09:35 by obehavka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	initialize_vars(t_vars *vars)
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

static t_mutex_error	initialize_mutexes(t_vars *vars)
{
	int	at;

	at = mutex_array_init(vars->forks, vars->number_of_philosophers);
	if (at)
		return ((t_mutex_error){FORKS, at - 1});
	at = mutex_array_init(vars->last_eat_mutex, vars->number_of_philosophers);
	if (at)
		return ((t_mutex_error){LAST_EAT, at - 1});
	at = mutex_array_init(vars->eat_count_mutex, vars->number_of_philosophers);
	if (at)
		return ((t_mutex_error){EAT_COUNT, at - 1});
	at = pthread_mutex_init(&vars->print_mutex, NULL);
	if (at)
		return ((t_mutex_error){PRINT, 0});
	at = pthread_mutex_init(&vars->is_finished_mutex, NULL);
	if (at)
		return ((t_mutex_error){IS_FINISHED, 0});
	at = pthread_mutex_init(&vars->start_time_mutex, NULL);
	if (at)
		return ((t_mutex_error){START_TIME, 0});
	return ((t_mutex_error){NONE, 0});
}

int	initialize(t_vars *vars)
{
	t_mutex_error	error;

	error = initialize_mutexes(vars);
	if (error.type != NONE)
	{
		clean_mutexes(vars, error);
		return (exit_error("Failed to initialize mutexes"));
	}
	initialize_vars(vars);
	return (0);
}
