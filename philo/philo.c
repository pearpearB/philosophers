/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:13:03 by jabae             #+#    #+#             */
/*   Updated: 2022/08/11 16:49:46 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_and_set_info(char *argv[], t_info *info)
{
	info->num_philo = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		info->num_must_eat = ft_atoi(argv[5]);
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

int main(int argc, char *argv[])
{
	t_info	info;

	if (!(argc == 5 || argc == 6) || !check_and_set_info(argv, &info))
		ft_error("[Error] Invalid Arguments\n");

	printf("%d\n", info.num_philo);
	printf("%d\n", info.time_die);
	printf("%d\n", info.time_eat);
	printf("%d\n", info.time_sleep);
	printf("%d\n", info.num_must_eat);
	return (0);
}