/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:11:53 by jabae             #+#    #+#             */
/*   Updated: 2022/08/29 17:37:49 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eat_philo(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&philo->info->fork[philo->fork_right]);
	print_philo(info, philo->id, FORK);
	pthread_mutex_lock(&philo->info->fork[philo->fork_left]);
	print_philo(info, philo->id, FORK);
	if (check_death(info))
	{
		pthread_mutex_unlock(&philo->info->fork[philo->fork_right]);
		pthread_mutex_unlock(&philo->info->fork[philo->fork_left]);
		return (1);
	}
	print_philo(info, philo->id, EAT);
	pthread_mutex_lock(&(info->check_last_eat));
	philo->time_last_eat = init_time();
	pthread_mutex_unlock(&(info->check_last_eat));
	philo->num_eat += 1;
	if (philo->num_eat == info->num_must_eat)
	{
		pthread_mutex_lock(&(info->check_full));
		info->num_full_philo += 1;
		pthread_mutex_unlock(&(info->check_full));
	}
	wait_time(info->time_eat, philo);
	pthread_mutex_unlock(&philo->info->fork[philo->fork_right]);
	pthread_mutex_unlock(&philo->info->fork[philo->fork_left]);
	return (0);
}

static void	*one_philo(t_info *info, t_philo *philo)
{
	print_philo(info, philo->id, FORK);
	wait_time(info->time_die, philo);
	print_philo(info, philo->id, DIE);
	return (0);
}

static void	*act_philo(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (philo->info->num_philo == 1)
		return (one_philo(philo->info, philo));
	if (!(philo->id % 2))
		usleep(200);
	while (1)
	{
		if (check_death(philo->info))
			break ;
		if (eat_philo(philo->info, philo))
			break ;
		if (check_death(philo->info) || \
			philo->num_eat == philo->info->num_must_eat)
			break ;
		print_philo(philo->info, philo->id, SLEEP);
		wait_time(philo->info->time_sleep, philo);
		if (check_death(philo->info))
			break ;
		print_philo(philo->info, philo->id, THINK);
		usleep(250);
	}
	return (0);
}

static void	*morintoring(void	*ph)
{
	t_philo	*philo;
	t_info	*info;
	int		i;

	philo = (t_philo *)ph;
	info = philo->info;
	i = -1;
	while (1)
	{
		if (++i >= info->num_philo)
			i = 0;
		if (check_end(info, philo, i))
			break ;
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
	if (pthread_create(&info->monitor_thread, NULL, morintoring, philo) != 0)
		return ;
	pthread_join(info->monitor_thread, NULL);
	i = -1;
	while (++i < info->num_philo)
		pthread_join(philo[i].thread, NULL);
}
