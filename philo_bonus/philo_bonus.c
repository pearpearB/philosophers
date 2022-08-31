/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:13:03 by jabae             #+#    #+#             */
/*   Updated: 2022/08/31 11:45:04 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	free_process(t_info *info, t_philo *philo)
{
	sem_close(info->check_death);
	sem_close(info->check_last_eat);
	sem_close(info->print);
	sem_unlink("fork");
	sem_unlink("check_last_eat");
	sem_unlink("check_death");
	sem_unlink("print");
	free(philo);
	free(info->pid);
}

void	wait_process(t_info *info, t_philo *philo) // 스레드 join 같은 역할
{
	int	i;
	int	status;

	i = -1;
	while (++i < info->num_philo)
	{
		waitpid(-1, &status, 0); // pid 해당하는 값을 기다림 -1은 임의의 자식 프로세스 아무거나 기다림 // ststus는 exit 종료 코드를 받아옴
		if (status == 0)
		{
			sem_post(info->check_last_eat);
			sem_post(info->print);
		}
		else
		{
			sem_post(info->check_last_eat);
			sem_post(info->print);
			if (info->die_flag == 0)
				print_philo(info, philo->id, DIE);
			info->die_flag = 1;
			kill_pids(info, info->num_philo); // 한명이라도 죽으면 모든 자식 프로세스를 죽임
			sem_post(info->print);
			break ; //브레이크로 나와서 나머지 프리해줌
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
		ft_error("Invalid Arguments");
	if (init_info(&info))
		ft_error("Semaphore open failed");
	if (init_philo(&info, &philo))
		ft_error("Philo init failed");
	if (init_process(&info, philo))
		ft_error("Philo process failed");
	wait_process(&info, philo);
	free_process(&info, philo);
	return (0);
}
