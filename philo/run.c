/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:11:53 by jabae             #+#    #+#             */
/*   Updated: 2022/08/26 11:32:09 by jabae            ###   ########.fr       */
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
	// printf("check die %u\n", init_time() - philo->time_last_eat);
	if (dead)
		return (1);
	else if ((unsigned int)info->time_die < init_time() - philo->time_last_eat)
	{
		print_status(philo->info, init_time() - info->time_start, philo->id, DIE);
		pthread_mutex_lock(&(info->check_death));
			philo->info->isdied = 1;
		pthread_mutex_unlock(&(info->check_death));
		return (1);
	}
	return (0);
}

// int check_death2(t_philo *philo)
// {
// 	t_info	*info;
// 	unsigned int	now_time;
// 	int dead;

// 	dead = 0;
// 	info = philo->info;
// 	pthread_mutex_lock(&(info->check_death));
// 		dead = info->isdied;
// 	pthread_mutex_unlock(&(info->check_death));
// 	if (dead)
// 		return (1);
// 	now_time = init_time();
// 	if (now_time - philo->time_last_eat >= (unsigned int)info->time_die)
// 		dead = 1;
// 	if (dead)
// 		return (1);
// 	return (0);
// }

static int eat_philo(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&philo->info->fork[philo->fork_right]);
	print_status(info, init_time() - info->time_start, philo->id, FORK);
	if (info->num_philo == 1)
	{
		wait_time(info->time_die);
		pthread_mutex_unlock(&philo->info->fork[philo->fork_right]);
		print_status(info, init_time() - info->time_start, philo->id, DIE);
		return (1);
	}
	pthread_mutex_lock(&philo->info->fork[philo->fork_left]);
	print_status(info, init_time() - info->time_start, philo->id, FORK);
	if (check_death(philo))
		return (1);
	print_status(info, init_time() - info->time_start, philo->id, EAT);
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
		usleep(100);
	while (1)
	{
		if (check_death(philo))
			break;
		if (philo->num_eat == info->num_must_eat)
			break;
		if (eat_philo(info, philo))
			break;
		if (check_death(philo))
			break;
		print_status(info, init_time() - info->time_start, philo->id, SLEEP);
		wait_time(info->time_sleep);
		if (check_death(philo))
			break;
		print_status(info, init_time() - info->time_start, philo->id, THINK);
	}
	return (0);
}

// void	monitoring(t_info *info, t_philo *philo)
// {
// 	int	i;

// 	i = -1;
// 	while (1)
// 	{
// 		if (++i >= info->num_philo)
// 			i -= info->num_philo;
// 		// printf("test: %d\n", i);
// 		pthread_mutex_lock(&info->check_num_eat);
// 		if (info->num_must_eat == (&philo[i])->num_eat)
// 			break ;
// 		if (check_death(&philo[i]))
// 		{
// 			// print_status(info, init_time() - info->time_start, i + 1, DIE);
// 			break ;
// 		}
// 		pthread_mutex_unlock(&info->check_num_eat);
// 	}
// 	pthread_mutex_unlock(&info->check_num_eat);
// }

void	run_philo(t_info *info, t_philo *philo)
{
	int	i;
	// unsigned int now_time;

	i = -1;
	// now_time = init_time();
	// info->time_start = now_time;
	while (++i < info->num_philo)
	{
		// philo[i].time_last_eat = now_time;
		if (pthread_create(&philo[i].thread, NULL, act_philo, &philo[i]) != 0)
			return ;
		// if (pthread_detach(philo[i].thread))
		// 	return ;
	}
	// monitoring(info, philo);
	i = -1;
	while (++i < info->num_philo)
		pthread_join(philo[i].thread, NULL);
}
