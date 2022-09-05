/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:11:53 by jabae             #+#    #+#             */
/*   Updated: 2022/09/05 15:49:05 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	eat_philo(t_info *info, t_philo *philo)
{
	sem_wait(info->fork);
	print_philo(info, philo->id, FORK);
	sem_wait(info->fork);
	print_philo(info, philo->id, FORK);
	print_philo(info, philo->id, EAT);
	philo->num_eat += 1;
	pthread_mutex_lock(&(philo->check_last_eat));
	philo->time_last_eat = init_time();
	pthread_mutex_unlock(&(philo->check_last_eat));
	wait_time(info->time_eat);
	sem_post(info->fork);
	sem_post(info->fork);
}

static void	*monitoring(void	*ph)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)ph;
	info = philo->info;
	while (1)
	{
		pthread_mutex_lock(&(philo->check_last_eat));
		if ((long long)info->time_die < init_time() - philo->time_last_eat)
		{
			pthread_mutex_unlock(&(philo->check_last_eat));
			print_philo(info, philo->id, DIE);
			exit(1);
		}
		pthread_mutex_unlock(&(philo->check_last_eat));
		usleep(100);
	}
	return (0);
}

void	*run_philo(t_info *info, t_philo *philo)
{
	if (pthread_create(&philo->thread, NULL, &monitoring, philo) != 0)
		exit(1);
	if (!(philo->id % 2))
		usleep(100);
	pthread_detach(philo->thread);
	while (1)
	{
		eat_philo(info, philo);
		if (philo->num_eat == info->num_must_eat)
			break ;
		print_philo(info, philo->id, SLEEP);
		wait_time(info->time_sleep);
		print_philo(info, philo->id, THINK);
	}
	exit (0);
}