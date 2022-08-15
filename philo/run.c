/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:11:53 by jabae             #+#    #+#             */
/*   Updated: 2022/08/15 17:06:01 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int check_death(t_philo *philo)
{
	if (philo->info->time_die < get_time() - philo->time_last_eat || \ // 시간? 어떤시간?
		philo->info->isdied == 1)
	{
		philo->info->isdied = 1;
		printf("%u : philo[%d] is died\n", \
			get_time() - philo->info->time_start, philo->id); // 어떤시간~~~?!?!?!?!
		return (1);
	}
	return (0);
}

static void	*life_cycle(void *philo)
{
	t_philo philo;

	philo = (t_philo *)philo;
	if (philo->id % 2 == 0)
		usleep(100);
	while (!check_death(philo))
	{
		// 여기부터!
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
