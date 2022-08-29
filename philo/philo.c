/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:13:03 by jabae             #+#    #+#             */
/*   Updated: 2022/08/29 17:03:23 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_thread(t_info *info, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < info->num_philo)
		pthread_mutex_destroy(&(info->fork[i]));
	pthread_mutex_destroy(&(info->print));
	pthread_mutex_destroy(&(info->check_death));
	pthread_mutex_destroy(&(info->check_full));
	pthread_mutex_destroy(&(info->check_last_eat));
	free(info->fork);
	free(philo);
}

static int	get_info(char **argv, t_info *info)
{
	info->num_philo = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	if (info->num_philo < 1 || info->time_die < 1 || \
		info->time_eat < 1 || info->time_sleep < 1)
		return (1);
	if (argv[5])
	{
		info->num_must_eat = ft_atoi(argv[5]);
		if (info->num_must_eat < 1)
			return (1);
	}
	else
		info->num_must_eat = -1;
	return (0);
}

int	main(int argc, char *argv[])
{
	t_info	info;
	t_philo	*philo;

	if (!(argc == 5 || argc == 6) || get_info(argv, &info))
	{
		printf("[Error] Invalid Arguments\n");
		return (-1);
	}
	if (init_info(&info))
		return (-1);
	if (init_philo(&info, &philo))
		return (-1);
	run_philo(&info, philo);
	free_thread(&info, philo);
	return (0);
}
