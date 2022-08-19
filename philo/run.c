/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:11:53 by jabae             #+#    #+#             */
/*   Updated: 2022/08/17 16:16:39 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_acting(t_philo *philo, int status)
{
	long long	time;
	int		id;

	time = get_time() - philo->info->time_start;
	id = philo->id;
	if (status == FORK)
		printf("%u : philo[%d] has taken a fork\n", time, id);
	else if (status == EAT)
		printf("%u : philo[%d] is died\n", time, id);
	else if (status == SLEEP)
		printf("%u : philo[%d] is died\n", time, id);
	else if (status == THINK)
		printf("%u : philo[%d] is died\n", time, id);
	else if (status == DIE)
		printf("%u : philo[%d] is died\n", time, id);
}

static int check_death(t_philo *philo)
{
	if (philo->info->time_die < get_time() - philo->time_last_eat || \
		philo->info->isdied == 1)
	{
		philo->info->isdied = 1;
		print_acting(philo, DIE);
		return (1);
	}
	return (0);
}

static int	check_eat(t_philo *philo)
{
	if (check_death(philo))
		return (0);
	pthread_mutex_lock(&philo->info->fork[philo->fork_right]);
	pthread_mutex_lock(&philo->info->fork[philo->fork_left]);
	print_acting(philo, FORK);

}

static void	*life_cycle(void *philo)
{
	t_philo philo;

	philo = (t_philo *)philo;
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
