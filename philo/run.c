/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:11:53 by jabae             #+#    #+#             */
/*   Updated: 2022/08/19 17:07:05 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int check_death(t_philo *philo)
{
	if (philo->info->time_die < get_time() - philo->time_last_eat || \
		philo->info->isdied == 1)
	{
		philo->info->isdied = 1;
		printf("%u : philo[%d] died\n", \
			get_time() - philo->info->time_start, philo->id);
		return (1);
	}
	return (0);
}

static void	wait_time(unsigned int time, t_philo *philo)
{
	long long start_time;

	start_time = get_time();
	while(get_time() - start_time < time)
	{
		if (philo->info->isdied == 1 || philo->eat_cnt == philo->info->num_must_eat)
			return ;
		usleep(100);
	}
	return ;
}

static int	check_eat(t_philo *philo)
{
	if (check_death(philo))
		return (0);
	pthread_mutex_lock(&philo->info->fork[philo->fork_right]);
	pthread_mutex_lock(&philo->info->fork[philo->fork_left]);
	printf("%u : philo[%d] has taken a fork\n", \
		get_time() - philo->info->time_start, philo->id);
	printf("%u : philo[%d] is eating	|	total eat count: %d\n", \
		get_time() - philo->info->time_start, philo->id, philo->eat_cnt++);
	wait_time(philo->info->time_eat, philo);
	pthread_mutex_unlock(&philo->info->fork[philo->fork_right]);
	pthread_mutex_unlock(&philo->info->fork[philo->fork_left]);
	if (check_death(philo))
		return (0);
	philo->time_last_eat = get_time();
	philo->eat_cnt++;
	if (philo->info->isdied == 1 || philo->eat_cnt == philo->info->num_must_eat)
		return (0);
	return (1);
}

static void	*life_cycle(void *ph)
{
	t_philo *philo;

	philo = (t_philo *)ph;
	if (philo->id % 2 == 0)
		usleep(100);
	while (!check_death(philo))
	{
		if (philo->eat_cnt == philo->info->num_must_eat)
			break ;
		if (!check_eat(philo))
			break ;
		if (get_time() - philo->info->time_start > 0 && philo->info->isdied == 0)
			printf("%u : philo[%d] is sleeping\n", \
				get_time() - philo->info->time_start, philo->id);
		if (!check_death(philo))
			break ;
		if (get_time() - philo->info->time_start > 0 && philo->info->isdied == 0)
			printf("%u : philo[%d] is thinking\n", \
				get_time() - philo->info->time_start, philo->id);
	}
	return (0);
}

void	run_philo(t_info *info, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < info->num_philo)
	{
		if (pthread_create(&philo[i].th, NULL, life_cycle, &philo[i]) != 0)
			return ;
	}
	i = -1;
	while (++i < info->num_philo)
		pthread_join(philo[i].th, NULL);
}
