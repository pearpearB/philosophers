/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:24:17 by jabae             #+#    #+#             */
/*   Updated: 2022/08/30 12:01:18 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// int	check_death(t_info *info)
// {
// 	int		isdied;

// 	pthread_mutex_lock(&(info->check_death));
// 	isdied = info->die_flag;
// 	pthread_mutex_unlock(&(info->check_death));
// 	return (isdied);
// }

void	kill_pids(t_info *info, int id)
{
	int	i;

	i = -1;
	while (++i < id)
		kill(info->pid[i], SIGKILL);
	sem_post(info->check_sem);
}

void	print_philo(t_info *info, int id, int status)
{
	long long	now_time;

	now_time = init_time() - info->time_start;
	sem_wait(info->print_sem);
	sem_wait(info->check_sem);
	if (info->die_flag)
	{
		sem_post(info->check_sem);
		sem_post(info->print_sem);
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
	sem_post(info->check_sem);
	sem_post(info->print_sem);
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
