/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:11:53 by jabae             #+#    #+#             */
/*   Updated: 2022/08/30 12:22:37 by jabae            ###   ########.fr       */
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
	sem_wait(info->eat_sem);
	philo->time_last_eat = init_time();
	sem_post(info->eat_sem);
	wait_time(info->time_eat);
	sem_post(info->fork);
	sem_post(info->fork);
}

static void	*one_philo(t_info *info, t_philo *philo)
{
	print_philo(info, philo->id, FORK);
	wait_time(info->time_die);
	print_philo(info, philo->id, DIE);
	return (0);
}

static void	*monitoring(void	*ph)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)ph;
	info = philo->info;
	while (1)
	{
		// sem_wait(info->check_sem);
		sem_wait(info->eat_sem);
		if ((long long)info->time_die < init_time() - philo->time_last_eat)
		{
			sem_post(info->eat_sem);
			exit(1);
		}
		sem_post(info->eat_sem);
		usleep(100);
	}
	return (0);
}

void	*run_philo(t_info *info, t_philo *philo)
{
	if (info->num_philo == 1)
		return (one_philo(info, philo)); // ㅁㅗ니터링이 해줄 수도 있음 확인!
	philo->time_last_eat = init_time();
	if (pthread_create(&philo->thread, NULL, &monitoring, philo) != 0)
		exit(1);
	if (!(philo->id % 2))
		wait_time(info->time_eat - 10);
		// usleep(1000 * info->time_eat);
	pthread_detach(philo->thread);
	while (1)
	{
		// if (check_death(philo->info))
		// 	break ;
		eat_philo(info, philo);
		// if (check_death(philo->info) || \
		// 	philo->num_eat == philo->info->num_must_eat)
		// 	break ;
		if (philo->num_eat == info->num_must_eat)
			break ;
		print_philo(info, philo->id, SLEEP);
		wait_time(info->time_sleep);
		// if (check_death(philo->info))
		// 	break ;
		print_philo(info, philo->id, THINK);
		usleep(250);
	}
	exit (0);
}
