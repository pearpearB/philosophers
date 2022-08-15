/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:13:03 by jabae             #+#    #+#             */
/*   Updated: 2022/08/15 15:15:42 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int get_info(char **argv, t_info *info)
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
		return(ft_error("[Error] Can't get time\n"));
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

int main(int argc, char *argv[])
{
	t_info	info;
	t_philo	*philo;

	if (!(argc == 5 || argc == 6) || !get_info(argv, &info))
		return(ft_error("[Error] Invalid Arguments\n"));
	if (!init_info(&info))
		return(ft_error("[Error] Can't init info for Mutex\n"));
	init_philo(&info, &philo);
	run_philo(&info, philo);
	// free_thread(&info, philo);
	
	printf("%d\n", info.num_philo);
	printf("%d\n", info.time_die);
	printf("%d\n", info.time_eat);
	printf("%d\n", info.time_sleep);
	printf("%d\n", info.num_must_eat);
	return (0);
}
