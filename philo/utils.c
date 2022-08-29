/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:24:17 by jabae             #+#    #+#             */
/*   Updated: 2022/08/29 11:21:01 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo(t_info *info, long long time, int id, int status)
{
	int	isdied;

	pthread_mutex_lock(&(info->print));
	pthread_mutex_lock(&(info->check_death));
		isdied = info->die_flag;
	pthread_mutex_unlock(&(info->check_death));
	if (!isdied)
	{
		if (status == FORK)
			printf("%lld %d has taken a fork\n", time, id);
		else if (status == EAT)
			printf("%lld %d is eating\n", time, id);
		else if (status == SLEEP)
			printf("%lld %d is sleeping\n", time, id);
		else if (status == THINK)
			printf("%lld %d is thinking\n", time, id);
		else if (status == DIE)
		{
			printf("%lld %d died\n", time, id);
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
	while ((init_time() - start_time < time)) // 중간중간 죽었는지 체크추가하기
	{
		if ((long long)philo->info->time_die < init_time() - philo->time_last_eat)
			break;
		usleep(200);
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
