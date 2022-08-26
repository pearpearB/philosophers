/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:11:53 by jabae             #+#    #+#             */
/*   Updated: 2022/08/26 16:33:08 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_death(t_philo *philo)
{
	t_info	*info;
	int dead;

	info = philo->info;
	pthread_mutex_lock(&(info->check_death));
		dead = info->isdied;
	pthread_mutex_unlock(&(info->check_death));
	if (dead)
		return (1);
	else if ((unsigned int)info->time_die < init_time() - philo->time_last_eat)
	{
		print_status(philo->info, init_time() - info->time_start, philo->id, DIE);
		return (1);
	}
	return (0);
}

static int eat_philo(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&philo->info->fork[philo->fork_left]);
	print_status(info, init_time() - info->time_start, philo->id, FORK);
	if (info->num_philo == 1)
	{
		wait_time(info->time_die);
		pthread_mutex_unlock(&philo->info->fork[philo->fork_left]);
		print_status(info, init_time() - info->time_start, philo->id, DIE);
		return (1);
	}
	pthread_mutex_lock(&philo->info->fork[philo->fork_right]);
	print_status(info, init_time() - info->time_start, philo->id, FORK);
	if (check_death(philo))
	{
		pthread_mutex_unlock(&philo->info->fork[philo->fork_left]);
		pthread_mutex_unlock(&philo->info->fork[philo->fork_right]);
		return (1);
	}
	print_status(info, init_time() - info->time_start, philo->id, EAT);
	printf("eat_count: %d\n", philo->num_eat + 1);
	philo->time_last_eat = init_time();
	philo->num_eat += 1;
	wait_time(info->time_eat);
	pthread_mutex_unlock(&philo->info->fork[philo->fork_right]);
	pthread_mutex_unlock(&philo->info->fork[philo->fork_left]);
	return (0);
}

static void	*act_philo(void *ph)
{
	t_philo *philo;
	t_info	*info;

	philo = (t_philo *)ph;
	info = philo->info;
	if (!(philo->id % 2))
		usleep(200);
	while (1)
	{
		if (check_death(philo))
			break;
		if (eat_philo(info, philo))
			break;
		if (check_death(philo) || philo->num_eat == info->num_must_eat)
			break;
		print_status(info, init_time() - info->time_start, philo->id, SLEEP);
		wait_time(info->time_sleep);
		if (check_death(philo))
			break;
		print_status(info, init_time() - info->time_start, philo->id, THINK);
	}
	return (0);
}

void	run_philo(t_info *info, t_philo *philo)
{
	int	i;

	i = -1;
	info->time_start = init_time();
	while (++i < info->num_philo)
	{
		philo[i].time_last_eat = init_time();
		if (pthread_create(&philo[i].thread, NULL, act_philo, &philo[i]) != 0)
			return ;
	}
	i = -1;
	while (++i < info->num_philo)
		pthread_join(philo[i].thread, NULL);
}
