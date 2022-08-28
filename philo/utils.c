/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:24:17 by jabae             #+#    #+#             */
/*   Updated: 2022/08/28 19:54:50 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_thread(t_info *info, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < info->num_philo)
		pthread_mutex_destroy(&(info->fork[i]));
	pthread_mutex_destroy(&(info->print));
	pthread_mutex_destroy(&(info->check_death));
	pthread_mutex_destroy(&(info->check_full));
	pthread_mutex_destroy(&(info->check_last_eat));
	free(info->fork);
	free(philo);
}

void	print_philo(t_info *info, long long time, int id, int status)
{
	int	dead;

	pthread_mutex_lock(&(info->print));
	pthread_mutex_lock(&(info->check_death));
		dead = info->isdied;
	pthread_mutex_unlock(&(info->check_death));
	if (!dead)
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
			info->isdied = 1;
			pthread_mutex_unlock(&(info->check_death));
		}
	}
	pthread_mutex_unlock(&(info->print));
}

void	wait_time(long long time)
{
	long long	start_time;

	start_time = init_time();
	while (init_time() - start_time < time)
		usleep(200);
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
