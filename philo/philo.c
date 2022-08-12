/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:13:03 by jabae             #+#    #+#             */
/*   Updated: 2022/08/12 15:18:24 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int get_info(char **argv, t_info *info)
{
	info->num_philo = ft_atoui(argv[1]);
	info->time_die = ft_atoui(argv[2]);
	info->time_eat = ft_atoui(argv[3]);
	info->time_sleep = ft_atoui(argv[4]);
	if (argv[5])
	{
		info->num_must_eat = ft_atoui(argv[5]);
		if (info->num_must_eat < 1)
			return (0);
	}
	else if (!argv[5])
		info->num_must_eat = -1;
	if (info->num_philo < 1 || info->time_die < 1 || \
		info->time_eat < 1 || info->time_sleep < 1)
		return (0);
	return (1);
}

static unsigned int	get_time()
{
	struct timeval	tp;

	if (gettimeofday(&tp, NULL))
		ft_error("[Error] Invalid Arguments\n");
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

static void init(t_info *info, t_philo philo)
{
	int	i;

	i = -1;
	info->num_die = 0;
	info->start_time = get_time();
}

int main(int argc, char *argv[])
{
	t_info	info;
	t_philo	*philo;

	if (!(argc == 5 || argc == 6) || !get_info(argv, &info))
		ft_error("[Error] Invalid Arguments\n");
	info.fork = malloc(sizeof(pthread_mutex_t) * info.num_philo);
	if (!info.fork)
		ft_error("[Error] Insufficient Memory\n");
	philo = malloc(sizeof(t_philo) * info.num_philo);
	if (!philo)
		ft_error("[Error] Insufficient Memory\n");
	init(&info, philo);
	
	printf("%d\n", info.num_philo);
	printf("%d\n", info.time_die);
	printf("%d\n", info.time_eat);
	printf("%d\n", info.time_sleep);
	printf("%d\n", info.num_must_eat);
	return (0);
}
