/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:13:03 by jabae             #+#    #+#             */
/*   Updated: 2022/08/19 18:21:27 by jabae            ###   ########.fr       */
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
	free_thread(&info, philo);
	return (0);
}

// gcc -fsanitize=thread -g init.c  philo.c philo.h run.c utils.c
