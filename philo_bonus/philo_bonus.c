/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:13:03 by jabae             #+#    #+#             */
/*   Updated: 2022/08/29 22:58:52 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	free_process(t_info *info, t_philo *philo)
{
	sem_close(info->check_sem);
	sem_close(info->print_sem);
	sem_close(info->eat_sem);
	sem_unlink("fork_sem");
	sem_unlink("eat_sem");
	sem_unlink("print_sem");
	sem_unlink("check_sem");
	free(philo);
	free(info->pid);
}

void	wait_process(t_info *info, t_philo *philo)
{
	int	i;
	int	status;

	i = -1;
	while (++i < info->num_philo)
	{
		waitpid(-1, &status, 0);
		if (status == 0)
		{
			sem_post(info->check_sem);
			sem_post(info->print_sem);
		}
		else
		{
			if (info->die_flag == 0)
				print_philo(info, philo->id, DIE);
			info->die_flag = 1;
			kill_pids(info, info->num_philo);
			sem_post(info->print_sem);
			break ;
		}
	}
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
		exit(EXIT_FAILURE);
	}
	if (init_info(&info))
	{
		printf("[Error] Semaphore open failed\n");
		exit(EXIT_FAILURE);
	}
	if (init_philo(&info, &philo))
	{
		printf("[Error] Philo init failed\n");
		exit(EXIT_FAILURE);
	}
	if (init_process(&info, &philo))
	{
		printf("[Error] Philo process failed\n");
		exit(EXIT_FAILURE);
	}
	run_philo(&info, philo);
	wait_process(&info, philo);
	free_process(&info, philo);
	return (0);
}
