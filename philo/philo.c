/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:13:03 by jabae             #+#    #+#             */
/*   Updated: 2022/08/12 17:08:37 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int get_info(char **argv, t_info *info)
{
	info->num_philo = ft_atoui(argv[1]);
	info->time_die = ft_atoui(argv[2]);
	info->time_eat = ft_atoui(argv[3]);
	info->time_sleep = ft_atoui(argv[4]);
	if (info->num_philo < 1 || info->time_die < 1 || \
		info->time_eat < 1 || info->time_sleep < 1)
		return (0);
	if (argv[5])
	{
		info->num_must_eat = ft_atoui(argv[5]);
		if (info->num_must_eat < 1)
			return (0);
	}
	else if (!argv[5])
		info->num_must_eat = -1;
	return (1);
}

static int	get_time()
{
	struct timeval	tp;

	if (gettimeofday(&tp, NULL) < 0)
		ft_error("[Error] Can't get time\n");
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

int	init_info(t_info *info)
{
	int	i;
	
	i = -1;
	info->death = 0;
	info->start_time = get_time();
	if ((pthread_mutex_init(&info->check_eat_cnt, NULL)) != 0)
		return (0);
	if ((pthread_mutex_init(&info->check_last_food, NULL)) != 0)
		return (0);
	if ((pthread_mutex_init(&info->check_death, NULL)) != 0)
		return (0);
	if ((pthread_mutex_init(&info->print, NULL)) != 0)
		return (0);
	info->fork = malloc(sizeof(pthread_mutex_t) * info->num_philo);
	if (!info->fork)
		ft_error("[Error] Insufficient Memory\n");
	while (++i < info->num_philo)
	{
		if ((pthread_mutex_init(&info->fork[i], NULL)) != 0)
			return (0);
	}
	return (1);
}

void init_philo(t_info *info, t_philo **philo)
{
	int	i;

	*philo = malloc(sizeof(t_philo) * info->num_philo);
	if (!philo)
		ft_error("[Error] Insufficient Memory\n");
	i = -1;
	while (++i < info->num_philo)
	{
		(*philo)[i].id = i + 1;
		if (i == 0)
			(*philo)[i].fork_right = info->num_philo - 1;
		else
			(*philo)[i].fork_right = i - 1;
		(*philo)[i].fork_left = i;
		(*philo)[i].eat_cnt = 0;
		(*philo)[i].last_food_time = get_time();
		(*philo)[i].info = info;
	}
	return (1);
}

int main(int argc, char *argv[])
{
	t_info	info;
	t_philo	*philo;

	if (!(argc == 5 || argc == 6) || !get_info(argv, &info))
		ft_error("[Error] Invalid Arguments\n");
	if (!init_info(&info))
		ft_error("[Error] Can't init info for Mutex\n");
	init_philo(&info, &philo);
	
	printf("%d\n", info.num_philo);
	printf("%d\n", info.time_die);
	printf("%d\n", info.time_eat);
	printf("%d\n", info.time_sleep);
	printf("%d\n", info.num_must_eat);
	return (0);
}
