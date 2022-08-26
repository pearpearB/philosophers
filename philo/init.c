/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:00:31 by jabae             #+#    #+#             */
/*   Updated: 2022/08/26 15:45:14 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	init_time(void)
{
	struct timeval	tp;

	if (gettimeofday(&tp, NULL) < 0)
		return(printf("[Error] Can't get time\n"));
	return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
}

int	init_info(t_info *info)
{
	int	i;
	
	i = -1;
	info->isdied = 0;
	if ((pthread_mutex_init(&info->check_death, NULL)) != 0)
		return (0);
	if ((pthread_mutex_init(&info->print, NULL)) != 0)
		return (0);
	info->fork = malloc(sizeof(pthread_mutex_t) * info->num_philo);
	if (!info->fork)
		return(printf("[Error] Insufficient Memory\n"));
	while (++i < info->num_philo)
	{
		if ((pthread_mutex_init(&info->fork[i], NULL)) != 0)
			return(printf("[Error] Can't init info for Mutex\n"));
	}
	return (0);
}

int init_philo(t_info *info, t_philo **philo)
{
	int	i;

	*philo = malloc(sizeof(t_philo) * info->num_philo);
	if (!philo)
		return(printf("[Error] Insufficient Memory\n"));
	i = -1;
	while (++i < info->num_philo)
	{
		(*philo)[i].id = i + 1;
		if (i == 0)
			(*philo)[i].fork_right = info->num_philo - 1;
		else
			(*philo)[i].fork_right = i - 1;
		(*philo)[i].fork_left = i;
		(*philo)[i].num_eat = 0;
		(*philo)[i].info = info;
	}
	return (0);
}
