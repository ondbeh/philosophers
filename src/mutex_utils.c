/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obehavka <obehavka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:31:23 by obehavka          #+#    #+#             */
/*   Updated: 2024/11/28 13:58:48 by obehavka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	read_long(long *value, pthread_mutex_t *mutex)
{
	long	tmp;

	pthread_mutex_lock(mutex);
	tmp = *value;
	pthread_mutex_unlock(mutex);
	return (tmp);
}

void	write_long(long *value, long new_value, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	*value = new_value;
	pthread_mutex_unlock(mutex);
}

int	mutex_array_destroy(pthread_mutex_t *mutex_array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(&mutex_array[i]);
		++i;
	}
	return (1);
}

int	mutex_array_init(pthread_mutex_t *mutex_array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (pthread_mutex_init(&mutex_array[i], NULL))
			return (i + 1);
		++i;
	}
	return (0);
}

int	clean_mutexes(t_vars *vars, t_mutex_error error)
{
	if (error.type == FORKS)
		return (mutex_array_destroy(vars->forks, error.at));
	mutex_array_destroy(vars->forks, vars->number_of_philosophers);
	if (error.type == LAST_EAT)
		return (mutex_array_destroy(vars->last_eat_mutex, error.at));
	mutex_array_destroy(vars->last_eat_mutex, vars->number_of_philosophers);
	if (error.type == EAT_COUNT)
		return (mutex_array_destroy(vars->eat_count_mutex, error.at));
	mutex_array_destroy(vars->eat_count_mutex, vars->number_of_philosophers);
	if (error.type == PRINT)
		return (1);
	pthread_mutex_destroy(&vars->print_mutex);
	if (error.type == IS_FINISHED)
		return (1);
	pthread_mutex_destroy(&vars->is_finished_mutex);
	if (error.type == START_TIME)
		return (1);
	pthread_mutex_destroy(&vars->start_time_mutex);
	return (0);
}
