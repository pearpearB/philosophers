/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:11:53 by jabae             #+#    #+#             */
/*   Updated: 2022/08/22 19:15:22 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	run_print(t_info *info, unsigned int time_act, int id, int status)
{
	int	num;
	int	dead;

	pthread_mutex_lock(&(info->print));
	// pthread_mutex_lock(&(info->check_death));
	// 	dead = info->isdied;
	// pthread_mutex_unlock(&(info->check_death));
	dead = check_death(philo); // check
	if (!dead)
	{
		if (status == FORK)
			printf("%u %d has taken a fork\n", time_act, id);
		else if (status == EAT)
			printf("%u %d is eating\n", time_act, id);
		else if (status == SLEEP)
			printf("%u %d is sleeping\n", time_act, id);
		else if (status == THINK)
			printf("%u %d is thinking\n", time_act, id);
		else if (status == DIE)
			printf("%u %d died\n", time_act, id);
	}
	pthread_mutex_unlock(&(info->print));
	return (0); // 여기서 죽으면 어캄?
}

static int check_death(t_philo *philo)
{
	t_info	*info;
	int dead;

	info = philo->info;
	pthread_mutex_lock(&(info->check_death));
		dead = info->isdied;
	pthread_mutex_unlock(&(info->check_death));
	if (dead)
		return (1);
	else if (info->time_die < get_time() - philo->time_last_eat)
	{
		run_print(philo->info, get_time() - info->time_start, philo->id, DIE);
		pthread_mutex_lock(&(info->check_death));
			philo->info->isdied = 1;
		pthread_mutex_unlock(&(info->check_death));
		return (1);
	}
	return (0);
}

static void	wait_time(unsigned int time)
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

static int eat_philo(t_info *info, t_philo *philo)
{
	if (check_death(philo))
		return (0);
	pthread_mutex_lock(&philo->info->fork[philo->fork_right]);
	pthread_mutex_lock(&philo->info->fork[philo->fork_left]);
	run_print(info, get_time() - info->time_start, philo->id, FORK);
	run_print(info, get_time() - info->time_start, philo->id, EAT);
	philo->time_last_eat = get_time();
	philo->num_eat += 1;
	wait_time(info->time_eat);
	pthread_mutex_unlock(&philo->info->fork[philo->fork_right]);
	pthread_mutex_unlock(&philo->info->fork[philo->fork_left]);
	return (1);
}

static void	*act_philo(void *ph)
{
	t_philo *philo;
	t_info	*info;
	int		dead;

	philo = (t_philo *)ph;
	info = philo->info;
	if (philo->id % 2 == 0)
		usleep(100);
	dead = 0;
	while (1)
	{
		pthread_mutex_lock(&(info->check_death));
		dead = info->isdied;
		pthread_mutex_unlock(&(info->check_death));
		if (dead || philo->num_eat == info->num_must_eat)
			break;
		if (!eat_philo(info, philo))
			break;
		run_print(info, get_time() - info->time_start, philo->id, SLEEP);
		wait_time(info->time_sleep);
		run_print(info, get_time() - info->time_start, philo->id, THINK);
	}
	return (0);
}

void	run_philo(t_info *info, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < info->num_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, act_philo, &philo[i]) != 0)
			return ;
	}
	i = -1;
	while (++i < info->num_philo)
		pthread_join(philo[i].thread, NULL);
}
