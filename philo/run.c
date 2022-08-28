/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:11:53 by jabae             #+#    #+#             */
/*   Updated: 2022/08/28 23:16:04 by jabae            ###   ########.fr       */
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
	// if ((long long)info->time_die < init_time() - philo->time_last_eat)
	// {
	// 	print_philo(info, init_time() - info->time_start, philo->id, DIE);
	// 	isdied = 1;
	// }
	// pthread_mutex_unlock(&(info->check_last_eat));
	return (isdied);
}

static int	eat_philo(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&philo->info->fork[philo->fork_left]);
	print_philo(info, init_time() - info->time_start, philo->id, FORK);
	if (info->num_philo == 1)
	{
		wait_time(info->time_die, philo);
		pthread_mutex_unlock(&philo->info->fork[philo->fork_left]);
		print_philo(info, init_time() - info->time_start, philo->id, DIE);
		return (1);
	}
	pthread_mutex_lock(&philo->info->fork[philo->fork_right]);
	print_philo(info, init_time() - info->time_start, philo->id, FORK);
	if (check_death(philo))
	{
		pthread_mutex_unlock(&philo->info->fork[philo->fork_left]);
		pthread_mutex_unlock(&philo->info->fork[philo->fork_right]);
		return (1);
	}
	print_philo(info, init_time() - info->time_start, philo->id, EAT);
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

static void	*morintoring(void	*ph)
{
	t_philo	*philo;
	t_info	*info;
	int	i;

	philo = (t_philo *)ph;
	info = philo->info;
	i = -1;
	while (1)
	{
		if (++i >= info->num_philo)
			i = 0;
		pthread_mutex_lock(&(info->check_full));
		if (info->num_full_philo == info->num_philo)
		{
			pthread_mutex_lock(&(info->check_death));
			info->die_flag = 1;
			pthread_mutex_unlock(&(info->check_death));
			break ;
		}
		pthread_mutex_unlock(&(info->check_full));
		pthread_mutex_lock(&(info->check_last_eat));
		if ((long long)info->time_die < init_time() - philo[i].time_last_eat)
		{
			print_philo(info, init_time() - info->time_start, philo[i].id, DIE);
			pthread_mutex_unlock(&(info->check_last_eat));
			break;
		}
		pthread_mutex_unlock(&(info->check_last_eat));
		/////////////////////////////////////////////////
		// pthread_mutex_lock(&(info->check_last_eat));
		// if (check_death(&philo[i])) // !!!잠자는 시간동안 죽고 종료 안되는 문제 해결해야 함
		// {
		// 	pthread_mutex_lock(&(info->check_death));
		// 	info->die_flag = 1;
		// 	pthread_mutex_unlock(&(info->check_death));
		// 	break ;
		// }
		// pthread_mutex_unlock(&(info->check_last_eat));
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
