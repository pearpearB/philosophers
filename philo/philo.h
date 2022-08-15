/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:13:31 by jabae             #+#    #+#             */
/*   Updated: 2022/08/15 17:03:11 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define UINT_MAX 4294967295

typedef struct s_info
{
	unsigned int	num_philo;
	unsigned int	time_die;
	unsigned int	time_eat;
	unsigned int	time_sleep;
	int	num_must_eat;
	int	isdied; // ?
	// int	finish_eat; // ?
	long long	time_start;
	pthread_mutex_t	*fork;
	// pthread_mutex_t	check_eat_cnt; // ?
	// pthread_mutex_t check_last_food; // ?
	// pthread_mutex_t	check_death; // ?
	pthread_mutex_t	print; // ?
}	t_info;

typedef struct s_philo
{
	unsigned int	id;
	unsigned int	fork_right;
	unsigned int	fork_leht;
	unsigned int	eat_cnt;
	long long	time_last_eat; // ?
	t_info	*info;
	pthread_t	th;
}	t_philo;

/* init */
int		init_info(t_info *info);
void	init_philo(t_info *info, t_philo **philo);

/* run */
void	run_philo(t_info *info, t_philo *philo);

/* utils */
int 	ft_error(char *msg);
long long	ft_atoui(const char *s);

#endif
