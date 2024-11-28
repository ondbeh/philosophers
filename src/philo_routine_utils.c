/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obehavka <obehavka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:09:56 by obehavka          #+#    #+#             */
/*   Updated: 2024/11/28 10:01:38 by obehavka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	announce(char *message, t_philo *philo)
{
	long	time;
	long	start_time;
	long	is_finished;

	start_time = read_long(&philo->vars->start_time,
			&philo->vars->start_time_mutex);
	is_finished = read_long(&philo->vars->is_finished,
			&philo->vars->is_finished_mutex);
	time = (ft_getcurrenttime() - start_time) / 1000;
	if (is_finished)
		return ;
	pthread_mutex_lock(&philo->vars->print_mutex);
	printf("%ld %ld %s\n", time, philo->id, message);
	pthread_mutex_unlock(&philo->vars->print_mutex);
}
