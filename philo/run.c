/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:11:53 by jabae             #+#    #+#             */
/*   Updated: 2022/08/29 11:39:34 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	t_info	*info;
	int		isdied;

	info = philo->info;
	isdied = 0;
	pthread_mutex_lock(&(info->check_death));
		isdied = info->die_flag;
	pthread_mutex_unlock(&(info->check_death));
	
	// pthread_mutex_lock(&(info->check_last_eat));
	if ((long long)info->time_die < init_time() - philo->time_last_eat)
	{
		print_philo(info, init_time() - info->time_start, philo->id, DIE);
		isdied = 1;
	}
	// pthread_mutex_unlock(&(info->check_last_eat));

	return (isdied);
}

static int	eat_philo(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&philo->info->fork[philo->fork_right]);
	print_philo(info, init_time() - info->time_start, philo->id, FORK);
	if (info->num_philo == 1)
	{
		wait_time(info->time_die, philo);
		pthread_mutex_unlock(&philo->info->fork[philo->fork_right]);
		print_philo(info, init_time() - info->time_start, philo->id, DIE);
		return (1);
	}
	pthread_mutex_lock(&philo->info->fork[philo->fork_left]);
	print_philo(info, init_time() - info->time_start, philo->id, FORK);
	if (check_death(philo))
	{
		pthread_mutex_unlock(&philo->info->fork[philo->fork_right]);
		pthread_mutex_unlock(&philo->info->fork[philo->fork_left]);
		return (1);
	}
	print_philo(info, init_time() - info->time_start, philo->id, EAT);
	// pthread_mutex_lock(&(info->check_last_eat));
	philo->time_last_eat = init_time();
	// pthread_mutex_unlock(&(info->check_last_eat));
	philo->num_eat += 1;
	wait_time(info->time_eat, philo);
	pthread_mutex_unlock(&philo->info->fork[philo->fork_right]);
	pthread_mutex_unlock(&philo->info->fork[philo->fork_left]);
	return (0);
}

static void	*act_philo(void *ph)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)ph;
	info = philo->info;
	if (!(philo->id % 2))
		usleep(200);
	while (1)
	{
		if (check_death(philo))
			break ;
		if (eat_philo(info, philo))
			break ;
		if (info->num_must_eat == philo->num_eat)
			break;
		if (check_death(philo))
			break ;
		print_philo(info, init_time() - info->time_start, philo->id, SLEEP);
		wait_time(info->time_sleep, philo);
		if (check_death(philo))
			break ;
		print_philo(info, init_time() - info->time_start, philo->id, THINK);
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
