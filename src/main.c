/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obehavka <obehavka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:35:06 by obehavka          #+#    #+#             */
/*   Updated: 2024/11/21 09:53:27 by obehavka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	parse_input(int argc, char **argv, t_vars *vars)
{
	vars->number_of_philosophers = ft_atoi(argv[1]);
	vars->time_to_die = ft_atoi(argv[2]);
	vars->time_to_eat = ft_atoi(argv[3]);
	vars->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		vars->eat_times = ft_atoi(argv[5]);
	else
		vars->eat_times = -1;
	if (vars->number_of_philosophers < 1)
		exit_error("Invalid number of philosophers");
	if (vars->time_to_die < 1 || vars->time_to_eat < 1)
		exit_error("Invalid time values");
	if (argc == 6 && vars->eat_times < 0)
		exit_error("Invalid number of times to eat");
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 5 && argc != 6)
		exit_error("Invalid number of arguments");
	parse_input(argc, argv, &vars);
	return (0);
}
