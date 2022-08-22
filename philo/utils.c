/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:24:17 by jabae             #+#    #+#             */
/*   Updated: 2022/08/22 19:10:29 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_thread(t_info *info, t_philo *philo)
{
	int i;

	i = -1;
	while (++i < info->num_philo)
		pthread_mutex_destroy(&(info->fork[i]));
	pthread_mutex_destroy(&(info->print));
	pthread_mutex_destroy(&(info->check_death));
	free(info->fork);
	free(philo);
}

unsigned int	get_time(void)
{
	struct timeval	tp;

	if (gettimeofday(&tp, NULL) < 0)
		return(printf("[Error] Can't get time\n"));
	return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
}

static int	ft_isdigit(const char s)
{
	if (!('0' <= s && s <= '9'))
		return(printf("[Error] Not Number Type\n"));
	return (1);
}

int	ft_atoi(const char *s)
{
	long long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (((*s >= 9 && *s <= 13) || *s == ' ') && *s)
		s++;
	if ((*s == '+' || *s == '-') && *s)
	{
		if (*s == '-')
			sign *= -1;
		s++;
	}
	while (*s && ft_isdigit(*s))
	{
		result = result * 10 + (*s - '0');
		if (sign > 0 && result * sign > INT_MAX)
			return(printf("[Error] Out of Integer Range\n"));
		else if (sign < 0 && result * sign < INT_MIN)
			return(printf("[Error] Out of Integer Range\n"));
		s++;
	}
	return (result * sign);
}
