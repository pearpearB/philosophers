/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:11:53 by jabae             #+#    #+#             */
/*   Updated: 2022/08/29 16:41:25 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	if (check_die_flag(info))
		return (1);
	if ((long long)info->time_die < init_time() - philo->time_last_eat)
	{
		print_philo(info, philo->id, DIE);
		return (1);
	}
	return (0);
}

static int	eat_philo(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&philo->info->fork[philo->fork_right]);
	print_philo(info, philo->id, FORK);
	// if (info->time_die < (init_time() - philo->time_last_eat) + info->time_eat)
	// {
	// 	pthread_mutex_unlock(&philo->info->fork[philo->fork_right]);
	// 	wait_time((info->time_die - (init_time() - philo->time_last_eat)), philo);
	// 	check_death(philo);
	// } // 시도하려 했으나 실패함
	pthread_mutex_lock(&philo->info->fork[philo->fork_left]);
	print_philo(info, philo->id, FORK);
	if (check_death(philo))
	{
		pthread_mutex_unlock(&philo->info->fork[philo->fork_right]);
		pthread_mutex_unlock(&philo->info->fork[philo->fork_left]);
		return (1);
	}
	print_philo(info, philo->id, EAT);
	philo->time_last_eat = init_time();
	philo->num_eat += 1;
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
		if (check_death(philo))
			break ;
		if (eat_philo(philo->info, philo))
			break ;
		if (philo->info->num_must_eat == philo->num_eat)
			break ;
		if (check_death(philo))
			break ;
		print_philo(philo->info, philo->id, SLEEP);
		wait_time(philo->info->time_sleep, philo);
		if (check_death(philo))
			break ;
		print_philo(philo->info, philo->id, THINK);
		usleep(250);
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
