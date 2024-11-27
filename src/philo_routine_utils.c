/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obehavka <obehavka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:09:56 by obehavka          #+#    #+#             */
/*   Updated: 2024/11/27 14:30:22 by obehavka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	announce(char *message, t_philo *philo)
{
	long	time;

	time = (ft_getcurrenttime() - philo->vars->start_time) / 1000;
	if (read_long(&philo->vars->is_finished, &philo->vars->is_finished_mutex))
	{
		printf("is finished\n");
		return ;
	}
	pthread_mutex_lock(&philo->vars->print_mutex);
	printf("%ld %ld %s\n", time, philo->id, message);
	pthread_mutex_unlock(&philo->vars->print_mutex);
}
