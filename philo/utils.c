/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:24:17 by jabae             #+#    #+#             */
/*   Updated: 2022/08/24 15:22:47 by jabae            ###   ########.fr       */
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

void	wait_time(unsigned int time)
{
	unsigned int	start_time;
	unsigned int	now_time;

	start_time = get_time();
	while(1)
	{
		now_time = get_time();
		if (now_time - start_time >= time)
			break ;
		usleep(100);
	}
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
	return ('0' <= s && s <= '9');
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
	while (*s)
	{
		if (ft_isdigit(*s))
			return(-1);
		result = result * 10 + (*s - '0');
		if ((sign > 0 && result * sign > INT_MAX) || \
			(sign < 0 && result * sign < INT_MIN))
			return(-1);
		s++;
	}
	return (result * sign);
}
