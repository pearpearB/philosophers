/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:11:53 by jabae             #+#    #+#             */
/*   Updated: 2022/08/29 22:10:27 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat_philo(t_info *info, t_philo *philo)
{
	sem_wait(info->fork);
	print_philo(info, philo->id, FORK);
	sem_wait(info->fork);
	print_philo(info, philo->id, FORK);
	print_philo(info, philo->id, EAT);
	philo->num_eat += 1;
	sem_wait(info->eat_sem);
	philo->time_last_eat = init_time();
	sem_post(info->eat_sem);
	wait_time(info->time_eat, philo);
	sem_post(info->forks);
	sem_post(info->forks); // 여기부터 해야함
}

static void	*one_philo(t_info *info, t_philo *philo)
{
	print_philo(info, philo->id, FORK);
	wait_time(info->time_die, philo);
	print_philo(info, philo->id, DIE);
	return (0);
}

// static void	*act_philo(void *ph)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)ph;
// 	if (philo->info->num_philo == 1)
// 		return (one_philo(philo->info, philo));
// 	if (!(philo->id % 2))
// 		usleep(200);
// 	while (1)
// 	{
// 		if (check_death(philo->info))
// 			break ;
// 		if (eat_philo(philo->info, philo))
// 			break ;
// 		if (check_death(philo->info) || \
// 			philo->num_eat == philo->info->num_must_eat)
// 			break ;
// 		print_philo(philo->info, philo->id, SLEEP);
// 		wait_time(philo->info->time_sleep, philo);
// 		if (check_death(philo->info))
// 			break ;
// 		print_philo(philo->info, philo->id, THINK);
// 		usleep(250);
// 	}
// 	return (0);
// }

// static void	*morintoring(void	*ph)
// {
// 	t_philo	*philo;
// 	t_info	*info;
// 	int		i;

// 	philo = (t_philo *)ph;
// 	info = philo->info;
// 	i = -1;
// 	while (1)
// 	{
// 		if (++i >= info->num_philo)
// 			i = 0;
// 		if (check_end(info, philo, i))
// 			break ;
// 	}
// 	return (0);
// }

void	*run_philo(t_info *info, t_philo *philo)
{
	philo->time_last_eat = init_time(); // 한 명일 때, 짝수일 때 어케함?
	if (pthread_create(&philo->thread, NULL, &monitoring, philo) != 0)
		exit(1);
	pthread_detach(philo->thread);
	while (1)
	{
		if (check_death(philo->info))
			break ;
		if (eat_philo(philo->info, philo))
			break ;
		if (check_death(philo->info) || \
			philo->num_eat == philo->info->num_must_eat)
			break ;
		print_philo(philo->info, philo->id, SLEEP);
		wait_time(philo->info->time_sleep, philo);
		if (check_death(philo->info))
			break ;
		print_philo(philo->info, philo->id, THINK);
		usleep(250);
	}
	exit (0);
}
