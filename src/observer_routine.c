/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obehavka <obehavka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:34:53 by obehavka          #+#    #+#             */
/*   Updated: 2024/11/27 16:03:10 by obehavka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*observer_routine(void *void_vars)
{
	t_vars	*vars;
	long	time;
	int		i;
	t_philo	*philo;
	long	problem_time;

	vars = (t_vars *)void_vars;
	time = ft_getcurrenttime();
	printf("start time: %ld\n", time);
	write_long(&vars->start_time, time, &vars->start_time_mutex);
	while(!read_long(vars->is_finished, &vars->is_finished_mutex))
	{
		ft_usleep(50);
		i = 0;
		while (i < vars->number_of_philosophers)
		{
			philo = &vars->philosophers[i];
			problem_time = ft_getcurrenttime() - read_long(philo->last_eat, &vars->last_eat_mutex[i]);
			if (problem_time > vars->time_to_die)
			{
				pthread_mutex_lock(&vars->print_mutex);
				printf("problem_time: %ld\n", problem_time);
				printf("current time: %ld\n",ft_getcurrenttime() - read_long(vars->start_time, &vars->start_time_mutex));
				printf("last eat: %ld\n", ft_getcurrenttime() - read_long(philo->last_eat, &vars->last_eat_mutex[i]));
				printf("time to die: %ld\n", vars->time_to_die);
				printf("%ld %d died\n", ft_getcurrenttime() - read_long(vars->start_time, &vars->start_time_mutex), i + 1);
				pthread_mutex_unlock(&vars->print_mutex);
				//write_long(&vars->is_finished, 1, &vars->is_finished_mutex);
				return (NULL);
			}
			++i;
		}
	}
	return (NULL);
}
