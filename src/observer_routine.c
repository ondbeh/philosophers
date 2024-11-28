/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obehavka <obehavka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:34:53 by obehavka          #+#    #+#             */
/*   Updated: 2024/11/28 11:51:50 by obehavka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	check_philo_dead(t_vars *vars, int index)
{
	t_philo	*philo;
	long	d_time;

	philo = &vars->philosophers[index];
	d_time = ft_gettime()
		- read_long(&philo->last_eat, &vars->last_eat_mutex[index]);
	if (d_time > vars->time_to_die)
	{
		announce(DIE, philo);
		write_long(&vars->is_finished, 1, &vars->is_finished_mutex);
		return (1);
	}
	return (0);
}

void	*observer_routine(void *void_vars)
{
	t_vars	*vars;
	int		i;
	int		all_full;

	vars = (t_vars *)void_vars;
	write_long(&vars->start_time, ft_gettime(), &vars->start_time_mutex);
	while (!read_long(&vars->is_finished, &vars->is_finished_mutex))
	{
		all_full = 1;
		ft_usleep(500);
		i = 0;
		while (i < vars->number_of_philosophers)
		{
			if (check_philo_dead(vars, i))
				break ;
			if (read_long(&vars->philosophers[i].eat_count,
					&vars->eat_count_mutex[i]) < vars->eat_times)
				all_full = 0;
			++i;
		}
		if (all_full && vars->eat_times > -1)
			write_long(&vars->is_finished, 1, &vars->is_finished_mutex);
	}
	return (NULL);
}
