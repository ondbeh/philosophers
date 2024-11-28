/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obehavka <obehavka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:34:53 by obehavka          #+#    #+#             */
/*   Updated: 2024/11/28 10:01:36 by obehavka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*observer_routine(void *void_vars)
{
	t_vars	*vars;
	int		i;
	t_philo	*philo;
	long	problem_time;
	int		all_full;

	vars = (t_vars *)void_vars;
	write_long(&vars->start_time, ft_getcurrenttime(), &vars->start_time_mutex);
	while(!read_long(&vars->is_finished, &vars->is_finished_mutex))
	{
		all_full = 1;
		ft_usleep(500);
		i = 0;
		while (i < vars->number_of_philosophers)
		{

			philo = &vars->philosophers[i];
			problem_time = ft_getcurrenttime() - read_long(&philo->last_eat, &vars->last_eat_mutex[i]);
			if (problem_time > vars->time_to_die)
			{
				announce("died", philo);
				write_long(&vars->is_finished, 1, &vars->is_finished_mutex);
				return (NULL);
			}
			if (read_long(&philo->eat_count, &vars->eat_count_mutex[i]) < vars->eat_times)
				all_full = 0;
			++i;
		}
		if (all_full && vars->eat_times > -1)
			write_long(&vars->is_finished, 1, &vars->is_finished_mutex);
	}
	return (NULL);
}
