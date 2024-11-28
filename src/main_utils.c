/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obehavka <obehavka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:48:47 by obehavka          #+#    #+#             */
/*   Updated: 2024/11/28 11:55:23 by obehavka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_iswhitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static int	ft_isdigit(int ch)
{
	if (ch < 48 || ch > 57)
		return (0);
	return (1);
}

long	ft_gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000 + time.tv_usec);
}

void	ft_usleep(long time)
{
	long	start_time;

	start_time = ft_gettime();
	while (ft_gettime() - start_time < time)
		usleep(50);
}

long	ft_atol(const char *str)
{
	long	ret_int;
	int		is_positive;
	int		digit;

	is_positive = 1;
	ret_int = 0;
	while (ft_iswhitespace (*str))
		++str;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			is_positive *= (-1);
		++str;
	}
	while (ft_isdigit (*str))
	{
		digit = *str - '0';
		ret_int *= 10;
		ret_int -= digit;
		++str;
	}
	return (ret_int * is_positive * (-1));
}
