/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obehavka <obehavka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:36:03 by obehavka          #+#    #+#             */
/*   Updated: 2024/11/27 15:47:13 by obehavka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

# define PHILOS_MAX 250

typedef struct s_vars	t_vars;
typedef struct s_philo
{
	t_vars			*vars;
	pthread_t		thread;
	long			id;
	long			first_fork;
	long			second_fork;
	long			last_eat;
	long			eat_count;
}	t_philo;

typedef struct s_vars
{
	t_philo				philosophers[PHILOS_MAX];
	pthread_t			observer_thread;
	pthread_mutex_t		forks[PHILOS_MAX];
	pthread_mutex_t		last_eat_mutex[PHILOS_MAX];
	pthread_mutex_t		eat_count_mutex[PHILOS_MAX];
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		is_finished_mutex;
	pthread_mutex_t		start_time_mutex;
	long					number_of_philosophers;
	long					time_to_die;
	long					time_to_eat;
	long					time_to_sleep;
	long					eat_times;
	long				start_time;
	long				is_finished;
}	t_vars;

int		exit_error(char *error_message);
int		ft_atoi(const char *str);
int		mutex_array_init(pthread_mutex_t *mutex_array, int size);
int		mutex_array_destroy(pthread_mutex_t *mutex_array, int size);
long	read_long(long value, pthread_mutex_t *mutex);
void	write_long(long *value, long new_value, pthread_mutex_t *mutex);
long	ft_getcurrenttime(void);
void	ft_usleep(long time);
void	*philo_routine(void *void_philo);
void	announce(char *message, t_philo *philo);
void	*observer_routine(void *void_vars);

#endif
