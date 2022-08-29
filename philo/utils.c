/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:24:17 by jabae             #+#    #+#             */
/*   Updated: 2022/08/29 14:00:29 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_die_flag(t_info *info)
{
	int	isdied;

	pthread_mutex_lock(&(info->check_death));
	isdied = info->die_flag;
	pthread_mutex_unlock(&(info->check_death));
	return (isdied);
}

void	print_philo(t_info *info, int id, int status)
{
	long long	now_time;

	pthread_mutex_lock(&(info->print));
	now_time = init_time() - info->time_start;
	if (!check_die_flag(info))
	{
		if (status == FORK)
			printf("%lld %d has taken a fork\n", now_time, id);
		else if (status == EAT)
			printf("%lld %d is eating\n", now_time, id);
		else if (status == SLEEP)
			printf("%lld %d is sleeping\n", now_time, id);
		else if (status == THINK)
			printf("%lld %d is thinking\n", now_time, id);
		else if (status == DIE)
		{
			printf("%lld %d died\n", now_time, id);
			pthread_mutex_lock(&(info->check_death));
			info->die_flag = 1;
			pthread_mutex_unlock(&(info->check_death));
		}
	}
	pthread_mutex_unlock(&(info->print));
}

void	wait_time(long long time, t_philo *philo)
{
	long long	start_time;

	start_time = init_time();
	while ((init_time() - start_time < time))
	{
		if ((long long)philo->info->time_die < \
			init_time() - philo->time_last_eat)
			break ;
		usleep(250);
	}
}

static int	ft_isdigit(const char s)
{
	return ('0' <= s && s <= '9');
}

int	ft_atoi(const char *s)
{
	long long	result;
	int			sign;

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
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (-1);
		result = result * 10 + (*s - '0');
		if ((sign > 0 && result * sign > INT_MAX) || \
			(sign < 0 && result * sign < INT_MIN))
			return (-1);
		s++;
	}
	return (result * sign);
}
