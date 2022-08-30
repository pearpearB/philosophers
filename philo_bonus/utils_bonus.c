/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:24:17 by jabae             #+#    #+#             */
/*   Updated: 2022/08/30 14:21:36 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_pids(t_info *info, int id)
{
	int	i;

	i = -1;
	while (++i < id)
		kill(info->pid[i], SIGKILL);
	sem_post(info->check_death);
}

void	print_philo(t_info *info, int id, int status)
{
	long long	now_time;

	now_time = init_time() - info->time_start;
	sem_wait(info->print);
	sem_wait(info->check_death);
	if (info->die_flag)
	{
		sem_post(info->check_death);
		sem_post(info->print);
		exit(1);
	}
	if (status == FORK)
		printf("%lld %d has taken a fork\n", now_time, id);
	else if (status == EAT)
		printf("%lld %d is eating\n", now_time, id);
	else if (status == SLEEP)
		printf("%lld %d is sleeping\n", now_time, id);
	else if (status == THINK)
		printf("%lld %d is thinking\n", now_time, id);
	else if (status == DIE)
		printf("%lld %d died\n", now_time, id);
	sem_post(info->check_death);
	sem_post(info->print);
}

void	wait_time(long long time)
{
	long long	start_time;

	start_time = init_time();
	while ((init_time() - start_time < time))
		usleep(250);
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
		if (!('0' <= *s && *s <= '9'))
			return (-1);
		result = result * 10 + (*s - '0');
		if ((sign > 0 && result * sign > INT_MAX) || \
			(sign < 0 && result * sign < INT_MIN))
			return (-1);
		s++;
	}
	return (result * sign);
}
