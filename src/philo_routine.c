/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obehavka <obehavka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:48:45 by obehavka          #+#    #+#             */
/*   Updated: 2024/11/28 11:53:24 by obehavka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	philo_think(t_philo *philo)
{
	announce(THINK, philo);
	if (philo->vars->number_of_philosophers % 2)
		ft_usleep(philo->vars->time_to_eat / 10);
}

static void	philo_eat(t_philo *philo)
{
	t_vars	*vars;
	long	eat_count;
	int		id;

	vars = philo->vars;
	id = philo->id - 1;
	eat_count = read_long(&philo->eat_count, &vars->eat_count_mutex[id]);
	pthread_mutex_lock(&vars->forks[philo->first_fork]);
	announce(FORK, philo);
	if (philo->first_fork == philo->second_fork)
	{
		pthread_mutex_unlock(&vars->forks[philo->first_fork]);
		ft_usleep(vars->time_to_die * 2);
		return ;
	}
	pthread_mutex_lock(&vars->forks[philo->second_fork]);
	announce(FORK, philo);
	announce(EAT, philo);
	write_long(&philo->last_eat, ft_gettime(), &vars->last_eat_mutex[id]);
	write_long(&philo->eat_count, eat_count + 1, &vars->eat_count_mutex[id]);
	ft_usleep(vars->time_to_eat);
	pthread_mutex_unlock(&vars->forks[philo->first_fork]);
	pthread_mutex_unlock(&vars->forks[philo->second_fork]);
}

static void	philo_sleep(t_philo *philo)
{
	announce(SLEEP, philo);
	ft_usleep(philo->vars->time_to_sleep);
}

void	*philo_routine(void *void_philo)
{
	t_philo	*philo;
	t_vars	*vars;
	int		index;
	long	start_time;

	philo = (t_philo *)void_philo;
	vars = philo->vars;
	index = philo->id - 1;
	start_time = read_long(&vars->start_time, &vars->start_time_mutex);
	while (start_time == 0)
		start_time = read_long(&vars->start_time, &vars->start_time_mutex);
	write_long(&philo->last_eat, start_time, &vars->last_eat_mutex[index]);
	while (!read_long(&vars->is_finished, &vars->is_finished_mutex))
	{
		if (philo->id % 2 == 0
			&& read_long(&philo->eat_count, &vars->eat_count_mutex[index]) == 0)
			philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
