/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:13:03 by jabae             #+#    #+#             */
/*   Updated: 2022/09/05 15:50:35 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	free_process(t_info *info, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < info->num_philo)
		pthread_mutex_destroy(&(philo[i].check_last_eat));
	sem_close(info->print);
	sem_unlink("fork");
	sem_unlink("print");
	free(philo);
	free(info->pid);
}

void	wait_process(t_info *info)
{
	int	i;
	int	status;

	i = -1;
	while (++i < info->num_philo)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			kill_pids(info, info->num_philo);
			usleep(2000); // SIGINT로 종료하기 때문에 회수할 시간이 필요함
			sem_post(info->print);
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
		ft_error("Invalid Arguments");
	if (init_info(&info))
		ft_error("Semaphore open failed");
	if (init_philo(&info, &philo))
		ft_error("Philo init failed");
	if (init_process(&info, philo))
		ft_error("Philo process failed");
	wait_process(&info);
	free_process(&info, philo);
	return (0);
}
