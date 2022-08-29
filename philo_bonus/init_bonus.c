/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:00:31 by jabae             #+#    #+#             */
/*   Updated: 2022/08/29 22:04:58 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	init_time(void)
{
	struct timeval	tp;

	if (gettimeofday(&tp, NULL) < 0)
		return (printf("[Error] Can't get time\n"));
	return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
}

int	init_info(t_info *info)
{
	info->die_flag = 0;
	info->num_full_philo = 0;
	info->time_start = init_time(); // 임시
	info->fork = sem_open("fork_sem", O_CREAT, 0644, info->philo_num);
	if (info->fork == SEM_FAILED)
		return (-1);
	info->eat_sem = sem_open("eat_sem", O_CREAT, 0644, 1);
	if (info->eat_sem == SEM_FAILED)
		return (-1);
	info->check_sem = sem_open("check_sem", O_CREAT, 0644, 1);
	if (info->check_sem == SEM_FAILED)
		return (-1);
	info->print = sem_open("print_sem", O_CREAT, 0644, 1);
	if (info->print == SEM_FAILED)
		return (-1);
	return (0);
}

int	init_philo(t_info *info, t_philo **philo)
{
	int	i;

	*philo = malloc(sizeof(t_philo) * info->num_philo);
	if (!philo)
		return (-1);
	i = -1;
	while (++i < info->num_philo)
	{
		(*philo)[i].id = i + 1;
		// if (i == 0)
		// 	(*philo)[i].fork_right = info->num_philo - 1;
		// else
		// 	(*philo)[i].fork_right = i - 1;
		// (*philo)[i].fork_left = i;
		(*philo)[i].num_eat = 0;
		(*philo)[i].info = info;
	}
	return (0);
}

static void	kill_pids(t_info *info, int id)
{
	int	i;

	i = -1;
	while (++i < id)
		kill(info->pid[i], SIGKILL);
	sem_post(info->check_sem); // 이거 왜 해줌???
}

int	init_process(t_info *info, t_philo **philo)
{
	int	i;

	info->pid = malloc(sizeof(pid_t) * info->num_philo);
	if (!info->pid)
		return (-1);
	i = -1;
	while (++i < info->num_philo)
	{
		info->pid[i] = fork();
		if (info->pid[i] < 0)
		{
			kill_pids(info, i);
			return (-1);
		}
		if (info->pid[i] == 0)
			run_philo(info, &philo[i]);
	}
	return (0);
}
