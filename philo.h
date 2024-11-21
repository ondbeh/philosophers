/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obehavka <obehavka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:36:03 by obehavka          #+#    #+#             */
/*   Updated: 2024/11/21 09:51:13 by obehavka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>

# define PHILOS_MAX 250

typedef struct s_vars
{
	pthread_t	philosophers[PHILOS_MAX];
	bool		forks[PHILOS_MAX];
	int			number_of_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			eat_times;
}	t_vars;

void	exit_error(char *error_message);
int		ft_atoi(const char *str);

#endif
