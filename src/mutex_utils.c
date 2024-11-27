/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obehavka <obehavka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:31:23 by obehavka          #+#    #+#             */
/*   Updated: 2024/11/27 12:48:05 by obehavka         ###   ########.fr       */
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
			return (mutex_array_destroy(mutex_array, i));
		++i;
	}
	return (0);
}
