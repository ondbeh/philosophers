/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obehavka <obehavka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:34:53 by obehavka          #+#    #+#             */
/*   Updated: 2024/11/27 14:22:38 by obehavka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*observer_routine(void *void_vars)
{
	t_vars	*vars;
	long	time;
	int		i;
	t_philo	*philo;

	vars = (t_vars *)void_vars;
	time = ft_getcurrenttime();
	write_long(&vars->start_time, time, &vars->last_eat_mutex[0]);
	while(!read_long(&vars->is_finished, &vars->is_finished_mutex))
	{
		ft_usleep(100);
		i = 0;
		while (i < vars->number_of_philosophers)
		{
			philo = &vars->philosophers[i];
			if (ft_getcurrenttime() - read_long(&philo->last_eat, &vars->last_eat_mutex[i]) > vars->time_to_die)
			{
				pthread_mutex_lock(&vars->print_mutex);
				printf("%ld %d died\n", ft_getcurrenttime() - read_long(&vars->start_time, &vars->last_eat_mutex[i]), i + 1);
				pthread_mutex_unlock(&vars->print_mutex);
				write_long(&vars->is_finished, 1, &vars->is_finished_mutex);
				return (NULL);
			}
			++i;
		}
	}
	return (NULL);
}
